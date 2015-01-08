#pragma once
#include "ComponentVisitor.h"
#include <list>
#include "MindMapSceneAdapter.h"
using namespace std;

class Component;

class DisplayComponentVisitor : public ComponentVisitor
{
    public:
        DisplayComponentVisitor(MindMapSceneAdapter*);
        ~DisplayComponentVisitor();
        void visitor(Node*);
        void visitor(Root*);
        void visitor(TriangleDecorator*);
        void visitor(CircleDecorator*);
        void visitor(RectangleDecorator*);
    private:
        MindMapSceneAdapter* _scene;
        void displayNode(list<Component*>);
        void drawNode(int, int, int, string, bool);
};

