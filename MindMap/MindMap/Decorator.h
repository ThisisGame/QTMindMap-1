#pragma once
#include "DecoratorComponent.h"
class Decorator :
    public DecoratorComponent
{
    public:
        Decorator();
        ~Decorator();
        void draw(int, string);
        int getWidth();
        int getHeight();
        void setPoint(int x, int y);
        GraphicComponentItem* getItem();
};

