#include "GUIPresentationModel.h"


GUIPresentationModel::GUIPresentationModel(MindMapModel* model)
{
    _model = model;
    _saveMindMapActionEnable = false;
    _pasteActionEnable = false;
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

bool GUIPresentationModel::getCopyActionEnbale()
{
    return _copyActionEnbale;
}

bool GUIPresentationModel::getCutActionEnbale()
{
    return _cutActionEnbale;
}

bool GUIPresentationModel::getPasteActionEnable()
{
    return _pasteActionEnable;
}

bool GUIPresentationModel::getRedoActionEnable()
{
    return _model->IsCanRedo();
}

bool GUIPresentationModel::getUndoActionEnable()
{
    return _model->IsCanUedo();
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
        disableAction();
        _pasteActionEnable = false;
        _saveMindMapActionEnable = true;
        notifyUpdateView();
    }
    catch (const char* message)
    {
        _message = message;
    }
}

void GUIPresentationModel::saveMindMap(string filename)  //儲存Mindmap
{
    try
    {
        if (filename != "")
        {
            _model->saveMindMap(filename);
        }
        else
        {
            _message = ERROR_OPEN_FILE;
        }
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
        _cutActionEnbale = true;
        _copyActionEnbale = true;
    }
    notifyUpdateView();
}

void GUIPresentationModel::deleteComponent()
{
    _model->deleteComponent();
    disableAction();
    notifyUpdateView();
}

bool GUIPresentationModel::checkString(string description, bool cancel)
{
    bool result = true;
    if (cancel == false)
    {
        result = false;
    }
    else if (description == "")
    {
        _message = "You Inputed Empty String!";
        notifyUpdateError();
        result = false;
    }
    return result;
}

void GUIPresentationModel::editDescription(string description, bool cancel)
{
    if (checkString(description, cancel))
    {
        _model->changeDescription(description);
        notifyUpdateView();
    }
}

void GUIPresentationModel::createMindMap(string topic, bool cancel)
{
    if (checkString(topic, cancel))
    {
        _model->createMindMap(topic);
        _pasteActionEnable = false;
        _saveMindMapActionEnable = true;
        notifyUpdateView();
    }
}

void GUIPresentationModel::insertNode(char mode, string description, bool cancel)
{
    if(checkString(description, cancel))
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
    _copyActionEnbale = false;
    _cutActionEnbale = false;
}

void GUIPresentationModel::copyComponent()
{
    _model->cloneItem();
    _pasteActionEnable = true;
    notifyUpdateView();
}

void GUIPresentationModel::cutComponent()
{
    _model->cutComponent();
    _pasteActionEnable = true;
    notifyUpdateView();
}

void GUIPresentationModel::pasteComponent()
{
    _model->pasteComponent();
    notifyUpdateView();
}

void GUIPresentationModel::redo()
{
    _model->redo();
    disableSelected();
    notifyUpdateView();
}

void GUIPresentationModel::undo()
{
    _model->undo();
    disableSelected();
    notifyUpdateView();
}