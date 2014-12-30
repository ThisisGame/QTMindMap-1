#pragma once
#include "ComponentVisitor.h"
class SimpleExpendAndCollapseComponentVisitor : public ComponentVisitor
{
    public:
        SimpleExpendAndCollapseComponentVisitor();
        ~SimpleExpendAndCollapseComponentVisitor();
        void visitor(Node*);
        void visitor(Root*);
        void visitor(TriangleDecorator*);
        void visitor(CircleDecorator*);
        void visitor(RectangleDecorator*);
};

