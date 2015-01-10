#include "CircleDecorator.h"
#include "MindMapGUIScene.h"

CircleDecorator::CircleDecorator(int id) : Decorator(id)
{
    _type = CIRCLE_TYPE;
}

CircleDecorator::~CircleDecorator()
{
    delete _child;
}

Component* CircleDecorator::clone()
{
    Component* cloneItem = new CircleDecorator(_id);
    Component* child = _child->clone();
    cloneItem->addChild(child);
    return cloneItem;
}

void CircleDecorator::accept(ComponentVisitor* visitor)
{
    visitor->visitor(this);
}