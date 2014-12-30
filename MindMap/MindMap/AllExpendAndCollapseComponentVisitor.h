#pragma once
#include "ComponentVisitor.h"
class Component;

class AllExpendAndCollapseComponentVisitor : public ComponentVisitor
{
    public:
        AllExpendAndCollapseComponentVisitor();
        ~AllExpendAndCollapseComponentVisitor();
        void visitor(Node*);
        void visitor(Root*);
        void visitor(TriangleDecorator*);
        void visitor(CircleDecorator*);
        void visitor(RectangleDecorator*);
        void setExpend(bool);
        bool isExpend();
    private:
        void visitChildren(Component*);
        bool* _expend;
};

