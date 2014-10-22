#include "InsertChildCommand.h"

InsertChildCommand::InsertChildCommand(Component* component, Component* child, MindMapModel* model)
{
    _component = component;
    _child = child;
    _model = model;
}

InsertChildCommand::~InsertChildCommand()
{
    delete _child;
}

void InsertChildCommand::deleteCommand()
{
}

void InsertChildCommand::execute()
{
    _component->addChild(_child);
    _model->doInsertNode(_child);
}

void InsertChildCommand::unexcute()
{
    _component->deleteNodeByNode(_child);
    _model->doUninsertNode(_child);
}