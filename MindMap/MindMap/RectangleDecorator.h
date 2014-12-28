#pragma once
#include "Decorator.h"
class RectangleDecorator : public Decorator
{
    public:
        RectangleDecorator(int);
        ~RectangleDecorator();
        Component* clone();
        void accept(ComponentVisitor*);
};

