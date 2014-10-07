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
    //先將父親list內的資料刪除（記住位置），再加到新的list內
}

void ChangeParentCommand::unexcute()
{
}
