#include "AllExpendAndCollapseComponentVisitor.h"
#include "Node.h"
#include "Root.h"
#include "TriangleDecorator.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"

AllExpendAndCollapseComponentVisitor::AllExpendAndCollapseComponentVisitor()
{
    _expend = NULL;
}

AllExpendAndCollapseComponentVisitor::~AllExpendAndCollapseComponentVisitor()
{
    delete _expend;
}

void AllExpendAndCollapseComponentVisitor::visitor(Node* node)
{
    setExpend(node->isExpend());
    node->setExpend(isExpend());
    visitChildren(node);
}

void AllExpendAndCollapseComponentVisitor::visitor(Root* root)
{
    setExpend(root->isExpend());
    root->setExpend(isExpend());
    visitChildren(root);
}

void AllExpendAndCollapseComponentVisitor::visitor(TriangleDecorator* triangle)
{
    visitChildren(triangle);
}

void AllExpendAndCollapseComponentVisitor::visitor(CircleDecorator* circle)
{
    visitChildren(circle);
}

void AllExpendAndCollapseComponentVisitor::visitor(RectangleDecorator* rectangle)
{
    visitChildren(rectangle);
}

void AllExpendAndCollapseComponentVisitor::visitChildren(Component* component)
{
    for (auto child : component->getNodeList())
    {
        child->accept(this);
    }
}

void AllExpendAndCollapseComponentVisitor::setExpend(bool expend)
{
    if (_expend == NULL)
    {
        _expend = new bool(!expend);
    }
}

bool AllExpendAndCollapseComponentVisitor::isExpend()
{
    return *_expend;
}