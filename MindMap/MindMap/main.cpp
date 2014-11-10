
#include <QApplication>
#include <iostream>
#include "TextUIView.h"
#include "MindMapModel.h"
#include "MindMapGUIView.h"
using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MindMapModel* model = new MindMapModel();
    MindMapGUIView mindMapGUI(model);
    /*
    MindMapModel* model = new MindMapModel();
    TextUIView* view = new TextUIView(model);
    view->run();
    */
    mindMapGUI.show();
    return a.exec();
}
