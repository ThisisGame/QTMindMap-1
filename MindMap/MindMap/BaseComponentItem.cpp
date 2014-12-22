#include "BaseComponentItem.h"

BaseComponentItem::BaseComponentItem()
{
}

BaseComponentItem::~BaseComponentItem()
{
}

void BaseComponentItem::draw(int id, string description)
{
}

int BaseComponentItem::getHeight()
{
    return _item->getHeight();
}

int BaseComponentItem::getWidth()
{
    return _item->getWidth();
}

void BaseComponentItem::setPoint(int x, int y)
{
    _item->setPoint(x, y);
}

GraphicComponentItem* BaseComponentItem::getItem()
{
    return _item;
}
