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
        void Visitor(Node*);
        void Visitor(Root*);
        void Visitor(TriangleDecorator*);
        void Visitor(CircleDecorator*);
        void Visitor(RectangleDecorator*);
        void saveFile(string);
    private:
        vector<Component*> _saveList;
        void reOrderNumber();
        void unOrderNumber(vector<int>);
        vector<int> getIdList();
        struct PointerCompare;
};

