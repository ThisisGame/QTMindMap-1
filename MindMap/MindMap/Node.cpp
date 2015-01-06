#include "Node.h"
#include "Decorator.h"


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

void Node::accept(ComponentVisitor* visitor)
{
    visitor->visitor(this);
}


void Node::up(Component* component)
{
    if (*_nodelist.begin() == component)
    {
        return;
    }
    list<Component*>::iterator upComponent;
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if (*i == component)
        {
            Component*  newComponent = *upComponent;
            *upComponent = component;
            *i = newComponent;
            return;
        }
        upComponent = i;
    }
}

void Node::down(Component* component)
{
    if (*--_nodelist.end() == component)
    {
        return;
    }
    list<Component*>::iterator upComponent;
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if (*i == component)
        {
            upComponent = i++;
            Component* newComponent = *i;
            *upComponent = newComponent;
            *i = component;
            return;
        }
    }
}

bool Node::isUpComonent(Component* component)
{
    if (*_nodelist.begin() == component)
    {
        return true;
    }
    return false;
}

bool Node::isUnderComonent(Component* component)
{
    if (*--_nodelist.end() == component)
    {
        return true;
    }
    return false;
}