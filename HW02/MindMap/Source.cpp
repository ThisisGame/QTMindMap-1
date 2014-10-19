#include <iostream>
#include "TextUIView.h"
#include "MindMapModel.h"
using namespace std;

int main()
{
    MindMapModel* model = new MindMapModel();
    TextUIView* view = new TextUIView(model);
    view->run();
    system("PAUSE");
    return 0;
}