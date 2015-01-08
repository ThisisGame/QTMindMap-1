#pragma once
#include "Component.h"
#include "ConstString.h"

class Composite : public Component
{
    public:
        Composite(int);
        ~Composite();
        void addChild(Component*);
        void clearNodeList();
        void deleteNodeByNode(Component*);
        void changeNodeByNode(Component*, Component*);
        void display(stringstream&, string, bool);
        void addChilds(list<Component*>);
        list<Component*> getNodeList();
        void setChildrenYPoint(int);
        void addDecorator(Component*);
        Component* getDecorator();
        bool isDecorator();
        string getSide();
        bool isExpend();
        void setExpend(bool);
    protected:
        list<Component*> _nodelist;
        Component* _parent;
        string _side;
        bool _expend;
};

