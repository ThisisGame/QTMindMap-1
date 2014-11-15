#include "MindMapGUIScene.h"
#include "GraphicComponentItem.h"
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

/*
void MindMapGUIScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //QGraphicsScene::mousePressEvent(event);
}

void MindMapGUIScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    //QGraphicsScene::mouseDoubleClickEvent(event);
}
*/