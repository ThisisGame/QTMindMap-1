#pragma once
#include "Composite.h"
#include "ConstString.h"

class Node :
    public Composite
{
    public:
        Node();
        Node(int);
        Node(string, int);
        ~Node();
        void addParent(Component*);
        void addSibling(Component*);
        void setParent(Component*);
        Component* getParent();
    private:
        Component* _parent;
};

