#include "Model/SampleModel.h"
#include "Controller/ProductionController.h"
#include "Controller/OrderController.h"
#include "View/SampleView.h"

int main() {
    SampleModel          model;
    ProductionController productionCtrl(model);
    OrderController      orderCtrl(model);
    SampleView           view(model, productionCtrl, orderCtrl);

    view.run();
    return 0;
}
