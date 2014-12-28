#include "Decorator.h"
#include "MindMapGUIScene.h"

Decorator::Decorator(int id)
{
    _id = id;
    _parent = NULL;
    _type = "Decorator";
}

Decorator::Decorator()
{
}

Decorator::~Decorator()
{
    delete _child;
}

void Decorator::changeNodeByNode(Component* component, Component* decorator)
{
    _parent->changeNodeByNode(this, decorator);
}

void Decorator::addDecorator(Component* decorator)
{
    if (_parent != NULL)
    {
        _parent->changeNodeByNode(this, decorator);
    }
    decorator->addChild(this);
}

void Decorator::addChild(Component* child)
{
    _child = child;
    _child->setParent(this);
}

void Decorator::addParent(Component* parent)
{
    _parent->deleteNodeByNode(this);
    _parent->addChild(parent);
    parent->addChild(this);
}

void Decorator::addSibling(Component* sibling)
{
    _parent->addChild(sibling);
}

void Decorator::clearNodeList()
{
    _child->clearNodeList();
}

void Decorator::deleteNodeByNode(Component* component)
{
    _parent->deleteNodeByNode(this);
}

void Decorator::display(stringstream& outputStream, string levelString, bool last)
{
    _child->display(outputStream, levelString, last);
}

void Decorator::setParent(Component* parent)
{
    _parent = parent;
}

bool Decorator::isParent(Component* parent)
{
    return _parent->isParent(parent);
}

void Decorator::addChilds(list<Component*> childs)
{
    _child->addChilds(childs);
}

Component* Decorator::getParent()
{
    return _parent;
}

list<Component*> Decorator::getNodeList()
{
    list<Component*> child;
    child.push_back(_child);
    return child;
}

void Decorator::calculatePos(int& position, int level, MindMapGUIScene* scene, string side)
{
    level += 5;
    position += 5;
    _child->calculatePos(position, level, scene, side);
    position += 5;
    if (side == "Left")
    {
        setChildrenXPoint(-5, true);
    }
    else
    {
        setChildrenXPoint(5, true);
    }
    setPoint(_child->getPoint()[0] - 5, _child->getPoint()[1] - 5);
    _height = _child->getHeight() + 10;
    _width = _child->getWidth() + 10;
}

void Decorator::setChildrenYPoint(int height)
{
    _point[1] += height;
    _child->setChildrenYPoint(height);
}

void Decorator::setChildrenXPoint(int x, bool firstNode)
{
    if (firstNode == false)
    {
        _point[0] += x;
    }
    _child->setChildrenXPoint(x, firstNode);
}

Component* Decorator::getDecorator()
{
    if (_parent != NULL && _parent->isDecorator())
    {
        return _parent->getDecorator();
    }
    else
    {
        return this;
    }
}

bool Decorator::isDecorator()
{
    return true;
}