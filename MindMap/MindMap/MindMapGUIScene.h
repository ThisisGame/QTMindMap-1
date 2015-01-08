#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include "GraphicComponentItem.h"
#include "GUIPresentationModel.h"
#include "MindMapSceneAdapter.h"

class MindMapGUIScene : public QGraphicsScene , public MindMapSceneAdapter
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
        void addCircleDecorator(int, int, int, int);
        void addRectDecorator(int, int, int, int);
        void addTriangleDecorator(int, int, int, int);
        void setBorder();
        void addConnectLine(int, int, int, int);
    protected:
        GUIPresentationModel* _pModel;
        GraphicComponentItem* _item;
};

