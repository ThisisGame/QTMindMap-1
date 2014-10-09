#pragma once
#include "Composite.h"
#include "ConstString.h"

class Root :
    public Composite
{
    public:
        Root();
        Root(int);
        Root(string, int);
        ~Root();
        void addParent(Component*);
        void addSibling(Component*);
        void setParent(Component*);
        Component* getParent();
};

