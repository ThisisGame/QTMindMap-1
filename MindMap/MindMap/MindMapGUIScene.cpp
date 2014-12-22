#include "MindMapGUIScene.h"
#include <QtWidgets/QGraphicsView>
#include <iostream>
using namespace std;

MindMapGUIScene::MindMapGUIScene(GUIPresentationModel* pModel, QObject* parent) : QGraphicsScene(parent)
{
    _pModel = pModel;
    QPolygonF Triangle;
    Triangle.append(QPointF(-10., 0));
    Triangle.append(QPointF(0., -10));
    Triangle.append(QPointF(10., 0));
    Triangle.append(QPointF(-10., 0));
    addPolygon(Triangle);
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
void MindMapGUIScene::addEllipseDecorator()
{
    _item->addEllipseDecorator();
}
void MindMapGUIScene::addRectDecorator()
{
    _item->addRectangleDecorator();
}

void MindMapGUIScene::setBorder()
{
    _item->setBorder(Qt::red);
}