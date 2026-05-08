#pragma once
#include <string>

enum class SampleStatus {
    Pending,
    InProduction,
    QualityCheck,
    Completed,
    Shipped,
    Cancelled
};

struct Sample {
    int id;
    std::string name;
    std::string waferLot;
    std::string processType;
    int quantity;
    SampleStatus status;
};
