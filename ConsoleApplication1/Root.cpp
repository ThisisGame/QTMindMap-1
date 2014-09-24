#include "Root.h"

Root::Root()
{
    _type = "Root";
}

Root::Root(string description, int id) : Composite(description, id)
{
    _type = "Root";
}

Root::~Root()
{
}


void Root::addParent(Component* parent)
{
    delete parent;
    _messanger = "Root can't insert parent node";
}

void Root::addSibling(Component* sibling)
{
    delete sibling;
    _messanger = "Root can't insert sibling node";
}