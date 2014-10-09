#include "DeleteComponentCommand.h"

DeleteComponentCommand::DeleteComponentCommand(Component* component, MindMapModel* model)
{
    _component = component;
    _model = model;
    _parent = _component->getParent();
    _oldChildList = _component->getNodeList();
    _oldNodeList = _model->getNodeList();
    _oldParentList = _parent->getNodeList();
}

DeleteComponentCommand::~DeleteComponentCommand()
{
}

void DeleteComponentCommand::execute()
{
    _model->doDeleteNode(_component);
    _parent->deleteNodeByNode(_component);
    for (auto child : _oldChildList)
    {
        _parent->addChild(child);
    }
}

void DeleteComponentCommand::unexcute()
{
    _parent->clearNodeList();
    _component->clearNodeList();
    for (auto child : _oldParentList)
    {
        _parent->addChild(child);
    }
    for (auto child : _oldChildList)
    {
        _component->addChild(child);
    }
    _model->doAddNodes(_oldNodeList);
}
