#include "Component.h"

Component::Component()
{
    _type = "Component";
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

