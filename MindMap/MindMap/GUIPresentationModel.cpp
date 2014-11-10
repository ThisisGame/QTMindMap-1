#include "GUIPresentationModel.h"


GUIPresentationModel::GUIPresentationModel(MindMapModel* model)
{
    _model = model;
    _saveMindMapActionEnable = false;
    disableAction();
}

GUIPresentationModel::~GUIPresentationModel()
{
}

bool GUIPresentationModel::getSaveMindMapActionEnable()
{
    return _saveMindMapActionEnable;
}

bool GUIPresentationModel::getEditNodeActionEnable()
{
    return _editNodeActionEnable;
}

bool GUIPresentationModel::getDeleteNodeActionEnable()
{
    return _deleteNodeActionEnable;
}

bool GUIPresentationModel::getInsertChildActionEnable()
{
    return _insertChildActionEnable;
}

bool GUIPresentationModel::getInsertSiblingActionEnable()
{
    return _insertSiblingActionEnable;
}

bool GUIPresentationModel::getInsertParentActionEnable()
{
    return _insertParentActionEnable;
}

Subject* GUIPresentationModel::getSubject()
{
    return this;
}


void GUIPresentationModel::loadMindMap(string filename)  //讀取Mindmap
{
    try
    {
        _model->loadMindMap(filename);
        _model->display();
        _message = _model->getMessage();
        _saveMindMapActionEnable = true;
        notifyUpdateView();
    }
    catch (const char* message)
    {
        _message = message;
    }
}

void GUIPresentationModel::saveMindMap(string filename)  //讀取Mindmap
{
    try
    {
        _model->saveMindMap(filename);
    }
    catch (const char* message)
    {
        _message = message;
        notifyUpdateError();
    }
}

string GUIPresentationModel::getMessage() //取得字串訊息
{
    string message = _message;
    _message = EMPTY_STRING;
    return message;
}

void GUIPresentationModel::draw(MindMapGUIScene* scene)
{
    _model->draw(scene);
}

void GUIPresentationModel::selectComponent(int id)
{
    _model->selectComponent(id);
    disableAction();
    _insertChildActionEnable = true;
    _editNodeActionEnable = true;
    if (!_model->isRoot())
    {
        _deleteNodeActionEnable = true;
        _insertSiblingActionEnable = true;
        _insertParentActionEnable = true;
    }
    notifyUpdateView();
}

void GUIPresentationModel::editDescription(string description)
{
    if (description == "")
    {
        _message = "You Inputed Empty String!";
        notifyUpdateError();
    }
    else
    {
        _model->changeDescription(description);
        notifyUpdateView();
    }
}

void GUIPresentationModel::createMindMap(string topic)
{
    if (topic == "")
    {
        _message = "You Inputed Empty String!";
        notifyUpdateError();
    }
    else
    {
        _model->createMindMap(topic);
        _saveMindMapActionEnable = true;
        notifyUpdateView();
    }
}

void GUIPresentationModel::deleteComponent()
{
    _model->deleteComponent();
    disableAction();
    notifyUpdateView();
}

void GUIPresentationModel::insertNode(char mode, string description)
{
    if (description == "")
    {
        _message = "You Inputed Empty String!";
        notifyUpdateError();
    }
    else
    {
        _model->insertNode(mode);
        _model->setDescription(description);
        notifyUpdateView();
    }
}

void GUIPresentationModel::disableSelected()
{
    _model->disableSelected();
    disableAction();
    notifyUpdateView();
}

void GUIPresentationModel::disableAction()
{
    _editNodeActionEnable = false;
    _deleteNodeActionEnable = false;
    _insertChildActionEnable = false;
    _insertSiblingActionEnable = false;
    _insertParentActionEnable = false;
}