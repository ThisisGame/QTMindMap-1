#include "Component.h"

Component::Component()
{
    _type = "Component";
    _selected = false;
}

Component::~Component()
{
}

void Component::setDescription(string topic)
{
    _description = topic;
}

string Component::getDescription()
{
    return _description;
}

int Component::getId()
{
    return _id;
}

void Component::setId(int id)
{
    _id = id;
}

string Component::getType()
{
    return _type;
}

void Component::setSelected(bool selected)
{
    _selected = selected;
}

bool Component::getSelected()
{
    return _selected;
}

