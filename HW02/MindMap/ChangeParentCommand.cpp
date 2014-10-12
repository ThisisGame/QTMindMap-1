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

void ChangeParentCommand::execute()
{
    //Case1���N����list������ƧR���]�O���m�^�A�A�[��s��list��
    //case2�Nchild���X�ӥ[�iparent��node���A�A�Nnode�[�J���[��parent���A�����s�쥻��parent�A�ª�nodelist�n�s�_��
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
