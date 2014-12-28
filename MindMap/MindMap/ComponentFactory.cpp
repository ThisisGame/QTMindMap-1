#include "ComponentFactory.h"
#include "Node.h"
#include "Root.h"
#include "ConstString.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"
#include "TriangleDecorator.h"

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
    else if (type == CIRCLE_TYPE)
    {
        return new CircleDecorator(_id);
    }
    else if (type == RECTANGLE_TYPE)
    {
        return new RectangleDecorator(_id);
    }
    else if (type == TRIANGLE_TYPE)
    {
        return new TriangleDecorator(_id);
    }
    else
    {
        throw "Can't create Component!";
    }
}