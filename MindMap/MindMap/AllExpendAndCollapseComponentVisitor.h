#pragma once
#include "ComponentVisitor.h"
class Component;

namespace MindMapTest
{
    class AllExpendAndCollapseComponentVisitorTest;
}

class AllExpendAndCollapseComponentVisitor : public ComponentVisitor
{
        friend class MindMapTest::AllExpendAndCollapseComponentVisitorTest;
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

