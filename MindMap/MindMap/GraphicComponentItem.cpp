#include "GraphicComponentItem.h"
#include <QPen>
#include <QtWidgets/QInputDialog>

GraphicComponentItem::GraphicComponentItem(string description, int id, GUIPresentationModel* pModel)
{
    BOUNDING_RECT = 5;
    _id = id;
    _pModel = pModel;
    this->setHandlesChildEvents(false);
    _textItem = new QGraphicsTextItem(QString::fromStdString(description));
    _textItem->setObjectName(QString::fromStdString(description));
    this->addToGroup(_textItem);
    _borderItem = new QGraphicsRectItem(_textItem->boundingRect().adjusted(-BOUNDING_RECT, -BOUNDING_RECT, BOUNDING_RECT, BOUNDING_RECT));
    this->addToGroup(_borderItem);
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(mouseClickEvent()));
}


GraphicComponentItem::~GraphicComponentItem()
{
}

void GraphicComponentItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    _timer->start(20);
}

void GraphicComponentItem::setPresentationModel(GUIPresentationModel* pModel)
{
    _pModel = pModel;
}

void GraphicComponentItem::setBorder(Qt::GlobalColor temp)
{
    int BORDER_WIDTH = 3;
    QPen pen(temp);
    pen.setWidth(BORDER_WIDTH);
    _borderItem->setPen(pen);
}

void GraphicComponentItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    bool result;
    _timer->stop();
    QString text = QInputDialog::getText(NULL, "Edit", "Please input your description", QLineEdit::Normal, QString::null, &result);
    _pModel->editDescription(text.toStdString(), result);
}

void GraphicComponentItem::mouseClickEvent()
{
    _pModel->selectComponent(_id);
}

int GraphicComponentItem::getWidth()
{
    return boundingRect().width();
}

int GraphicComponentItem::getHeight()
{
    return boundingRect().height();
}

void GraphicComponentItem::setPoint(int x, int y)
{
    this->setPos(x + BOUNDING_RECT, y);
}

