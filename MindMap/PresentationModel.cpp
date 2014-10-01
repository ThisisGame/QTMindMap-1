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

string PresentationModel::getMessage() //���o�r��T��
{
    string message = _message;
    _message = EMPTY_STRING;
    return message;
}

void PresentationModel::selectMode(char mode)  //�]�w�Ҧ�
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

void PresentationModel::insertMode(char mode)  //��ܴ��JNode�Ҧ��A���b�P�_
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

void PresentationModel::updateMode()  //��sMode�Ҧ��A�P�_�O�_�w���Component
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

void PresentationModel::display()  //��X���
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

void PresentationModel::saveMindMap()  //�x�sMindmap
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

void PresentationModel::setMessage(string messange) //�]�w���~�T��
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