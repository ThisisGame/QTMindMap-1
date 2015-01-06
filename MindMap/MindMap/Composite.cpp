#include "Composite.h"
#include "GraphicComponentItem.h"
#include "MindMapGUIScene.h"

Composite::Composite(int id)
{
    _id = id;
    _parent = NULL;
    _side = NONE_SIDE;
    _expend = true;
}

Composite::~Composite()
{
    for (auto child : _nodelist)
    {
        delete child;
    }
}

void Composite::addDecorator(Component* decorator)  //增加
{
    if (_parent != NULL)
    {
        _parent->changeNodeByNode(this, decorator);
    }
    decorator->addChild(this);
}

void Composite::addChild(Component* node)  //增加Node
{
    node->setParent(this);
    for (auto child : _nodelist)
    {
        if (child == node)
        {
            return;
        }
    }
    _nodelist.push_back(node);
}

void Composite::clearNodeList() //清除NodeList內所有元素
{
    _nodelist.clear();
}

void Composite::addChilds(list<Component*> nodelist)  //取得NodeList
{
    for (auto child : nodelist)
    {
        this->addChild(child);
    }
}

list<Component*> Composite::getNodeList()  //取得NodeList
{
    return _nodelist;
}

void Composite::changeNodeByNode(Component* component, Component* newComponent)
{
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if (*i == component)
        {
            *i = newComponent;
            newComponent->setParent(this);
            return;
        }
    }
}

void Composite::deleteNodeByNode(Component* component)
{
    _nodelist.remove(component);
}

void Composite::display(stringstream& outputStream, string levelString, bool last) //處理輸出樹狀
{
    outputStream << "+-" + _description + "(" + _type + ", ID: " << _id << ")" << endl;  //Output Example +-Computer(Root, ID: 0)
    if (last == true)
    {
        levelString += "  ";
    }
    else
    {
        levelString += "| ";
    }
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if (i == --_nodelist.end())
        {
            last = true;
        }
        else
        {
            last = false;
        }
        outputStream << levelString;
        (*i)->display(outputStream, levelString, last);
    }
}

void Composite::calculatePos(int& position, int level, MindMapGUIScene* scene, string side)  	//AutoLayout計算區塊
{
    int NODE_DIST = 25;
    int x = level;
    int y = position;
    scene->createItem(_id, _description);
    setHeightAndWidth(scene->getHeight(), scene->getWidth());
    level = level + scene->getWidth() + NODE_DIST;
    scene->deleteItem();
    if (_expend == true)
    {
        for (auto child : _nodelist)
        {
            child->calculatePos(position, level, scene, side);
        }
    }
    int height = position - y;
    if (height != 0)
    {
        y = y + (height - NODE_DIST - _height) / 2;
    }
    else
    {
        position += _height + NODE_DIST;
    }
    _side = side;
    if (_side == RIGHT_SIDE)
    {
        setPoint(x, y);
    }
    else
    {
        setPoint(-x, y);
    }
    if (height != 0 && height < _height)
    {
        int changeHeightAmount = _height - height;
        setChildrenYPoint(changeHeightAmount / 2);
        position += changeHeightAmount;
    }
}

void Composite::setChildrenYPoint(int height)
{
    _point[1] += height;
    for (auto child : _nodelist)
    {
        child->setChildrenYPoint(height);
    }
}

void Composite::setChildrenXPoint(int x, bool firstNode)
{
    if (firstNode == false)
    {
        _point[0] += x;
    }
    firstNode = false;
    for (auto child : _nodelist)
    {
        child->setChildrenXPoint(x, firstNode);
    }
}

Component* Composite::getDecorator()
{
    if (_parent != NULL && _parent->isDecorator())
    {
        return _parent->getDecorator();
    }
    else
    {
        return this;
    }
}

bool Composite::isDecorator()
{
    return false;
}

string Composite::getSide()
{
    return _side;
}

bool Composite::isExpend()
{
    return _expend;
}

void Composite::setExpend(bool expend)
{
    _expend = expend;
}