#include "EditComponentCommand.h"

EditComponentCommand::EditComponentCommand(string newDescription, Component* component)
{
    _newDescription = newDescription;
    _oldDescription = component->getDescription();
    _component = component;
}

EditComponentCommand::~EditComponentCommand()
{
}

void EditComponentCommand::execute()
{
    _component->setDescription(_newDescription);
}

void EditComponentCommand::unexcute()
{
    _component->setDescription(_oldDescription);
}
