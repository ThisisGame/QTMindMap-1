#include "TriangleDecorator.h"
#include "MindMapGUIScene.h"

TriangleDecorator::TriangleDecorator(int id)
{
    _id = id;
    _parent = NULL;
    _type = TRIANGLE_TYPE;
}

TriangleDecorator::~TriangleDecorator()
{
    delete _child;
}

Component* TriangleDecorator::clone()
{
    Component* cloneItem = new TriangleDecorator(_id);
    Component* child = _child->clone();
    cloneItem->addChild(child);
    return cloneItem;
}

void TriangleDecorator::accept(ComponentVisitor* visitor)
{
    visitor->Visitor(this);
}