#include "Circle.h"
#include "MindMapGUIScene.h"

Circle::Circle(int id)
{
    _id = id;
    _parent = NULL;
    _type = "Circle";
}

Circle::~Circle()
{
    delete _child;
}

void Circle::drawComponent(MindMapGUIScene* scene)
{
    _child->drawComponent(scene);
    scene->addCircleDecorator(_point[0], _point[1], _width, _height);
}

Component* Circle::clone()
{
    Component* cloneItem = new Circle(_id);
    Component* child = _child->clone();
    cloneItem->addChild(child);
    return cloneItem;
}