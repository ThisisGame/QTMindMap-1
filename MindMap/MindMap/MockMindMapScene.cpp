#include "MockMindMapScene.h"

MockMindMapScene::MockMindMapScene()
{
}

MockMindMapScene::~MockMindMapScene()
{
}

void MockMindMapScene::createItem(int id, string description)
{
    _description = description;
}

int MockMindMapScene::getWidth()
{
    return 50;
}

int MockMindMapScene::getHeight()
{
    if (_description.size() >= 15)
    {
        return 600;
    }
    else
    {
        return 100;
    }
}

void MockMindMapScene::setPos(int, int)
{
}

void MockMindMapScene::deleteItem()
{
}

void MockMindMapScene::addComponentItem()
{
}

void MockMindMapScene::addCircleDecorator(int, int, int, int)
{
}

void MockMindMapScene::addRectDecorator(int, int, int, int)
{
}

void MockMindMapScene::addTriangleDecorator(int, int, int, int)
{
}

void MockMindMapScene::setBorder()
{
}

void MockMindMapScene::addConnectLine(int, int, int, int)
{
}
