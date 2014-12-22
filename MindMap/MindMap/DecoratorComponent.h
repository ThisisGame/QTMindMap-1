#pragma once
#include <string>
#include "GraphicComponentItem.h"
using namespace std;
class DecoratorComponent
{
    public:
        DecoratorComponent();
        ~DecoratorComponent();
        virtual void draw(int, string) = 0;
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        virtual void setPoint(int x, int y) = 0;
        virtual GraphicComponentItem* getItem() = 0;
};

