#include "Rectangle.h"
#include "MindMapGUIScene.h"

Rectangle::Rectangle(int id)
{
    _id = id;
    _parent = NULL;
    _type = "Rectangle";
}

Rectangle::~Rectangle()
{
    delete _child;
}

void Rectangle::drawComponent(MindMapGUIScene* scene)
{
    _child->drawComponent(scene);
    scene->addRectDecorator(_point[0], _point[1], _width, _height);
}

Component* Rectangle::clone()
{
    Component* cloneItem = new Rectangle(_id);
    Component* child = _child->clone();
    cloneItem->addChild(child);
    return cloneItem;
}