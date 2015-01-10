#include "Root.h"
#include "MindMapSceneAdapter.h"

Root::Root(int id) : Composite(id)
{
    _type = ROOT_TYPE;
    setPoint(0, 0);
}

Root::Root(int id, string description) : Composite(id)
{
    _type = ROOT_TYPE;
    _description = description;
    setPoint(0, 0);
}

Root::~Root()
{
}

void Root::addParent(Component* parent) //Root���঳Parent
{
    throw ERROR_ROOT_INSERT_PARENT;
}

void Root::addSibling(Component* sibling) //Root���঳Sibling
{
    throw ERROR_ROOT_INSERT_SIBLING;
}

void Root::setParent(Component* parent) //Root����]�wParent
{
    _parent = parent;
}

bool Root::isParent(Component* parent)
{
    return false;
}

Component* Root::getParent()
{
    return _parent;
}

Component* Root::clone()
{
    return NULL;
}

void Root::calculatePos(int& position, int level, MindMapSceneAdapter* scene, string side)  	//AutoLayout�p��϶�
{
    int NODE_DIST = 25;
    int LEFT_MODE = 1;
    int RIGHT_MODE = 2;
    int positionRight = 0;
    int positionLeft = 0;
    int i = 0;
    //SETUP
    scene->createItem(_id, _description);
    setHeightAndWidth(scene->getHeight(), scene->getWidth());
    scene->deleteItem();
    for (auto child : _nodelist)
    {
        if (i % 2 == 0)
        {
            child->calculatePos(positionRight, getWidth() + NODE_DIST, scene, RIGHT_SIDE);
        }
        else
        {
            child->calculatePos(positionLeft, getWidth() + NODE_DIST, scene, LEFT_SIDE);
        }
        i++;
    }
    int test = 0;
    int mode = 0;
    int y = 0;
    i = 0;
    if (positionLeft > positionRight)
    {
        mode = LEFT_MODE;
        y = (positionLeft - getHeight() - NODE_DIST) / 2;
        test = y - (positionRight - getHeight() - NODE_DIST) / 2;
    }
    else
    {
        mode = RIGHT_MODE;
        y = (positionRight - getHeight() - NODE_DIST) / 2;
        test = y - (positionLeft - getHeight() - NODE_DIST) / 2;
    }
    setPoint(0, y);
    for (auto child : _nodelist)
    {
        if (i % 2 == 0 && mode == LEFT_MODE)
        {
            child->setChildrenYPoint(test);
        }
        else if (i % 2 == 1 && mode == RIGHT_MODE)
        {
            child->setChildrenYPoint(test);
        }
        i++;
    }
}

void Root::setChildrenXPoint(int x, bool firstNode)
{
    if (firstNode == false)
    {
        _point[0] += x;
    }
    firstNode = false;
    int i = 0;
    for (auto child : _nodelist)  //���u
    {
        if (i % 2 != 0)
        {
            child->setChildrenXPoint(-x, firstNode);
        }
        else
        {
            child->setChildrenXPoint(x, firstNode);
        }
        i++;
    }
}

void Root::accept(ComponentVisitor* visitor)
{
    visitor->visitor(this);
}


void Root::up(Component* component)
{
    if (*_nodelist.begin() == component)
    {
        return;
    }
    list<Component*>::iterator upComponent;
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if (*i == component)
        {
            Component*  newComponent = *upComponent;
            *upComponent = component;
            *i = newComponent;
            return;
        }
        if (component->getSide() == (*i)->getSide())
        {
            upComponent = i;
        }
    }
}

void Root::down(Component* component)
{
    if (*--_nodelist.end() == component)
    {
        return;
    }
    list<Component*>::iterator upComponent;
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if (*i == component)
        {
            upComponent = i++;
            Component* newComponent = *++i;
            *upComponent = newComponent;
            *i = component;
            return;
        }
    }
}

bool Root::isUpComonent(Component* component)
{
    if (*_nodelist.begin() == component)
    {
        return true;
    }
    if (*++_nodelist.begin() == component)
    {
        return true;
    }
    return false;
}

bool Root::isUnderComonent(Component* component)
{
    if (*--_nodelist.end() == component)
    {
        return true;
    }
    if (*--(--_nodelist.end()) == component)
    {
        return true;
    }
    return false;
}