#pragma once
#include "Component.h"
#include "ConstString.h"

class Composite :
    public Component
{
    public:
        Composite(int);
        ~Composite();
        void addChild(Component*);
        void clearNodeList();
        void deleteNodeByNode(Component*);
        void display(stringstream&, string, bool);
        void addChilds(list<Component*>);
        list<Component*> getNodeList();
        void draw(MindMapGUIScene*);
        void drawComponent(MindMapGUIScene*);
        void calculatePos(int&, int, MindMapGUIScene*);
        void setChildrenPoint(int);
    protected:
        list<Component*> _nodelist;
};

