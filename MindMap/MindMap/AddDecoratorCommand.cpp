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
    _decorator->addChild(NULL);
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
        _oldParent->changeNodeByNode(_decorator, _component);
    }
    else
    {
        _component->setParent(NULL);
    }
    _model->doUninsertNode(_decorator);
}