#include "PresentationModel.h"

PresentationModel::PresentationModel()
{
}

PresentationModel::PresentationModel(MindMapModel* model)
{
    _mode = ROOT_MODE;
    _model = model;
}

PresentationModel::~PresentationModel()
{
}

int PresentationModel::getMode()
{
    return _mode;
}

string PresentationModel::getMessage() //取得字串訊息
{
    string message = _message;
    _message = EMPTY_STRING;
    return message;
}

void PresentationModel::selectMode(char mode)  //設定模式
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

void PresentationModel::setDescription(string description, int mode)
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

//功能二
void PresentationModel::insertMode(char mode)  //選擇插入Node模式，防呆判斷
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
        setMessage(ERROR_INPUT_COMMAND);
    }
}

//功能三
void PresentationModel::editMode(char mode)  //選擇編輯Node模式，防呆判斷
{
    if (mode == 'a')
    {
        setMode(CHANGE_DESCTIPTION_MODE);
    }
    else if (mode == 'b')
    {
        setMode(CHANGE_PARENT_MODE);
    }
    else if (mode == 'c')
    {
        try
        {
        }
        catch (const char* message)
        {
            _message = message;
        }
    }
    else
    {
        setMessage(ERROR_INPUT_COMMAND);
    }
}

//選擇NODE時判斷是否有選到
void PresentationModel::updateMode()  //更新Mode模式，判斷是否已選擇Component
{
    if (_model->isSelectedComponent() == false)
    {
        setMessage(ERROR_NODE_NOTFOUND);
    }
    else if (_mode == INSERT_NEW_NODE_MODE)
    {
        setMode(SELECT_INSERT_MODE);
    }
    else if (_mode == EDIT_NODE_MODE)
    {
        setMode(SELECT_EDIT_MODE);
    }
}

void PresentationModel::display()  //輸出顯示
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

void PresentationModel::loadMindMap()  //讀取Mindmap
{
    try
    {
        _model->loadMindMap();
        _message = _model->getMessage();
    }
    catch (const char* message)
    {
        setMessage(message);
    }
}

void PresentationModel::saveMindMap()  //儲存Mindmap
{
    try
    {
        _model->saveMindMap();
        _message = _model->getMessage();
    }
    catch (const char* message)
    {
        setMessage(message);
    }
}

void PresentationModel::redo()
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

void PresentationModel::undo()
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


void PresentationModel::setMessage(string messange) //設定錯誤訊息
{
    _message = messange;
    setMode(MESSANGE_MODE);
}

void PresentationModel::exitMode(char input)
{
    if (input == 'y' || input == 'Y')
    {
        saveMindMap();
    }
}

void PresentationModel::setMode(int mode)
{
    _previousMode = _mode;
    _mode = mode;
}