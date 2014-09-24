#pragma once
#include "Composite.h"

class Node :
    public Composite
{
    public:
        Node();
        Node(string, int);
        ~Node();
        virtual void addParent(Component*);
        virtual void addSibling(Component*);
};

