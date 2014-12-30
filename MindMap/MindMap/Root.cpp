#include "Root.h"
#include "MindMapGUIScene.h"

Root::Root(int id) : Composite(id)
{
    _type = ROOT_TYPE;
}

Root::Root(int id, string description) : Composite(id)
{
    _type = ROOT_TYPE;
    _description = description;
}

Root::~Root()
{
}

void Root::addParent(Component* parent) //Root不能有Parent
{
    throw ERROR_ROOT_INSERT_PARENT;
}

void Root::addSibling(Component* sibling) //Root不能有Sibling
{
    throw ERROR_ROOT_INSERT_SIBLING;
}

void Root::setParent(Component* parent) //Root不能設定Parent
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

void Root::calculatePos(int& position, int level, MindMapGUIScene* scene, string side)  	//AutoLayout計算區塊
{
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
            child->calculatePos(positionRight, getWidth() + 25, scene, RIGHT_SIDE);
        }
        else
        {
            child->calculatePos(positionLeft, getWidth() + 25, scene, LEFT_SIDE);
        }
        i++;
    }
    int test = 0;
    int mode = 0;
    int y = 0;
    i = 0;
    if (positionLeft > positionRight)
    {
        mode = 1;
        y = (positionLeft - getHeight() - 25) / 2;
        test = y - (positionRight - getHeight() - 25) / 2;
    }
    else
    {
        mode = 2;
        y = (positionRight - getHeight() - 25) / 2;
        test = y - (positionLeft - getHeight() - 25) / 2;
    }
    setPoint(0, y);
    for (auto child : _nodelist)
    {
        if (i % 2 == 0 && mode == 1)
        {
            child->setChildrenYPoint(test);
        }
        else if (i % 2 == 1 && mode == 2)
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
    for (auto child : _nodelist)  //接線
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