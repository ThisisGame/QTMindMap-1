#include "Root.h"

Root::Root(int id) : Composite(id)
{
    _type = ROOT_TYPE;
}

Root::Root(int id, string description) : Composite(id)
{
    _type = ROOT_TYPE;
    _description = description;
}

Root::~Root()
{
}

void Root::addParent(Component* parent) //Root���঳Parent
{
    throw ERROR_ROOT_INSERT_PARENT;
}

void Root::addSibling(Component* sibling) //Root���঳Sibling
{
    throw ERROR_ROOT_INSERT_SIBLING;
}

void Root::setParent(Component* parent) //Root����]�wParent
{
}

bool Root::isParent(Component* parent)
{
    return false;
}

Component* Root::getParent()
{
    return NULL;
}

Component* Root::clone()
{
    return NULL;
}