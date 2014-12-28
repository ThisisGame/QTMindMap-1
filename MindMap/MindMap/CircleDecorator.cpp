#include "CircleDecorator.h"
#include "MindMapGUIScene.h"

CircleDecorator::CircleDecorator(int id)
{
    _id = id;
    _parent = NULL;
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
    visitor->Visitor(this);
}