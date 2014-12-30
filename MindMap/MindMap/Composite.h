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
        void calculatePos(int&, int, MindMapGUIScene*, string);
        void setChildrenYPoint(int);
        void setChildrenXPoint(int, bool);
        void addDecorator(Component*);
        Component* getDecorator();
        bool isDecorator();
        string getSide();
        bool isExpend();
        void setExpend(bool);
        void up(Component*);
        void down(Component*);
        bool isUpComonent(Component*);
        bool isUnderComonent(Component*);
    protected:
        list<Component*> _nodelist;
        Component* _parent;
        string _side;
        bool _expend;
};

