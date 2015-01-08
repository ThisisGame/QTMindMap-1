#pragma once
#include <string>
#include <list>
#include <sstream>
#include <iostream>
#include <vector>
#include "ComponentVisitor.h"

using namespace std;

class MindMapSceneAdapter;

class Component
{
    public:
        Component();
        virtual ~Component();
        int getId() const;
        void setId(int);
        void setDescription(string);
        string getType();
        string getDescription();
        void setSelected(bool);
        bool getSelected();
        void setPoint(int, int);
        vector<int> getPoint();
        void setHeightAndWidth(int, int);
        int getHeight();
        int getWidth();
        bool operator < (const Component&)const;
        virtual void addDecorator(Component*) = 0;
        virtual void addChild(Component*) = 0;
        virtual void addParent(Component*) = 0;
        virtual void addSibling(Component*) = 0;
        virtual void clearNodeList() = 0;
        virtual void deleteNodeByNode(Component*) = 0;
        virtual void display(stringstream&, string, bool = true) = 0;
        virtual void setParent(Component*) = 0;
        virtual bool isParent(Component*) = 0;
        virtual void addChilds(list<Component*>) = 0;
        virtual Component* getParent() = 0;
        virtual list<Component*> getNodeList() = 0;
        virtual Component* clone() = 0;
        virtual void calculatePos(int&, int, MindMapSceneAdapter*, string) = 0;
        virtual void setChildrenYPoint(int) = 0;
        virtual void setChildrenXPoint(int, bool) = 0;
        virtual Component* getDecorator() = 0;
        virtual void changeNodeByNode(Component*, Component*) = 0;
        virtual bool isDecorator() = 0;
        virtual void accept(ComponentVisitor*) = 0;
        virtual void up(Component*) = 0;
        virtual void down(Component*) = 0;
        virtual bool isUpComonent(Component*) = 0;
        virtual bool isUnderComonent(Component*) = 0;
        virtual string getSide() = 0;
    protected:
        int _id;
        vector<int> _point;
        bool _selected;
        string _description;
        string _type;
        int _height;
        int _width;
};

