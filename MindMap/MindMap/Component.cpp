#include "Component.h"

Component::Component()
{
    _type = "Component";
    _selected = false;
}

Component::~Component()
{
}

void Component::setDescription(string topic)
{
    _description = topic;
}

string Component::getDescription()
{
    return _description;
}

int Component::getId() const
{
    return _id;
}

void Component::setId(int id)
{
    _id = id;
}

string Component::getType()
{
    return _type;
}

void Component::setSelected(bool selected)
{
    _selected = selected;
}

bool Component::getSelected()
{
    return _selected;
}

vector<int> Component::getPoint()
{
    return _point;
}

void Component::setPoint(int x, int y)
{
    _point.clear();
    _point.push_back(x);
    _point.push_back(y);
}

void Component::setHeightAndWidth(int h, int w)
{
    _height = h;
    _width = w;
}

int Component::getHeight()
{
    return _height;
}

int Component::getWidth()
{
    return _width;
}

bool Component::operator < (const Component& component)const
{
    return _id < component.getId();
}