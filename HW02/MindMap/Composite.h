#pragma once
#include "Component.h"
#include "ConstString.h"

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
        void display(stringstream&, string, bool);
        list<Component*> getNodeList();
    protected:
        list<Component*> _nodelist;
};

