#include "ProductionController.h"

ProductionController::ProductionController(SampleModel& model) : model_(model) {}

int ProductionController::registerSample(const std::string& name, const std::string& waferLot,
                                          const std::string& processType, int quantity) {
    return model_.addSample(name, waferLot, processType, quantity);
}

bool ProductionController::startProduction(int sampleId) {
    return model_.updateSampleStatus(sampleId, SampleStatus::InProduction);
}

bool ProductionController::completeQualityCheck(int sampleId) {
    return model_.updateSampleStatus(sampleId, SampleStatus::QualityCheck);
}

bool ProductionController::completeProduction(int sampleId) {
    return model_.updateSampleStatus(sampleId, SampleStatus::Completed);
}

bool ProductionController::shipSample(int sampleId) {
    return model_.updateSampleStatus(sampleId, SampleStatus::Shipped);
}

bool ProductionController::cancelProduction(int sampleId) {
    return model_.updateSampleStatus(sampleId, SampleStatus::Cancelled);
}
