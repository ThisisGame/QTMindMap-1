#include "ChangeParentCommand.h"

ChangeParentCommand::ChangeParentCommand()
{
}

ChangeParentCommand::ChangeParentCommand(Component* child, Component* newParent)
{
    _newParent = newParent;
    _child = child;
    _oldParent = child->getParent();
    _isParent = newParent->isParent(child);
}

ChangeParentCommand::~ChangeParentCommand()
{
}

void ChangeParentCommand::deleteCommand()
{
}

void ChangeParentCommand::execute()
{
    if (!_isParent)
    {
        _oldParentList = _oldParent->getNodeList();
        _oldParent->deleteNodeByNode(_child);
        _newParent->addChild(_child);
    }
    else
    {
        _oldParentList = _child->getNodeList();
        _oldParent->deleteNodeByNode(_child);
        _oldParent->addChilds(_oldParentList);
        _newParent->addChild(_child);
        _child->clearNodeList();
    }
}

void ChangeParentCommand::unexcute()
{
    if (!_isParent)
    {
        _newParent->deleteNodeByNode(_child);
        _oldParent->clearNodeList();
        _oldParent->addChilds(_oldParentList);
    }
    else
    {
        for (auto child : _oldParentList)
        {
            child->addParent(_child);
        }
        _newParent->deleteNodeByNode(_child);
    }
}
