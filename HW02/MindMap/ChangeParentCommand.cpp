#include "ChangeParentCommand.h"

ChangeParentCommand::ChangeParentCommand()
{
}

ChangeParentCommand::ChangeParentCommand(int id, int newParent, int oldParent, MindMapModel* model)
{
    _id = id;
    _newParent = newParent;
    _oldParent = oldParent;
    _model = model;
}

ChangeParentCommand::~ChangeParentCommand()
{
}

void ChangeParentCommand::execute()
{
    //���N����list������ƧR���]�O���m�^�A�A�[��s��list��
}

void ChangeParentCommand::unexcute()
{
}
