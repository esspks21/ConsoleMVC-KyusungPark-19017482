#pragma once
#include "../Model/SampleModel.h"
#include <string>
#include <vector>

class OrderController {
public:
    explicit OrderController(SampleModel& model);

    int  placeOrder(int sampleId, int quantity, const std::string& orderDate);
    bool processOrder(int orderId);
    bool fulfillOrder(int orderId);
    bool cancelOrder(int orderId);
    std::vector<Order> getOrdersForSample(int sampleId) const;

private:
    SampleModel& model_;
};
