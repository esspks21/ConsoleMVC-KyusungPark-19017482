#include "SampleView.h"
#include <iostream>
#include <iomanip>

SampleView::SampleView(SampleModel& model, ProductionController& productionCtrl,
                       OrderController& orderCtrl)
    : model_(model), productionCtrl_(productionCtrl), orderCtrl_(orderCtrl) {}

void SampleView::run() {
    int choice = 0;
    while (true) {
        showMainMenu();
        std::cin >> choice;
        switch (choice) {
        case 1: handleProductionMenu(); break;
        case 2: handleOrderMenu();      break;
        case 3: handleViewMenu();       break;
        case 0: std::cout << "\n프로그램을 종료합니다.\n"; return;
        default: std::cout << "잘못된 입력입니다.\n"; break;
        }
    }
}

void SampleView::showMainMenu() const {
    printSeparator();
    std::cout << "   반도체 시료 생산주문관리 시스템\n";
    printSeparator();
    std::cout << "  1. 생산 관리\n";
    std::cout << "  2. 주문 관리\n";
    std::cout << "  3. 조회\n";
    std::cout << "  0. 종료\n";
    printSeparator();
    std::cout << "선택 > ";
}

void SampleView::handleProductionMenu() {
    printSeparator();
    std::cout << "  [생산 관리]\n";
    std::cout << "  1. 시료 등록\n";
    std::cout << "  2. 생산 시작\n";
    std::cout << "  3. 품질검사 완료\n";
    std::cout << "  4. 생산 완료\n";
    std::cout << "  5. 출하 처리\n";
    std::cout << "  6. 생산 취소\n";
    std::cout << "  0. 뒤로\n";
    printSeparator();
    std::cout << "선택 > ";

    int choice; std::cin >> choice; std::cin.ignore();
    if (choice == 0) return;

    if (choice == 1) {
        std::string name, waferLot, processType;
        int qty;
        std::cout << "시료명        : "; std::getline(std::cin, name);
        std::cout << "웨이퍼 Lot 번호: "; std::getline(std::cin, waferLot);
        std::cout << "공정 유형     : "; std::getline(std::cin, processType);
        std::cout << "수량          : "; std::cin >> qty;
        int id = productionCtrl_.registerSample(name, waferLot, processType, qty);
        std::cout << "시료 등록 완료 (ID: " << id << ")\n";
    } else {
        std::cout << "시료 ID : ";
        int id; std::cin >> id;
        bool ok = false;
        if      (choice == 2) ok = productionCtrl_.startProduction(id);
        else if (choice == 3) ok = productionCtrl_.completeQualityCheck(id);
        else if (choice == 4) ok = productionCtrl_.completeProduction(id);
        else if (choice == 5) ok = productionCtrl_.shipSample(id);
        else if (choice == 6) ok = productionCtrl_.cancelProduction(id);
        std::cout << (ok ? "처리 완료\n" : "처리 실패 (ID를 확인하세요)\n");
    }
}

void SampleView::handleOrderMenu() {
    printSeparator();
    std::cout << "  [주문 관리]\n";
    std::cout << "  1. 주문 등록\n";
    std::cout << "  2. 주문 처리 시작\n";
    std::cout << "  3. 주문 완료\n";
    std::cout << "  4. 주문 취소\n";
    std::cout << "  0. 뒤로\n";
    printSeparator();
    std::cout << "선택 > ";

    int choice; std::cin >> choice; std::cin.ignore();
    if (choice == 0) return;

    if (choice == 1) {
        int sampleId, qty;
        std::string date;
        std::cout << "시료 ID   : "; std::cin >> sampleId;
        std::cout << "주문 수량 : "; std::cin >> qty; std::cin.ignore();
        std::cout << "주문일자 (YYYY-MM-DD): "; std::getline(std::cin, date);
        int orderId = orderCtrl_.placeOrder(sampleId, qty, date);
        std::cout << "주문 등록 완료 (주문번호: " << orderId << ")\n";
    } else {
        std::cout << "주문번호 : ";
        int orderId; std::cin >> orderId;
        bool ok = false;
        if      (choice == 2) ok = orderCtrl_.processOrder(orderId);
        else if (choice == 3) ok = orderCtrl_.fulfillOrder(orderId);
        else if (choice == 4) ok = orderCtrl_.cancelOrder(orderId);
        std::cout << (ok ? "처리 완료\n" : "처리 실패 (주문번호를 확인하세요)\n");
    }
}

void SampleView::handleViewMenu() {
    printSeparator();
    std::cout << "  [조회]\n";
    std::cout << "  1. 전체 시료 목록\n";
    std::cout << "  2. 시료 상세 조회\n";
    std::cout << "  3. 상태별 시료 조회\n";
    std::cout << "  4. 전체 주문 목록\n";
    std::cout << "  0. 뒤로\n";
    printSeparator();
    std::cout << "선택 > ";

    int choice; std::cin >> choice;
    if (choice == 0) return;
    if      (choice == 1) showAllSamples();
    else if (choice == 2) { std::cout << "시료 ID : "; int id; std::cin >> id; showSampleDetail(id); }
    else if (choice == 3) showSamplesByStatus();
    else if (choice == 4) showAllOrders();
}

void SampleView::showAllSamples() const {
    auto samples = model_.getAllSamples();
    printSeparator();
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(16) << "시료명"
              << std::setw(16) << "Lot번호"
              << std::setw(14) << "공정유형"
              << std::setw(8)  << "수량"
              << "상태\n";
    printSeparator();
    for (const auto& s : samples) {
        std::cout << std::left
                  << std::setw(6)  << s.id
                  << std::setw(16) << s.name
                  << std::setw(16) << s.waferLot
                  << std::setw(14) << s.processType
                  << std::setw(8)  << s.quantity
                  << sampleStatusToString(s.status) << "\n";
    }
    if (samples.empty()) std::cout << "등록된 시료가 없습니다.\n";
}

void SampleView::showSampleDetail(int id) const {
    auto opt = model_.findSampleById(id);
    if (!opt) { std::cout << "해당 시료를 찾을 수 없습니다.\n"; return; }
    const auto& s = *opt;
    printSeparator();
    std::cout << "  [시료 상세 정보]\n";
    std::cout << "  ID        : " << s.id << "\n";
    std::cout << "  시료명    : " << s.name << "\n";
    std::cout << "  Lot 번호  : " << s.waferLot << "\n";
    std::cout << "  공정 유형 : " << s.processType << "\n";
    std::cout << "  수량      : " << s.quantity << "\n";
    std::cout << "  상태      : " << sampleStatusToString(s.status) << "\n";
    auto orders = model_.getOrdersBySampleId(id);
    std::cout << "  주문 수   : " << orders.size() << "건\n";
    printSeparator();
}

void SampleView::showSamplesByStatus() const {
    std::cout << "상태 선택 (0:대기 1:생산중 2:품질검사 3:완료 4:출하 5:취소): ";
    int s; std::cin >> s;
    if (s < 0 || s > 5) { std::cout << "잘못된 입력입니다.\n"; return; }
    auto status  = static_cast<SampleStatus>(s);
    auto samples = model_.getSamplesByStatus(status);
    printSeparator();
    std::cout << "  [" << sampleStatusToString(status) << " 시료 목록]\n";
    printSeparator();
    for (const auto& sample : samples)
        std::cout << "  ID: " << sample.id << " | " << sample.name
                  << " | Lot: " << sample.waferLot << " | 수량: " << sample.quantity << "\n";
    if (samples.empty()) std::cout << "해당 상태의 시료가 없습니다.\n";
}

void SampleView::showAllOrders() const {
    auto orders = model_.getAllOrders();
    printSeparator();
    std::cout << std::left
              << std::setw(10) << "주문번호"
              << std::setw(10) << "시료ID"
              << std::setw(10) << "수량"
              << std::setw(14) << "주문일자"
              << "상태\n";
    printSeparator();
    for (const auto& o : orders) {
        std::cout << std::left
                  << std::setw(10) << o.orderId
                  << std::setw(10) << o.sampleId
                  << std::setw(10) << o.quantity
                  << std::setw(14) << o.orderDate
                  << orderStatusToString(o.status) << "\n";
    }
    if (orders.empty()) std::cout << "등록된 주문이 없습니다.\n";
}

std::string SampleView::sampleStatusToString(SampleStatus status) const {
    switch (status) {
    case SampleStatus::Pending:      return "대기";
    case SampleStatus::InProduction: return "생산중";
    case SampleStatus::QualityCheck: return "품질검사";
    case SampleStatus::Completed:    return "완료";
    case SampleStatus::Shipped:      return "출하";
    case SampleStatus::Cancelled:    return "취소";
    default:                         return "알수없음";
    }
}

std::string SampleView::orderStatusToString(OrderStatus status) const {
    switch (status) {
    case OrderStatus::Received:   return "접수";
    case OrderStatus::Processing: return "처리중";
    case OrderStatus::Fulfilled:  return "완료";
    case OrderStatus::Cancelled:  return "취소";
    default:                      return "알수없음";
    }
}

void SampleView::printSeparator() const {
    std::cout << "========================================\n";
}
