#pragma once
#include "Decorator.h"
class Rectangle : public Decorator
{
    public:
        Rectangle(int);
        ~Rectangle();
        Component* clone();
        void drawComponent(MindMapGUIScene*);
};

