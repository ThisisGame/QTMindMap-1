#pragma once
#include "Composite.h"

class Root :
    public Composite
{
    public:
        Root();
        Root(string, int);
        ~Root();
        virtual void addParent(Component*);
        virtual void addSibling(Component*);
};

