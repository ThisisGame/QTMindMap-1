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
        virtual void Visitor(Node*) = 0;
        virtual void Visitor(Root*) = 0;
        virtual void Visitor(RectangleDecorator*) = 0;
        virtual void Visitor(TriangleDecorator*) = 0;
        virtual void Visitor(CircleDecorator*) = 0;
};

