#include "Model/SampleModel.h"
#include "Controller/ProductionController.h"
#include "Controller/OrderController.h"
#include "View/SampleView.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    SampleModel          model;
    ProductionController productionCtrl(model);
    OrderController      orderCtrl(model);
    SampleView           view(model, productionCtrl, orderCtrl);

    view.run();
    return 0;
}
