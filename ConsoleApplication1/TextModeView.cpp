#include "TextModeView.h"

TextModeView::TextModeView()
{
    _model = new MindMapModel();
}

TextModeView::~TextModeView()
{
}

void TextModeView::run() //TextMode
{
    selectMode();
}

string TextModeView::inputString() //字串輸入
{
    string inputString;
    getline(cin, inputString);
    fflush(stdin);
    cout << endl;
    return inputString;
}

void TextModeView::selectMode() //模式選擇
{
    cout << "Please enter your choice :" << endl;
    cout << "1. Create a new mind map" << endl;
    cout << "2. Insert a new node" << endl;
    cout << "3. Display mind map" << endl;
    cout << "4. Save mind map" << endl;
    cout << "5. Exit" << endl << ">";
    selectedMode(inputString()[0]);
}

void TextModeView::selectedMode(char mode) //模式設定
{
    if (mode == '1')
    {
        createNewMindMap();
    }
    else if (mode == '2')
    {
        insertNewNode();
    }
    else if (mode == '3')
    {
        display();
    }
    else if (mode == '4')
    {
        saveMindMap();
    }
}

void TextModeView::saveMindMap()
{
    display();
    _model->saveMindMap();
    selectMode();
}

void TextModeView::createNewMindMap()  //新建心智圖
{
    string topic;
    cout << "Please enter the topic :" << endl << ">";
    _model->createMindMap(inputString());
    display();
    selectMode();
}

void TextModeView::insertNewNode()  //新建Node模式顯示
{
    string nodeName;
    cout << "Enter the node ID:" << endl << ">";
    _model->setId(inputString()[0]);
    cout << "a.Insert a parent node" << endl;
    cout << "b.Insert a child node" << endl;
    cout << "c.Insert a sibling node" << endl << ">";
    insertNewNodeMode(inputString()[0]);
    cout << "Enter the node name:" << endl << ">";
    _model->setNodeName(inputString());
    display();
    selectMode();
}

void TextModeView::insertNewNodeMode(char mode)	//新建Node位置選擇
{
    if (mode == 'a')
    {
        _model->insertParent();
    }
    else if (mode == 'b')
    {
        _model->insertChild();
    }
    else if (mode == 'c')
    {
        _model->insertSibling();
    }
}

void TextModeView::display() //顯示心智圖
{
    cout << "The mind map Computer is displayed as follows:" << endl;
    _model->display();
    cout << endl;
}