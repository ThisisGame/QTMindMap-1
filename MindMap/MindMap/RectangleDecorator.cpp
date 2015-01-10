#include "RectangleDecorator.h"
#include "MindMapGUIScene.h"

RectangleDecorator::RectangleDecorator(int id) : Decorator(id)
{
    _type = RECTANGLE_TYPE;
}

RectangleDecorator::~RectangleDecorator()
{
    delete _child;
}

Component* RectangleDecorator::clone()
{
    Component* cloneItem = new RectangleDecorator(_id);
    Component* child = _child->clone();
    cloneItem->addChild(child);
    return cloneItem;
}

void RectangleDecorator::accept(ComponentVisitor* visitor)
{
    visitor->visitor(this);
}
