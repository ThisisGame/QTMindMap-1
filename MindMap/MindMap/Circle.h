#pragma once
#include "Decorator.h"
class Circle : public Decorator
{
    public:
        Circle(int);
        ~Circle();
        Component* clone();
        void drawComponent(MindMapGUIScene*);
};

