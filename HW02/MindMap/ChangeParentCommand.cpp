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
    //Case1���N����list������ƧR���]�O���m�^�A�A�[��s��list��
    //case2�Nchild���X�ӥ[�iparent��node���A�A�Nnode�[�J���[��parent���A�����s�쥻��parent�A�ª�nodelist�n�s�_��
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
