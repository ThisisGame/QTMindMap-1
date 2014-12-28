#include "MindMapGUIScene.h"
#include <QtWidgets/QGraphicsView>
#include <iostream>
using namespace std;

MindMapGUIScene::MindMapGUIScene(GUIPresentationModel* pModel, QObject* parent) : QGraphicsScene(parent)
{
    _pModel = pModel;
}

MindMapGUIScene::~MindMapGUIScene()
{
}

GUIPresentationModel* MindMapGUIScene::getPModel()
{
    return _pModel;
}

void MindMapGUIScene::draw()
{
    this->clear();
    _pModel->draw(this);
    this->setSceneRect(this->itemsBoundingRect());
}

void MindMapGUIScene::createItem(int id, string description)
{
    _item = new GraphicComponentItem(description, id, _pModel);
}

int MindMapGUIScene::getWidth()
{
    return _item->getWidth();
}

int MindMapGUIScene::getHeight()
{
    return _item->getHeight();
}

void MindMapGUIScene::setPos(int x, int y)
{
    _item->setPoint(x, y);
}

void MindMapGUIScene::deleteItem()
{
    delete _item;
}

void MindMapGUIScene::addComponentItem()
{
    addItem(_item);
}

void MindMapGUIScene::addCircleDecorator(int x, int y, int width, int height)
{
    addEllipse(x, y, width, height);
}

void MindMapGUIScene::addRectDecorator(int x, int y, int width, int height)
{
    addRect(x, y, width, height);
}

void MindMapGUIScene::addTriangleDecorator(int x, int y, int width, int height)
{
    QPolygonF triangle;
    triangle.append(QPointF(x, y + height));
    triangle.append(QPointF(x + width / 2, y));
    triangle.append(QPointF(x + width, y + height));
    triangle.append(QPointF(x, y + height));
    addPolygon(triangle);
}

void MindMapGUIScene::setBorder()
{
    _item->setBorder(Qt::red);
}