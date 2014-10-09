#include "ChangeParentCommand.h"

ChangeParentCommand::ChangeParentCommand()
{
}

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
    //Case1先將父親list內的資料刪除（記住位置），再加到新的list內
    //case2將child取出來加進parent的node內，再將node加入欲加的parent內，必須存原本的parent，舊的nodelist要存起來
    _oldParentList = _oldParent->getNodeList();
    _oldParent->deleteNodeByNode(_child);
    _newParent->addChild(_child);
}

void ChangeParentCommand::unexcute()
{
    _newParent->deleteNodeByNode(_child);
    _oldParent->clearNodeList();
    for (auto child : _oldParentList)
    {
        _oldParent->addChild(child);
    }
}
