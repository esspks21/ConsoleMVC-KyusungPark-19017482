#pragma once
#include "../Model/SampleModel.h"
#include "../Controller/ProductionController.h"
#include "../Controller/OrderController.h"

class SampleView {
public:
    SampleView(SampleModel& model, ProductionController& productionCtrl,
               OrderController& orderCtrl);
    void run();

private:
    void showMainMenu() const;
    void handleProductionMenu();
    void handleOrderMenu();
    void handleViewMenu();

    void showAllSamples() const;
    void showSampleDetail(int id) const;
    void showSamplesByStatus() const;
    void showAllOrders() const;

    std::string sampleStatusToString(SampleStatus status) const;
    std::string orderStatusToString(OrderStatus status) const;
    void printSeparator() const;

    SampleModel&          model_;
    ProductionController& productionCtrl_;
    OrderController&      orderCtrl_;
};
