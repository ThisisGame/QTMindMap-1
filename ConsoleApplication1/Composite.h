#pragma once
#include "Component.h"

class Composite :
    public Component
{
    public:
        Composite();
        Composite(string, int);
        ~Composite();
        virtual list<Component*> getNodeList();
        virtual void addChild(Component*);
        virtual void clearNodeList();
        virtual void deleteNodeByNode(Component*);
        virtual void setNodeList(list<Component*>);
        virtual void display(stringstream&, int, bool = false);
    protected:
        list<Component*> _nodelist;
};

