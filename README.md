# 반도체 시료 생산주문관리 시스템 (PoC)

C++ Console MVC 아키텍처 기반의 반도체 시료 생산주문관리 시스템 Proof of Concept입니다.

## 시스템 개요

반도체 공정에서 발생하는 시료의 등록, 생산 상태 관리, 주문 접수 및 처리 흐름을 콘솔 기반 MVC 패턴으로 구현합니다.

## 아키텍처

### 패키지 구조

```
ConsoleMVC-KyusungPark-19017482/
├── Model/
│   ├── Sample.h                # 시료 도메인 모델 (SampleStatus enum 포함)
│   ├── Order.h                 # 주문 도메인 모델 (OrderStatus enum 포함)
│   ├── SampleModel.h
│   └── SampleModel.cpp         # 시료·주문 인메모리 DB (CRUD)
├── Controller/
│   ├── ProductionController.h/cpp   # 생산 상태 전이 관리
│   └── OrderController.h/cpp        # 주문 접수·처리·완료·취소
├── View/
│   ├── SampleView.h
│   └── SampleView.cpp          # 콘솔 메뉴 UI 및 조회 출력
└── main.cpp                    # 진입점 — 의존성 조립
```

### MVC 역할 분리

| 레이어 | 클래스 | 역할 |
|--------|--------|------|
| **Model** | `SampleModel` | 반도체 시료와 주문 데이터를 인메모리 벡터로 관리 |
| **Controller** | `ProductionController` | 시료 등록 및 생산 상태 전이 로직 |
| **Controller** | `OrderController` | 주문 등록, 처리 시작, 완료, 취소 로직 |
| **View** | `SampleView` | 콘솔 메뉴 렌더링, 사용자 입력 수집, 조회 결과 출력 |

### 데이터 흐름

```
사용자 입력 → View → Controller → Model → View → 사용자 출력
```

- View는 Controller를 통해 데이터를 변경합니다.
- View는 조회 목적으로 Model을 직접 참조(read-only)합니다.
- Controller와 Model은 View에 의존하지 않습니다.

## 도메인 모델

### 시료 상태 흐름

```
대기(Pending) → 생산중(InProduction) → 품질검사(QualityCheck) → 완료(Completed) → 출하(Shipped)
                      └──────────────────────────────────────────────────────→ 취소(Cancelled)
```

### 주문 상태 흐름

```
접수(Received) → 처리중(Processing) → 완료(Fulfilled)
      └──────────────────────────────────→ 취소(Cancelled)
```

## 빌드 환경

- Visual Studio 2022
- C++20 (`/std:c++20`)
- Windows 10/11 (x64 / x86)
- 외부 라이브러리 없음 (STL만 사용)

## 실행 방법

1. Visual Studio에서 `ConsoleMVC-KyusungPark-19017482.slnx` 열기
2. `Debug | x64` 구성 선택
3. `Ctrl + F5` 로 빌드 및 실행

## 주요 기능

### 생산 관리
- 시료 등록 (시료명, 웨이퍼 Lot 번호, 공정 유형, 수량)
- 생산 시작 / 품질검사 완료 / 생산 완료 / 출하 처리 / 생산 취소

### 주문 관리
- 주문 등록 (시료 ID, 수량, 주문일자)
- 주문 처리 시작 / 주문 완료 / 주문 취소

### 조회
- 전체 시료 목록
- 시료 상세 정보 (연결된 주문 수 포함)
- 상태별 시료 필터 조회
- 전체 주문 목록
