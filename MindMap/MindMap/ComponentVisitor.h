#pragma once

class Node;
class Root;
class TriangleDecorator;
class RectangleDecorator;
class CircleDecorator;

class ComponentVisitor
{
    public:
        ComponentVisitor();
        virtual ~ComponentVisitor();
        virtual void visitor(Node*) = 0;
        virtual void visitor(Root*) = 0;
        virtual void visitor(RectangleDecorator*) = 0;
        virtual void visitor(TriangleDecorator*) = 0;
        virtual void visitor(CircleDecorator*) = 0;
};

