#include "InsertSiblingCommand.h"

InsertSiblingCommand::InsertSiblingCommand(Component* component, Component* sibling, MindMapModel* model)
{
    _component = component;
    _sibling = sibling;
    _parent = _component->getParent();
    _model = model;
}

InsertSiblingCommand::~InsertSiblingCommand()
{
    delete _sibling;
}

void InsertSiblingCommand::execute()
{
    _component->addSibling(_sibling);
    _model->doInsertNode(_sibling);
}

void InsertSiblingCommand::unexcute()
{
    _parent->deleteNodeByNode(_sibling);
    _model->doUninsertNode(_sibling);
}