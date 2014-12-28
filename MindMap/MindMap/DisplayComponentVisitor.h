#pragma once
#include "ComponentVisitor.h"
#include <list>
using namespace std;

class MindMapGUIScene;
class Component;

class DisplayComponentVisitor : public ComponentVisitor
{
    public:
        DisplayComponentVisitor(MindMapGUIScene*);
        ~DisplayComponentVisitor();
        void Visitor(Node*);
        void Visitor(Root*);
        void Visitor(TriangleDecorator*);
        void Visitor(CircleDecorator*);
        void Visitor(RectangleDecorator*);
    private:
        MindMapGUIScene* _scene;
        void displayNode(list<Component*>);
        void drawNode(int, int, int, string, bool);
};

