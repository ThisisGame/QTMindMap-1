#include "Node.h"
#include "Decorator.h"
#include "MindMapSceneAdapter.h"

Node::Node(int id) : Composite(id)
{
    _type = NODE_TYPE;
    setPoint(0, 0);
}

Node::Node(int id, string description) : Composite(id)
{
    _type = NODE_TYPE;
    _description = description;
    setPoint(0, 0);
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

void Node::setParent(Component* parent) //設定Parent
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


void Node::calculatePos(int& position, int level, MindMapSceneAdapter* scene, string side)  	//AutoLayout計算區塊
{
    int NODE_DIST = 25;
    int x = level;
    int y = position;
    scene->createItem(_id, _description);
    setHeightAndWidth(scene->getHeight(), scene->getWidth());
    level = level + scene->getWidth() + NODE_DIST;
    scene->deleteItem();
    if (_expend == true)
    {
        for (auto child : _nodelist)
        {
            child->calculatePos(position, level, scene, side);
        }
    }
    int height = position - y;
    if (height != 0)
    {
        y = y + (height - NODE_DIST - _height) / 2;
    }
    else
    {
        position += _height + NODE_DIST;
    }
    _side = side;
    if (_side == RIGHT_SIDE)
    {
        setPoint(x, y);
    }
    else
    {
        setPoint(-x, y);
    }
    if (height != 0 && height < _height)
    {
        int changeHeightAmount = _height - height;
        setChildrenYPoint(changeHeightAmount / 2);
        position += changeHeightAmount;
    }
}

void Node::setChildrenXPoint(int x, bool firstNode)
{
    if (firstNode == false)
    {
        _point[0] += x;
    }
    firstNode = false;
    for (auto child : _nodelist)
    {
        child->setChildrenXPoint(x, firstNode);
    }
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