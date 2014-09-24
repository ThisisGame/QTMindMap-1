#include "Node.h"

Node::Node()
{
    _type = "Node";
}

Node::Node(string description, int id) : Composite(description, id)
{
    _type = "Node";
}

Node::~Node()
{
}

void Node::addParent(Component* parent)
{
    _parent->deleteNodeByNode(this);
    _parent->addChild(parent);
    parent->addChild(this);
}

void Node::addSibling(Component* sibling)
{
    _parent->addChild(sibling);
}