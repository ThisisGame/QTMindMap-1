#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include "GUIPresentationModel.h"

class MindMapGUIScene : public QGraphicsScene
{
        Q_OBJECT

    public:
        MindMapGUIScene(GUIPresentationModel*, QObject* parent);
        ~MindMapGUIScene();
        GUIPresentationModel* getPModel();
        void draw();
    protected:
        //virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
        //virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
        GUIPresentationModel* _pModel;
};

