#include "ClearDecoratorCommand.h"

ClearDecoratorCommand::ClearDecoratorCommand(Component* component, MindMapModel* model)
{
    _component = component;
    _decorator = component->getDecorator();
    _model = model;
    _parent = _decorator->getParent();
    _componentParent = component->getParent();
    _oldNodeList = _model->getNodeList();
}

ClearDecoratorCommand::~ClearDecoratorCommand()
{
}

void ClearDecoratorCommand::execute()
{
    if (_parent != NULL)
    {
        _oldParentList = _parent->getNodeList();
        _parent->changeNodeByNode(_decorator, _component);
    }
    else
    {
        _componentParent = _component->getParent();
        _component->setParent(NULL);
    }
    _model->doClearDecorator(_decorator, _component);
}

void ClearDecoratorCommand::unexcute()
{
    if (_parent != NULL)
    {
        _parent->clearNodeList();
        _parent->addChilds(_oldParentList);
        _component->setParent(_componentParent);
    }
    else
    {
        _componentParent->addChild(_component);
    }
    _model->doAddNodes(_oldNodeList);
}