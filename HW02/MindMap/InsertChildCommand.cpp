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
    _model->doInsertChild(_component, _child);
}

void InsertChildCommand::unexcute()
{
    _model->doDeleteChild(_component, _child);
}