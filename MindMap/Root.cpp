#include "Root.h"

Root::Root()
{
    _type = ROOT_TYPE;
}

Root::Root(string description, int id) : Composite(description, id)
{
    _type = ROOT_TYPE;
}

Root::Root(int id) : Composite(id)
{
    _type = ROOT_TYPE;
}

Root::~Root()
{
}

void Root::addParent(Component* parent) //Root���঳Parent
{
    delete parent;
    throw ERROR_ROOT_INSERT_PARENT;
}

void Root::addSibling(Component* sibling) //Root���঳Sibling
{
    delete sibling;
    throw ERROR_ROOT_INSERT_SIBLING;
}

void Root::setParent(Component* parent) //Root����]�wParent
{
}