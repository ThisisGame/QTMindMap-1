#include "Component.h"

Component::Component()
{
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

string Component::getMessange()
{
    return _messanger;
}

void Component::setParent(Component* parent)
{
    _parent = parent;
}
