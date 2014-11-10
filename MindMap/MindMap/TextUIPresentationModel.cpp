#include "TextUIPresentationModel.h"

TextUIPresentationModel::TextUIPresentationModel()
{
}

TextUIPresentationModel::TextUIPresentationModel(MindMapModel* model)
{
    _mode = ROOT_MODE;
    _model = model;
}

TextUIPresentationModel::~TextUIPresentationModel()
{
}

int TextUIPresentationModel::getMode()
{
    return _mode;
}

string TextUIPresentationModel::getMessage() //���o�r��T��
{
    string message = _message;
    _message = EMPTY_STRING;
    return message;
}

void TextUIPresentationModel::selectMode(char mode)  //�]�w�Ҧ�
{
    if (mode == '1')
    {
        setMode(CREATE_NEW_MINDMAP_MODE);
    }
    else if (mode == '2')
    {
        setMode(INSERT_NEW_NODE_MODE);
    }
    else if (mode == '3')
    {
        setMode(EDIT_NODE_MODE);
    }
    else if (mode == '4')
    {
        setMode(DISPLAY_MODE);
    }
    else if (mode == '5')
    {
        setMode(SAVE_MIND_MAP_MODE);
    }
    else if (mode == '6')
    {
        setMode(LOAD_MIND_MAP_MODE);
    }
    else if (mode == '7')
    {
        setMode(REDO_MODE);
    }
    else if (mode == '8')
    {
        setMode(UNDO_MODE);
    }
    else if (mode == '9')
    {
        setMode(EXIT_MODE);
    }
    else
    {
        setMessage(ERROR_INPUT_COMMAND);
    }
}

void TextUIPresentationModel::setDescription(string description, int mode)
{
    if (mode == CREATE_NEW_MINDMAP_MODE)
    {
        _model->createMindMap(description);
    }
    else if (mode == ENTER_NODE_NAME_MODE)
    {
        _model->setDescription(description);
    }
    else if (mode == CHANGE_DESCTIPTION_MODE)
    {
        _model->changeDescription(description);
    }
}

//�\��G
void TextUIPresentationModel::insertMode(char mode)  //��ܴ��JNode�Ҧ��A���b�P�_
{
    if (mode == 'a' || mode == 'b' || mode == 'c')
    {
        try
        {
            _model->insertNode(mode);
            setMode(ENTER_NODE_NAME_MODE);
        }
        catch (const char* message)
        {
            _message = message;
        }
    }
    else
    {
        _message = ERROR_INPUT_COMMAND;
    }
}

//�\��T
void TextUIPresentationModel::editMode(char mode)  //��ܽs��Node�Ҧ��A���b�P�_
{
    if (mode == 'a')
    {
        setMode(CHANGE_DESCTIPTION_MODE);
    }
    else if (mode == 'b')
    {
        if (_model->isRoot())
        {
            setMessage(ERROR_ROOT_CHANGE_PARENT);
            return;
        }
        setMode(CHANGE_PARENT_MODE);
    }
    else if (mode == 'c')
    {
        if (_model->isRoot())
        {
            setMessage(ERROR_ROOT_DELETE);
            return;
        }
        _model->deleteComponent();
        display();
        setMode(MESSANGE_MODE);
    }
    else
    {
        _message = ERROR_INPUT_COMMAND;
    }
}

//���NODE�ɧP�_�O�_�����
void TextUIPresentationModel::selectComponent(string idString)  //��sMode�Ҧ��A�P�_�O�_�w���Component
{
    int id = atoi(idString.c_str());
    char firstchar = idString[0];
    if (!(firstchar >= '0' && firstchar <= '9'))
    {
        setMessage(ERROR_INPUT_CHAR);
    }
    else if (_mode != CHANGE_PARENT_MODE && _model->selectComponent(id) == false)
    {
        _message = ERROR_SELECT_NODE;
    }
    else if (_mode == INSERT_NEW_NODE_MODE)
    {
        setMode(SELECT_INSERT_MODE);
    }
    else if (_mode == EDIT_NODE_MODE)
    {
        setMode(SELECT_EDIT_MODE);
    }
    else if (_mode == CHANGE_PARENT_MODE)
    {
        try
        {
            _model->changeParent(id);
            display();
            setMode(MESSANGE_MODE);
        }
        catch (const char* message)
        {
            _message = message;
        }
    }
}

void TextUIPresentationModel::display()  //��X���
{
    try
    {
        _model->display();
        _message = _model->getMessage();
    }
    catch (const char* message)
    {
        setMessage(message);
    }
}

void TextUIPresentationModel::loadMindMap(string filename)  //Ū��Mindmap
{
    try
    {
        _model->loadMindMap(filename);
        display();
    }
    catch (const char* message)
    {
        setMessage(message);
    }
}

void TextUIPresentationModel::saveMindMap(string filename)  //�x�sMindmap
{
    try
    {
        _model->saveMindMap(filename);
        _message = _model->getMessage();
    }
    catch (const char* message)
    {
        setMessage(message);
    }
}

void TextUIPresentationModel::redo()
{
    try
    {
        _model->redo();
        display();
    }
    catch (const char* message)
    {
        setMessage(message);
    }
}

void TextUIPresentationModel::undo()
{
    try
    {
        _model->undo();
        display();
    }
    catch (const char* message)
    {
        setMessage(message);
    }
}


void TextUIPresentationModel::setMessage(string messange) //�]�w���~�T��
{
    _message = messange;
    setMode(MESSANGE_MODE);
}

void TextUIPresentationModel::exitMode(char input, string filename)
{
    if (input == 'y' || input == 'Y')
    {
        saveMindMap(filename);
    }
}

void TextUIPresentationModel::setMode(int mode)
{
    _mode = mode;
}