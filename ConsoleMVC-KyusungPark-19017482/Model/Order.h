#pragma once
#include <string>

enum class OrderStatus {
    Received,
    Processing,
    Fulfilled,
    Cancelled
};

struct Order {
    int orderId;
    int sampleId;
    int quantity;
    std::string orderDate;
    OrderStatus status;
};
