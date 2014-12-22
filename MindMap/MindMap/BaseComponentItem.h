#pragma once
#include "DecoratorComponent.h"
class BaseComponentItem :
    public DecoratorComponent
{
    public:
        BaseComponentItem();
        ~BaseComponentItem();
        void draw(int, string);
        int getWidth();
        int getHeight();
        void setPoint(int x, int y);
        GraphicComponentItem* getItem();
    private:
        GraphicComponentItem* _item;
};

