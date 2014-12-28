#pragma once
#include "Decorator.h"
class CircleDecorator : public Decorator
{
    public:
        CircleDecorator(int);
        ~CircleDecorator();
        Component* clone();
        void accept(ComponentVisitor*);
};

