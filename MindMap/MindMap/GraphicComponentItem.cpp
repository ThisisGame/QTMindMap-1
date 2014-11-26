#include "GraphicComponentItem.h"
#include <QPen>
#include <QtWidgets/QInputDialog>

GraphicComponentItem::GraphicComponentItem(string description, int posX, int posY, int id, GUIPresentationModel* pModel)
{
    _id = id;
    _pModel = pModel;
    this->setHandlesChildEvents(false);
    _textItem = new QGraphicsTextItem(QString::fromStdString(description));
    _textItem->setObjectName(QString::fromStdString(description));
    _borderItem = new QGraphicsRectItem(_textItem->boundingRect().adjusted(-5, -5, +5, +5));
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

vector<int> GraphicComponentItem::getBoundLeft()
{
    vector<int> point;
    point.push_back(boundingRect().center().x() - boundingRect().width() / 2);
    point.push_back(boundingRect().center().y());
    return point;
}

vector<int> GraphicComponentItem::getBoundRight()
{
    vector<int> point;
    point.push_back(boundingRect().center().x() + boundingRect().width() / 2);
    point.push_back(boundingRect().center().y());
    return point;
}

