#include "CutNodeCommand.h"

CutNodeCommand::CutNodeCommand(Component* component, MindMapModel* model)
{
    _component = component;
    _model = model;
    _parent = component->getParent();
    _oldNodeList = _model->getNodeList();
    _oldParentList = _parent->getNodeList();
}

CutNodeCommand::~CutNodeCommand()
{
}

void CutNodeCommand::execute()
{
    _model->doCutNodes(_component);
    _parent->deleteNodeByNode(_component);
}

void CutNodeCommand::unexcute()
{
    _parent->clearNodeList();
    _parent->addChilds(_oldParentList);
    _model->doAddNodes(_oldNodeList);
}