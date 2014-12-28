#include "AddDecoratorCommand.h"

AddDecoratorCommand::AddDecoratorCommand(Component* component, Component* decorator, MindMapModel* model)
{
    _component = component->getDecorator();
    _decorator = decorator;
    _oldParent = _component->getParent();
    _model = model;
}

AddDecoratorCommand::~AddDecoratorCommand()
{
    delete _decorator;
}

void AddDecoratorCommand::execute()
{
    _component->addDecorator(_decorator);
    _model->doInsertNode(_decorator);
}

void AddDecoratorCommand::unexcute()
{
    if (_oldParent != NULL)
    {
        _oldParent->deleteNodeByNode(_decorator);
        _oldParent->addChild(_component);
    }
    else
    {
        _component->setParent(NULL);
    }
    _model->doUninsertNode(_decorator);
}