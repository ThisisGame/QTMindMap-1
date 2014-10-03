#include "TextUIView.h"

TextUIView::TextUIView()  //��l��
{
    _model = new MindMapModel();
    _pModel = new PresentationModel(_model);
    _functionList[CREATE_NEW_MINDMAP_MODE] = &TextUIView::createNewMindMap;
    _functionList[INSERT_NEW_NODE_MODE] = &TextUIView::insertNewNode;
    _functionList[DISPLAY_MODE] = &TextUIView::display;
    _functionList[SAVE_MIND_MAP_MODE] = &TextUIView::saveMindMap;
    _functionList[EXIT_MODE] = &TextUIView::exitMode;
    _functionList[MESSANGE_MODE] = &TextUIView::messangeMode;
    _functionList[SELECT_INSERT_MODE] = &TextUIView::selectInsertMode;
    _functionList[ENTER_NODE_NAME_MODE] = &TextUIView::enterNodeName;
}

TextUIView::~TextUIView()
{
}

void TextUIView::run() //TextMode
{
    while (1)
    {
        selectMode();
    }
}

string TextUIView::inputString() //�r���J
{
    string inputString;
    getline(cin, inputString);
    fflush(stdin);
    cout << endl;
    return inputString;
}

char TextUIView::inputChar()  //�r����J
{
    return inputString()[0];
}

void TextUIView::selectMode() //�Ҧ����
{
    cout << "Please enter your choice :" << endl;
    cout << "1. Create a new mind map" << endl;
    cout << "2. Insert a new node" << endl;
    cout << "3. Display mind map" << endl;
    cout << "4. Save mind map" << endl;
    cout << "5. Exit" << endl << PROMPT_STRING;
    _pModel->selectMode(inputChar());
    messangeMode();
    (this->*(_functionList[_pModel->getMode()]))();
}

void TextUIView::createNewMindMap()  //�s�ؤ@��MindMap
{
    string topic;
    cout << "Please enter the topic :" << endl << PROMPT_STRING;
    _model->createMindMap(inputString());
    display();
}

void TextUIView::selectInsertMode()  //��ܴ��J�Ҧ�
{
    cout << "a.Insert a parent node" << endl;
    cout << "b.Insert a child node" << endl;
    cout << "c.Insert a sibling node" << endl << PROMPT_STRING;
    _pModel->insertMode(inputChar());
    messangeMode();
    (this->*(_functionList[_pModel->getMode()]))();
}

void TextUIView::display() //��ܤߴ���
{
    _pModel->display();
    messangeMode();
}

void TextUIView::saveMindMap() //�x�s�ߴ���
{
    _pModel->saveMindMap();
    messangeMode();
}

void TextUIView::messangeMode() //�T�����
{
    cout << _pModel->getMessage();
}

void TextUIView::exitMode() //�����{��
{
    cout << "Do you want save your mindmap?(Y/N)" << endl << PROMPT_STRING;
    _pModel->exitMode(inputChar());
    messangeMode();
    exit(1);
}

void TextUIView::insertNewNode()  //�s�WNode
{
    display();
    cout << "Enter the node ID:" << endl << PROMPT_STRING;
    _model->selectComponent(atoi(inputString().c_str()));
    _pModel->updateMode();
    (this->*(_functionList[_pModel->getMode()]))();
}

void TextUIView::enterNodeName() //��JNodeName
{
    cout << "Enter the node name:" << endl << PROMPT_STRING;
    _model->setDescription(inputString());
    display();
}