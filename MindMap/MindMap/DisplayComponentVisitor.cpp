#include "DisplayComponentVisitor.h"
#include "MindMapGUIScene.h"
#include "Node.h"
#include "Root.h"
#include "TriangleDecorator.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"

DisplayComponentVisitor::DisplayComponentVisitor(MindMapGUIScene* scene)
{
    _scene = scene;
}

DisplayComponentVisitor::~DisplayComponentVisitor()
{
}

void DisplayComponentVisitor::visitor(Node* node)  //NODE畫圖
{
    int x = node->getPoint()[0];
    int y = node->getPoint()[1];
    drawNode(x, y, node->getId(), node->getDescription(), node->getSelected());
    if (!node->isExpend())
    {
        return;
    }
    for (auto child : node->getNodeList())  //接線
    {
        if (node->getSide() == LEFT_SIDE)
        {
            _scene->addLine(x, y + node->getHeight() / 2, child->getPoint()[0] + child->getWidth(), child->getPoint()[1] + child->getHeight() / 2);
        }
        else
        {
            _scene->addLine(x + node->getWidth(), y + node->getHeight() / 2, child->getPoint()[0], child->getPoint()[1] + child->getHeight() / 2);
        }
        child->accept(this);
    }
}

void DisplayComponentVisitor::visitor(Root* root)  //ROOT畫圖
{
    int x = root->getPoint()[0];
    int y = root->getPoint()[1];
    drawNode(x, y, root->getId(), root->getDescription(), root->getSelected());
    if (!root->isExpend())
    {
        return;
    }
    int i = 0;
    for (auto child : root->getNodeList())  //接線
    {
        if (i % 2 != 0)
        {
            _scene->addLine(x, y + root->getHeight() / 2, child->getPoint()[0] + child->getWidth(), child->getPoint()[1] + child->getHeight() / 2);
        }
        else
        {
            _scene->addLine(x + root->getWidth(), y + root->getHeight() / 2, child->getPoint()[0], child->getPoint()[1] + child->getHeight() / 2);
        }
        child->accept(this);
        i++;
    }
}

void DisplayComponentVisitor::visitor(TriangleDecorator* triangle) //三角形裝飾
{
    displayNode(triangle->getNodeList());
    _scene->addTriangleDecorator(triangle->getPoint()[0], triangle->getPoint()[1], triangle->getWidth(), triangle->getHeight());
}

void DisplayComponentVisitor::visitor(CircleDecorator* circle) //圓形裝飾
{
    displayNode(circle->getNodeList());
    _scene->addCircleDecorator(circle->getPoint()[0], circle->getPoint()[1], circle->getWidth(), circle->getHeight());
}

void DisplayComponentVisitor::visitor(RectangleDecorator* rectangle) //方形裝飾
{
    displayNode(rectangle->getNodeList());
    _scene->addRectDecorator(rectangle->getPoint()[0], rectangle->getPoint()[1], rectangle->getWidth(), rectangle->getHeight());
}

void DisplayComponentVisitor::displayNode(list<Component*> nodelist) //顯示裝飾內的NODE
{
    for (auto child : nodelist)
    {
        child->accept(this);
    }
}

void DisplayComponentVisitor::drawNode(int x, int y, int id, string description, bool selected)
{
    _scene->createItem(id, description);
    if (selected)
    {
        _scene->setBorder();
    }
    _scene->addComponentItem();
    _scene->setPos(x, y);
}