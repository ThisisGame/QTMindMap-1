#include "TextUIView.h"

TextUIView::TextUIView()  //��l��
{
    _model = new MindMapModel();
    _pModel = new PresentationModel(_model);
    _functionList[ROOT_MODE] = &TextUIView::selectMode;
    //�\��@-�s��MindMap
    _functionList[CREATE_NEW_MINDMAP_MODE] = &TextUIView::createNewMindMap;
    //�\��G-���JNode
    _functionList[INSERT_NEW_NODE_MODE] = &TextUIView::insertNewNode;
    _functionList[SELECT_INSERT_MODE] = &TextUIView::selectInsertMode;
    _functionList[ENTER_NODE_NAME_MODE] = &TextUIView::enterNodeName;
    //�\��T-�ק�Node
    _functionList[EDIT_NODE_MODE] = &TextUIView::editMode;
    _functionList[SELECT_EDIT_MODE] = &TextUIView::selectEditMode;
    _functionList[CHANGE_DESCTIPTION_MODE] = &TextUIView::changeDescription;
    _functionList[CHANGE_PARENT_MODE] = &TextUIView::changeParent;
    //�\��|-���MindMap
    _functionList[DISPLAY_MODE] = &TextUIView::display;
    //�\�भ-�x�sMindMap
    _functionList[SAVE_MIND_MAP_MODE] = &TextUIView::saveMindMap;
    //�\�ऻ-Ū��MindMap
    _functionList[LOAD_MIND_MAP_MODE] = &TextUIView::loadMindMap;
    //�\��C-�����_��
    _functionList[REDO_MODE] = &TextUIView::redo;
    //�\��K-�_��
    _functionList[UNDO_MODE] = &TextUIView::undo;
    //�\��E-���}
    _functionList[EXIT_MODE] = &TextUIView::exitMode;
    //�@�Υ\��
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

void TextUIView::selectMode() //�Ҧ����
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

//�\��@
void TextUIView::createNewMindMap()  //�s�ؤ@��MindMap
{
    enterDescrption("Please enter the topic :", CREATE_NEW_MINDMAP_MODE);
}

//�\��G
void TextUIView::insertNewNode()  //�s�WNode
{
    display();
    selectId("Enter the node ID:");
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

void TextUIView::enterNodeName() //��JNodeName
{
    enterDescrption("Enter the node name:", ENTER_NODE_NAME_MODE);
}

//�\��T
void TextUIView::editMode()  //�s��node
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

//�\��|
void TextUIView::display() //��ܤߴ���
{
    _pModel->display();
    messangeMode();
}

//�\�भ
void TextUIView::saveMindMap() //�x�s�ߴ���
{
    _pModel->saveMindMap();
    messangeMode();
}

//�\�ऻ
void TextUIView::loadMindMap() //Ū���ߴ���
{
    _pModel->loadMindMap();
    messangeMode();
}

//�\��C
void TextUIView::redo()
{
    _pModel->redo();
    messangeMode();
}

//�\��K
void TextUIView::undo()
{
    _pModel->undo();
    messangeMode();
}

//�\��E
void TextUIView::exitMode() //�����{��
{
    cout << "Do you want save your mindMap?(Y/N)" << endl << PROMPT_STRING;
    _pModel->exitMode(inputChar());
    messangeMode();
    exit(1);
}


void TextUIView::messangeMode() //�T�����
{
    cout << _pModel->getMessage();
}