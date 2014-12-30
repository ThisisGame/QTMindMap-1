#include "SimpleExpendAndCollapseComponentVisitor.h"
#include "Node.h"
#include "Root.h"

SimpleExpendAndCollapseComponentVisitor::SimpleExpendAndCollapseComponentVisitor()
{
}

SimpleExpendAndCollapseComponentVisitor::~SimpleExpendAndCollapseComponentVisitor()
{
}

void SimpleExpendAndCollapseComponentVisitor::visitor(Node* node)
{
    bool expend = node->isExpend();
    node->setExpend(!expend);
}

void SimpleExpendAndCollapseComponentVisitor::visitor(Root* root)
{
    bool expend = root->isExpend();
    root->setExpend(!expend);
}

void SimpleExpendAndCollapseComponentVisitor::visitor(TriangleDecorator* triangle)
{
}

void SimpleExpendAndCollapseComponentVisitor::visitor(CircleDecorator* circle)
{
}

void SimpleExpendAndCollapseComponentVisitor::visitor(RectangleDecorator* rectangle)
{
}