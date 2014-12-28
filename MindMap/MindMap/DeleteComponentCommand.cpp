#include "DeleteComponentCommand.h"

DeleteComponentCommand::DeleteComponentCommand(Component* component, MindMapModel* model)
{
    _component = component;
    _decorator = component->getDecorator();
    _model = model;
    _parent = _decorator->getParent();
    _oldChildList = _component->getNodeList();
    _oldNodeList = _model->getNodeList();
    _oldParentList = _parent->getNodeList();
}

DeleteComponentCommand::~DeleteComponentCommand()
{
}

void DeleteComponentCommand::execute()
{
    _parent->deleteNodeByNode(_decorator);
    _parent->addChilds(_oldChildList);
    _component->clearNodeList();
    _model->doCutNodes(_decorator);
}

void DeleteComponentCommand::unexcute()
{
    _parent->clearNodeList();
    _parent->addChilds(_oldParentList);
    _component->addChilds(_oldChildList);
    _model->doAddNodes(_oldNodeList);
}
