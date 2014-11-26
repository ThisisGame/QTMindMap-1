#include "Node.h"

Node::Node(int id) : Composite(id)
{
    _type = NODE_TYPE;
}

Node::Node(int id, string description) : Composite(id)
{
    _type = NODE_TYPE;
    _description = description;
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

bool Node::isParent(Component* parent)
{
    if (parent == _parent)
    {
        return true;
    }
    else
    {
        return _parent->isParent(parent);
    }
}

Component* Node::getParent()
{
    return _parent;
}

Component* Node::clone()
{
    Component* cloneItem = new Node(_id, _description);
    for (auto item : _nodelist)
    {
        Component* child = item->clone();
        cloneItem->addChild(child);
    }
    return cloneItem;
}