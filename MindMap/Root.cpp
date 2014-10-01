#include "Root.h"
#include "ConstString.h"

Root::Root()
{
    _type = "Root";
}

Root::Root(string description, int id) : Composite(description, id)
{
    _type = "Root";
}

Root::Root(int id) : Composite(id)
{
    _type = "Root";
}

Root::~Root()
{
}

void Root::addParent(Component* parent) //Root不能有Parent
{
    delete parent;
    throw ERROR_ROOT_INSERT_PARENT;
}

void Root::addSibling(Component* sibling) //Root不能有Sibling
{
    delete sibling;
    throw ERROR_ROOT_INSERT_SIBLING;
}

void Root::setParent(Component* parent) //Root不能設定Parent
{
}