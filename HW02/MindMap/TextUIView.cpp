#include "TextUIView.h"

TextUIView::TextUIView()  //初始化
{
    _model = new MindMapModel();
    _pModel = new PresentationModel(_model);
    _functionList[ROOT_MODE] = &TextUIView::selectMode;
    //功能一-新建MindMap
    _functionList[CREATE_NEW_MINDMAP_MODE] = &TextUIView::createNewMindMap;
    //功能二-插入Node
    _functionList[INSERT_NEW_NODE_MODE] = &TextUIView::insertNewNode;
    _functionList[SELECT_INSERT_MODE] = &TextUIView::selectInsertMode;
    _functionList[ENTER_NODE_NAME_MODE] = &TextUIView::enterNodeName;
    //功能三-修改Node
    _functionList[EDIT_NODE_MODE] = &TextUIView::editMode;
    _functionList[SELECT_EDIT_MODE] = &TextUIView::selectEditMode;
    _functionList[CHANGE_DESCTIPTION_MODE] = &TextUIView::changeDescription;
    _functionList[CHANGE_PARENT_MODE] = &TextUIView::changeParent;
    //功能四-顯示MindMap
    _functionList[DISPLAY_MODE] = &TextUIView::display;
    //功能五-儲存MindMap
    _functionList[SAVE_MIND_MAP_MODE] = &TextUIView::saveMindMap;
    //功能六-讀取MindMap
    _functionList[LOAD_MIND_MAP_MODE] = &TextUIView::loadMindMap;
    //功能七-取消復原
    _functionList[REDO_MODE] = &TextUIView::redo;
    //功能八-復原
    _functionList[UNDO_MODE] = &TextUIView::undo;
    //功能九-離開
    _functionList[EXIT_MODE] = &TextUIView::exitMode;
    //共用功能
    _functionList[MESSANGE_MODE] = &TextUIView::messangeMode;
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

string TextUIView::inputString() //字串輸入
{
    string inputString;
    getline(cin, inputString);
    fflush(stdin);
    cout << endl;
    return inputString;
}

char TextUIView::inputChar()  //字元輸入
{
    return inputString()[0];
}

void TextUIView::selectId(string outputString)
{
    cout << outputString << endl << PROMPT_STRING;
    _model->selectComponent(atoi(inputString().c_str()));
    _pModel->updateMode();
    (this->*(_functionList[_pModel->getMode()]))();
}

void TextUIView::enterDescrption(string outputString, int mode)
{
    cout << outputString << endl << PROMPT_STRING;
    _pModel->setDescription(inputString(), mode);
    display();
}

void TextUIView::selectMode() //模式選擇
{
    cout << "Please enter your choice :" << endl;
    cout << "1. Create a new mind map" << endl;
    cout << "2. Insert a new node" << endl;
    cout << "3. Edit a node" << endl;
    cout << "4. Display mind map" << endl;
    cout << "5. Save mind map" << endl;
    cout << "6. Load mind map" << endl;
    cout << "7. Redo" << endl;
    cout << "8. Undo" << endl;
    cout << "9. Exit" << endl << PROMPT_STRING;
    _pModel->selectMode(inputChar());
    messangeMode();
    (this->*(_functionList[_pModel->getMode()]))();
}

//功能一
void TextUIView::createNewMindMap()  //新建一個MindMap
{
    enterDescrption("Please enter the topic :", CREATE_NEW_MINDMAP_MODE);
}

//功能二
void TextUIView::insertNewNode()  //新增Node
{
    display();
    selectId("Enter the node ID:");
}

void TextUIView::selectInsertMode()  //選擇插入模式
{
    cout << "a.Insert a parent node" << endl;
    cout << "b.Insert a child node" << endl;
    cout << "c.Insert a sibling node" << endl << PROMPT_STRING;
    _pModel->insertMode(inputChar());
    messangeMode();
    (this->*(_functionList[_pModel->getMode()]))();
}

void TextUIView::enterNodeName() //輸入NodeName
{
    enterDescrption("Enter the node name:", ENTER_NODE_NAME_MODE);
}

//功能三
void TextUIView::editMode()  //編輯node
{
    display();
    selectId("Enter the edit node ID:");
}

void TextUIView::selectEditMode()
{
    cout << "a.Edit the description of a node" << endl;
    cout << "b.Change the parent of a node" << endl;
    cout << "c.Delete a node" << endl << PROMPT_STRING;
    _pModel->editMode(inputChar());
    messangeMode();
    (this->*(_functionList[_pModel->getMode()]))();
}

void TextUIView::changeDescription()
{
    enterDescrption("Enter the description:", CHANGE_DESCTIPTION_MODE);
}

void TextUIView::changeParent()
{
    selectId("Enter the parent ID:");
}

//功能四
void TextUIView::display() //顯示心智圖
{
    _pModel->display();
    messangeMode();
}

//功能五
void TextUIView::saveMindMap() //儲存心智圖
{
    _pModel->saveMindMap();
    messangeMode();
}

//功能六
void TextUIView::loadMindMap() //讀取心智圖
{
    _pModel->loadMindMap();
    messangeMode();
}

//功能七
void TextUIView::redo()
{
    _pModel->redo();
    messangeMode();
}

//功能八
void TextUIView::undo()
{
    _pModel->undo();
    messangeMode();
}

//功能九
void TextUIView::exitMode() //結束程式
{
    cout << "Do you want save your mindMap?(Y/N)" << endl << PROMPT_STRING;
    _pModel->exitMode(inputChar());
    messangeMode();
    exit(1);
}


void TextUIView::messangeMode() //訊息顯示
{
    cout << _pModel->getMessage();
}