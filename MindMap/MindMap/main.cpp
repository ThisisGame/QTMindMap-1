
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
    cout << "Please input \"textuimode\" to run textUI, otherwise will run GUI\n>";
    string mode;
    cin >> mode;
    fflush(stdin);
    if (mode == "textuimode")
    {
        TextUIView* view = new TextUIView(model);
        view->run();
        return a.exec();
    }
    MindMapGUIView mindMapGUI(model);
    mindMapGUI.show();
    return a.exec();
}
