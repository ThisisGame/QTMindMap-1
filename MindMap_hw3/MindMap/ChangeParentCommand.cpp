#include "ChangeParentCommand.h"
#include "ConstString.h"

ChangeParentCommand::ChangeParentCommand(Component* child, Component* newParent)
{
    _newParent = newParent;
    _child = child;
    _oldParent = child->getParent();
}

ChangeParentCommand::~ChangeParentCommand()
{
}

void ChangeParentCommand::execute()
{
    if (_child == _newParent)
    {
        throw ERROR_SELECT_ITSELF;
    }
    else if (_newParent == NULL)
    {
        throw ERROR_SELECT_NODE;
    }
    _isParent = _newParent->isParent(_child);
    if (!_isParent)
    {
        _oldParentList = _oldParent->getNodeList();
        _oldParent->deleteNodeByNode(_child);
        _newParent->addChild(_child);
    }
    else
    {
        _childrenList = _child->getNodeList();
        _oldParentList = _oldParent->getNodeList();
        _oldParent->deleteNodeByNode(_child);
        _oldParent->addChilds(_childrenList);
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
        _child->addChilds(_childrenList);
        _oldParent->clearNodeList();
        _oldParent->addChilds(_oldParentList);
        _newParent->deleteNodeByNode(_child);
    }
}
