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

void Root::addParent(Component* parent) //Root不能有Parent
{
    throw ERROR_ROOT_INSERT_PARENT;
}

void Root::addSibling(Component* sibling) //Root不能有Sibling
{
    throw ERROR_ROOT_INSERT_SIBLING;
}

void Root::setParent(Component* parent) //Root不能設定Parent
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