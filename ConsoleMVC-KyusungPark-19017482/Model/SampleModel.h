#pragma once
#include "Sample.h"
#include "Order.h"
#include <vector>
#include <optional>

class SampleModel {
public:
    int  addSample(const std::string& name, const std::string& waferLot,
                   const std::string& processType, int quantity);
    bool updateSampleStatus(int id, SampleStatus status);
    bool deleteSample(int id);
    std::optional<Sample>      findSampleById(int id) const;
    std::vector<Sample>        getAllSamples() const;
    std::vector<Sample>        getSamplesByStatus(SampleStatus status) const;

    int  addOrder(int sampleId, int quantity, const std::string& orderDate);
    bool updateOrderStatus(int orderId, OrderStatus status);
    bool cancelOrder(int orderId);
    std::optional<Order>       findOrderById(int orderId) const;
    std::vector<Order>         getAllOrders() const;
    std::vector<Order>         getOrdersBySampleId(int sampleId) const;

private:
    std::vector<Sample> samples_;
    std::vector<Order>  orders_;
    int nextSampleId_ = 1;
    int nextOrderId_  = 1;
};
