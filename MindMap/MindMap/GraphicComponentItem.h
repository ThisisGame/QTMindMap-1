#pragma once
#include <QtWidgets/QGraphicsItemGroup>
#include "GUIPresentationModel.h"
#include <QtCore/QTimer>
#include <QtWidgets/QGraphicsSceneMouseEvent>
//#include <QtWidgets/QInputDialog>

class GraphicComponentItem : public QObject, public QGraphicsItemGroup
{
        Q_OBJECT

    public:
        GraphicComponentItem(string, int, GUIPresentationModel*);
        ~GraphicComponentItem();
        void setPresentationModel(GUIPresentationModel*);
        void setBorder(Qt::GlobalColor);
        int getHeight();
        int getWidth();
        void setPoint(int, int);
        void addRectangleDecorator();
        void addEllipseDecorator();
        void addTriangleDecorator();
    private slots:
        void mouseClickEvent();
    protected:
        virtual void mousePressEvent(QGraphicsSceneMouseEvent*);
        virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
    private:
        GUIPresentationModel* _pModel;
        QGraphicsRectItem* _borderItem;
        QGraphicsTextItem* _textItem;
        QTimer* _timer;
        int _id;
        int BOUNDING_RECT;
};

