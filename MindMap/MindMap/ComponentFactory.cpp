#include "ComponentFactory.h"
#include "Node.h"
#include "Root.h"
#include "ConstString.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

ComponentFactory::ComponentFactory()
{
    _id = 0;
}

ComponentFactory::~ComponentFactory()
{
}

int ComponentFactory::getId()
{
    return _id;
}

void ComponentFactory::setId(int id)
{
    _id = id;
}

void ComponentFactory::countId()
{
    _id++;
}

void ComponentFactory::unCountId()
{
    _id--;
}

Component* ComponentFactory::createComponent(string type)
{
    if (type == ROOT_TYPE)
    {
        return new Root(_id);
    }
    else if (type == NODE_TYPE)
    {
        return new Node(_id);
    }
    else if (type == "Circle")
    {
        return new Circle(_id);
    }
    else if (type == "Rectangle")
    {
        return new Rectangle(_id);
    }
    else if (type == "Triangle")
    {
        return new Triangle(_id);
    }
    else
    {
        throw "Can't create Component!";
    }
}