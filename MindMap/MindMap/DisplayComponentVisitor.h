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
        void visitor(Node*);
        void visitor(Root*);
        void visitor(TriangleDecorator*);
        void visitor(CircleDecorator*);
        void visitor(RectangleDecorator*);
    private:
        MindMapGUIScene* _scene;
        void displayNode(list<Component*>);
        void drawNode(int, int, int, string, bool);
};

