#include "OrderController.h"

OrderController::OrderController(SampleModel& model) : model_(model) {}

int OrderController::placeOrder(int sampleId, int quantity, const std::string& orderDate) {
    return model_.addOrder(sampleId, quantity, orderDate);
}

bool OrderController::processOrder(int orderId) {
    return model_.updateOrderStatus(orderId, OrderStatus::Processing);
}

bool OrderController::fulfillOrder(int orderId) {
    return model_.updateOrderStatus(orderId, OrderStatus::Fulfilled);
}

bool OrderController::cancelOrder(int orderId) {
    return model_.cancelOrder(orderId);
}

std::vector<Order> OrderController::getOrdersForSample(int sampleId) const {
    return model_.getOrdersBySampleId(sampleId);
}
