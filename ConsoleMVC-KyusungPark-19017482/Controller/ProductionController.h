#pragma once
#include "../Model/SampleModel.h"
#include <string>

class ProductionController {
public:
    explicit ProductionController(SampleModel& model);

    int  registerSample(const std::string& name, const std::string& waferLot,
                        const std::string& processType, int quantity);
    bool startProduction(int sampleId);
    bool completeQualityCheck(int sampleId);
    bool completeProduction(int sampleId);
    bool shipSample(int sampleId);
    bool cancelProduction(int sampleId);

private:
    SampleModel& model_;
};
