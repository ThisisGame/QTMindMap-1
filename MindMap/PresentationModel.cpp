#include "PresentationModel.h"

PresentationModel::PresentationModel()
{
}

PresentationModel::PresentationModel(MindMapModel* model)
{
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
        _mode = CREATE_NEW_MINDMAP_MODE;
    }
    else if (mode == '2')
    {
        _mode = INSERT_NEW_NODE_MODE;
    }
    else if (mode == '3')
    {
        _mode = DISPLAY_MODE;
    }
    else if (mode == '4')
    {
        _mode = SAVE_MIND_MAP_MODE;
    }
    else if (mode == '5')
    {
        _mode = EXIT_MODE;
    }
    else
    {
        setMessage(ERROR_INPUT_MSG);
    }
}

void PresentationModel::insertMode(char mode)  //選擇插入Node模式，防呆判斷
{
    if (mode == 'a' || mode == 'b' || mode == 'c')
    {
        try
        {
            _model->insertNode(mode);
            _mode = ENTER_NODE_NAME_MODE;
        }
        catch (const char* message)
        {
            _message = message;
        }
    }
    else
    {
        setMessage(ERROR_INPUT_MSG);
    }
}

void PresentationModel::updateMode()  //更新Mode模式，判斷是否已選擇Component
{
    if (_model->isSelectedComponent() == false)
    {
        setMessage(ERROR_INPUT_MSG);
    }
    else
    {
        _mode = SELECT_INSERT_MODE;
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

void PresentationModel::setMessage(string messange) //設定錯誤訊息
{
    _message = messange;
    _mode = MESSANGE_MODE;
}

void PresentationModel::exitMode(char input)
{
    if (input == 'y' || input == 'Y')
    {
        saveMindMap();
    }
}