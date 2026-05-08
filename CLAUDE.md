# CLAUDE.md

Claude AI가 이 프로젝트를 이해하고 작업하기 위한 메커니즘 문서입니다.

## 프로젝트 유형

- **언어**: C++20
- **패턴**: MVC (Model-View-Controller)
- **빌드**: Visual Studio 2022 (MSBuild / `.vcxproj`)
- **도메인**: 반도체 시료 생산주문관리 PoC
- **외부 의존성 없음**: STL (`vector`, `optional`, `string`) 만 사용

## MVC 메커니즘

### 의존성 방향 (단방향)

```
View  ──→  Controller  ──→  Model
 └─────────────────────────→ (read-only 조회)
```

- `View`는 사용자 입력을 받아 `Controller`에 위임합니다.
- `Controller`는 `Model`의 참조(`&`)를 보유하여 상태를 변경합니다.
- `View`는 `Model`을 직접 참조하여 read-only 조회를 수행합니다.
- `Model`과 `Controller`는 `View`를 알지 못합니다.

### 핵심 클래스 요약

#### Model 계층 (`Model/`)

| 파일 | 역할 |
|------|------|
| `Sample.h` | 시료 구조체 + `SampleStatus` enum (Pending→InProduction→QualityCheck→Completed→Shipped/Cancelled) |
| `Order.h` | 주문 구조체 + `OrderStatus` enum (Received→Processing→Fulfilled/Cancelled) |
| `SampleModel.h/cpp` | 시료·주문의 인메모리 CRUD. `std::vector` 기반, `std::optional` 반환 |

#### Controller 계층 (`Controller/`)

| 파일 | 역할 |
|------|------|
| `ProductionController.h/cpp` | `registerSample`, `startProduction`, `completeQualityCheck`, `completeProduction`, `shipSample`, `cancelProduction` |
| `OrderController.h/cpp` | `placeOrder`, `processOrder`, `fulfillOrder`, `cancelOrder`, `getOrdersForSample` |

#### View 계층 (`View/`)

| 파일 | 역할 |
|------|------|
| `SampleView.h/cpp` | `run()` 루프 진입, 메뉴 렌더링, 입력 파싱, 조회 테이블 출력 |

### main.cpp — 의존성 조립점

```cpp
SampleModel          model;
ProductionController productionCtrl(model);
OrderController      orderCtrl(model);
SampleView           view(model, productionCtrl, orderCtrl);
view.run();
```

모든 객체는 스택에 생성되고, 참조로 주입됩니다.

## 코드 수정 가이드

| 목적 | 수정 위치 |
|------|-----------|
| 새로운 시료 필드 추가 | `Model/Sample.h` 구조체, `SampleModel::addSample` 시그니처 |
| 생산 상태 단계 추가 | `SampleStatus` enum + `ProductionController` 메서드 + `SampleView::sampleStatusToString` |
| 영속성 추가 (파일/DB) | `SampleModel`의 `samples_`/`orders_` 벡터를 교체 |
| 새로운 조회 화면 추가 | `SampleView`에 메서드 추가 후 `handleViewMenu`에 항목 연결 |
| Controller 로직 단위 테스트 | View 없이 `SampleModel` + `ProductionController`/`OrderController` 만으로 독립 테스트 가능 |

## 주의 사항

- 현재 데이터는 인메모리에만 존재합니다 — 프로그램 종료 시 초기화됩니다.
- 한글 출력은 Windows 콘솔 인코딩(CP949 또는 UTF-8) 설정에 따라 깨질 수 있습니다.
- `vcxproj`에 새 파일 추가 시 `<ClCompile>` / `<ClInclude>` 항목과 `vcxproj.filters`도 함께 업데이트해야 합니다.
