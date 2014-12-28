#pragma once
#include "Decorator.h"
class TriangleDecorator : public Decorator
{
    public:
        TriangleDecorator(int);
        ~TriangleDecorator();
        Component* clone();
        void accept(ComponentVisitor*);
};

