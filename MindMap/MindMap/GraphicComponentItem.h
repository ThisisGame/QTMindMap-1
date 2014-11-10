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
        GraphicComponentItem(string, int, int, int, GUIPresentationModel*);
        ~GraphicComponentItem();
        void setPresentationModel(GUIPresentationModel*);
        void setBorder(Qt::GlobalColor);
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
};

