#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include "GraphicComponentItem.h"
#include "GUIPresentationModel.h"

class MindMapGUIScene : public QGraphicsScene
{
        Q_OBJECT

    public:
        MindMapGUIScene(GUIPresentationModel*, QObject* parent);
        ~MindMapGUIScene();
        GUIPresentationModel* getPModel();
        void draw();
        void createItem(int, string);
        int getWidth();
        int getHeight();
        void setPos(int, int);
        void deleteItem();
        void addComponentItem();
        void addEllipseDecorator();
        void addRectDecorator();
        void setBorder();
    protected:
        GUIPresentationModel* _pModel;
        GraphicComponentItem* _item;
};

