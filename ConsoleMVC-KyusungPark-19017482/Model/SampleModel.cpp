#include "SampleModel.h"
#include <algorithm>

int SampleModel::addSample(const std::string& name, const std::string& waferLot,
                            const std::string& processType, int quantity) {
    Sample s{ nextSampleId_++, name, waferLot, processType, quantity, SampleStatus::Pending };
    samples_.push_back(s);
    return s.id;
}

bool SampleModel::updateSampleStatus(int id, SampleStatus status) {
    for (auto& s : samples_) {
        if (s.id == id) { s.status = status; return true; }
    }
    return false;
}

bool SampleModel::deleteSample(int id) {
    auto it = std::remove_if(samples_.begin(), samples_.end(),
                             [id](const Sample& s) { return s.id == id; });
    if (it == samples_.end()) return false;
    samples_.erase(it, samples_.end());
    return true;
}

std::optional<Sample> SampleModel::findSampleById(int id) const {
    for (const auto& s : samples_)
        if (s.id == id) return s;
    return std::nullopt;
}

std::vector<Sample> SampleModel::getAllSamples() const { return samples_; }

std::vector<Sample> SampleModel::getSamplesByStatus(SampleStatus status) const {
    std::vector<Sample> result;
    for (const auto& s : samples_)
        if (s.status == status) result.push_back(s);
    return result;
}

int SampleModel::addOrder(int sampleId, int quantity, const std::string& orderDate) {
    Order o{ nextOrderId_++, sampleId, quantity, orderDate, OrderStatus::Received };
    orders_.push_back(o);
    return o.orderId;
}

bool SampleModel::updateOrderStatus(int orderId, OrderStatus status) {
    for (auto& o : orders_) {
        if (o.orderId == orderId) { o.status = status; return true; }
    }
    return false;
}

bool SampleModel::cancelOrder(int orderId) {
    return updateOrderStatus(orderId, OrderStatus::Cancelled);
}

std::optional<Order> SampleModel::findOrderById(int orderId) const {
    for (const auto& o : orders_)
        if (o.orderId == orderId) return o;
    return std::nullopt;
}

std::vector<Order> SampleModel::getAllOrders() const { return orders_; }

std::vector<Order> SampleModel::getOrdersBySampleId(int sampleId) const {
    std::vector<Order> result;
    for (const auto& o : orders_)
        if (o.sampleId == sampleId) result.push_back(o);
    return result;
}
