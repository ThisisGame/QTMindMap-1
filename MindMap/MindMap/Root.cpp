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

void Root::calculatePos(int& position, int level, MindMapGUIScene* scene, string side)  	//AutoLayout�p��϶�
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
            child->calculatePos(positionRight, getWidth() + 25, scene, "Right");
        }
        else
        {
            child->calculatePos(positionLeft, getWidth() + 25, scene, "Left");
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

void Root::drawComponent(MindMapGUIScene* scene)      //ø�Ϫ���϶�
{
    int x = getPoint()[0];
    int y = getPoint()[1];
    scene->createItem(_id, _description);
    if (_selected)
    {
        scene->setBorder();
    }
    scene->addComponentItem();
    scene->setPos(x, y);
    int i = 0;
    for (auto child : _nodelist)  //���u
    {
        if (i % 2 != 0)
        {
            scene->addLine(x, y + getHeight() / 2, child->getPoint()[0] + child->getWidth(), child->getPoint()[1] + child->getHeight() / 2);
        }
        else
        {
            scene->addLine(x + getWidth(), y + getHeight() / 2, child->getPoint()[0], child->getPoint()[1] + child->getHeight() / 2);
        }
        child->drawComponent(scene);
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
