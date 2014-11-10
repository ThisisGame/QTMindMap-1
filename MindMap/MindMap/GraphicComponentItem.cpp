#include "GraphicComponentItem.h"
#include <QPen>

GraphicComponentItem::GraphicComponentItem(string description, int posX, int posY, int id, GUIPresentationModel* pModel)
{
    _id = id;
    _pModel = pModel;
    this->setHandlesChildEvents(false);
    _textItem = new QGraphicsTextItem(QString::fromStdString(description));
    _textItem->setObjectName(QString::fromStdString(description));
    _borderItem = new QGraphicsRectItem(_textItem->boundingRect().adjusted(-5, -5 , +5, +5));
    this->addToGroup(_borderItem);
    this->addToGroup(_textItem);
    this->setPos(posX, posY);
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
    _borderItem->setPen(QPen(temp));
}

void GraphicComponentItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    //QGraphicsItem::mouseDoubleClickEvent(event);
    _timer->stop();
    QPointF pos = event->pos();
    cout << "Click on item: (" << pos.x() << "," << pos.y() << ")" << endl;
    //QString text = QInputDialog::getText(this, "Input", "Please input your description", QLineEdit::Normal);
    //_pModel->editDescription(text.toStdString());
}

void GraphicComponentItem::mouseClickEvent()
{
    cout << "Single" << endl;
    _pModel->selectComponent(_id);
}

