#include "EditComponentCommand.h"

EditComponentCommand::EditComponentCommand()
{
    _id = 0;
}

EditComponentCommand::EditComponentCommand(int id, string newDescription, string oldDescription, MindMapModel* model)
{
    _id = id;
    _newDescription = newDescription;
    _oldDescription = oldDescription;
    _model = model;
}

EditComponentCommand::~EditComponentCommand()
{
    cout << "delete command" << _id << endl;
}

void EditComponentCommand::execute()
{
    _model->selectComponent(_id);
    _model->setDescription(_newDescription);
}

void EditComponentCommand::unexcute()
{
    _model->selectComponent(_id);
    _model->setDescription(_oldDescription);
}
