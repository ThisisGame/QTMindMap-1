#pragma once
#include "Component.h"

class Composite :
    public Component
{
    public:
        Composite();
        Composite(int);
        Composite(string, int);
        ~Composite();
        void addChild(Component*);
        void clearNodeList();
        void deleteNodeByNode(Component*);
        void display(stringstream&, int, bool = false);
        list<Component*> getNodeList();
    protected:
        list<Component*> _nodelist;
};

