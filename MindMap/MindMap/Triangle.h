#pragma once
#include "Decorator.h"
class Triangle : public Decorator
{
    public:
        Triangle(int);
        ~Triangle();
        Component* clone();
        void drawComponent(MindMapGUIScene*);
};

