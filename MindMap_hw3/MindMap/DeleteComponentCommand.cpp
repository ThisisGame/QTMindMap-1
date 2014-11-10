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
    _parent->addChilds(_oldChildList);
}

void DeleteComponentCommand::unexcute()
{
    _parent->clearNodeList();
    _parent->addChilds(_oldParentList);
    _component->clearNodeList();
    _component->addChilds(_oldChildList);
    _model->doAddNodes(_oldNodeList);
}
