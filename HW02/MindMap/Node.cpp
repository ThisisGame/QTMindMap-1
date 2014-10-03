#include "Node.h"

Node::Node()
{
    _type = NODE_TYPE;
}

Node::Node(string description, int id) : Composite(description, id)
{
    _type = NODE_TYPE;
}

Node::Node(int id) : Composite(id)
{
    _type = NODE_TYPE;
}

Node::~Node()
{
}

void Node::addParent(Component* parent)  //Parent
{
    _parent->deleteNodeByNode(this);
    _parent->addChild(parent);
    parent->addChild(this);
}

void Node::addSibling(Component* sibling) //Sibling
{
    _parent->addChild(sibling);
}

void Node::setParent(Component* parent) //³]©wParent
{
    _parent = parent;
}