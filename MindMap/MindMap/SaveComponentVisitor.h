#pragma once
#include "ComponentVisitor.h"
#include "vector"
using namespace std;

class Component;

class SaveComponentVisitor : public ComponentVisitor
{
    public:
        SaveComponentVisitor();
        ~SaveComponentVisitor();
        void visitor(Node*);
        void visitor(Root*);
        void visitor(TriangleDecorator*);
        void visitor(CircleDecorator*);
        void visitor(RectangleDecorator*);
        void saveFile(string);
        void visitorNode(Component*);
    private:
        vector<Component*> _saveList;
        void reOrderNumber();
        void unOrderNumber(vector<int>);
        vector<int> getIdList();
        struct PointerCompare;
};

