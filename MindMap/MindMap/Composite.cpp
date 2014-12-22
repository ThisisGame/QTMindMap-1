#include "Composite.h"
#include "GraphicComponentItem.h"
#include "MindMapGUIScene.h"

Composite::Composite(int id)
{
    _id = id;
}

Composite::~Composite()
{
    for (auto child : _nodelist)
    {
        delete child;
    }
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

void Composite::draw(MindMapGUIScene* scene)
{
    int position = 0;
    calculatePos(position, 0, scene);
    drawComponent(scene);
}
//
//void Composite::drawComponent(MindMapGUIScene* scene)      //繪圖物件區塊
//{
//    int x = getPoint()[0];
//    int y = getPoint()[1];
//    scene->createItem(_id, _description);
//    if (_selected)
//    {
//        scene->setBorder();
//    }
//    scene->addComponentItem();
//    scene->setPos(x, y);
//    for (auto child : _nodelist)  //接線
//    {
//        scene->addLine(x + getWidth(), y + getHeight() / 2, child->getPoint()[0], child->getPoint()[1] + child->getHeight() / 2);
//        child->drawComponent(scene);
//    }
//}
//
//void Composite::calculatePos(int& position, int level, MindMapGUIScene* scene)  	//AutoLayout計算區塊
//{
//    int NODE_DIST = 25;
//    int x = level;
//    int y = position;
//    int itemHeight = 0;
//    scene->createItem(_id, _description);
//    setHeightAndWidth(scene->getHeight(), scene->getWidth());
//    level = level + scene->getWidth() + NODE_DIST;
//    itemHeight = scene->getHeight();
//    scene->deleteItem();
//    for (auto child : _nodelist)
//    {
//        child->calculatePos(position, level, scene);
//    }
//    int height = position - y;
//    if (height != 0)
//    {
//        y = y + (height - NODE_DIST - itemHeight) / 2;
//    }
//    else
//    {
//        position += itemHeight + NODE_DIST;
//    }
//    setPoint(x, y);
//    if (height != 0 && height < itemHeight)
//    {
//        int changeHeightAmount = itemHeight - height;
//        setChildrenPoint(changeHeightAmount / 2);
//        position += changeHeightAmount;
//    }
//}


void Composite::drawComponent(MindMapGUIScene* scene)      //繪圖物件區塊
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
    for (auto child : _nodelist)  //接線
    {
        scene->addLine(x, y + getHeight() / 2, child->getPoint()[0] + child->getWidth(), child->getPoint()[1] + child->getHeight() / 2);
        child->drawComponent(scene);
    }
}

void Composite::calculatePos(int& position, int level, MindMapGUIScene* scene)  	//AutoLayout計算區塊
{
    int NODE_DIST = 25;
    int x = level;
    int y = position;
    int getheight = 0;
    scene->createItem(_id, _description);
    setHeightAndWidth(scene->getHeight(), scene->getWidth());
    level = level + scene->getWidth() + NODE_DIST;
    getheight = scene->getHeight();
    scene->deleteItem();
    for (auto child : _nodelist)
    {
        child->calculatePos(position, level, scene);
    }
    int height = position - y;
    if (height != 0)
    {
        y = y + (height - NODE_DIST - getheight) / 2;
    }
    else
    {
        position += getheight + NODE_DIST;
    }
    setPoint(-x, y);
    if (height != 0 && height < getheight)
    {
        int changeHeightAmount = getheight - height;
        setChildrenPoint(changeHeightAmount / 2);
        position += changeHeightAmount;
    }
}

void Composite::setChildrenPoint(int height)
{
    _point[1] += height;
    for (auto child : _nodelist)
    {
        child->setChildrenPoint(height);
    }
}