#pragma once
#include "Composite.h"
#include "ConstString.h"

class Root :
    public Composite
{
    public:
        Root(int, string);
        Root(int);
        ~Root();
        void addParent(Component*);
        void addSibling(Component*);
        void setParent(Component*);
        bool isParent(Component*);
        Component* getParent();
};

