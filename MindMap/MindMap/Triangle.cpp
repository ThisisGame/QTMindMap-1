#include "Triangle.h"
#include "MindMapGUIScene.h"

Triangle::Triangle(int id)
{
    _id = id;
    _parent = NULL;
    _type = "Triangle";
}

Triangle::~Triangle()
{
    delete _child;
}

void Triangle::drawComponent(MindMapGUIScene* scene)
{
    _child->drawComponent(scene);
    scene->addTriangleDecorator(_point[0], _point[1], _width, _height);
}

Component* Triangle::clone()
{
    Component* cloneItem = new Triangle(_id);
    Component* child = _child->clone();
    cloneItem->addChild(child);
    return cloneItem;
}