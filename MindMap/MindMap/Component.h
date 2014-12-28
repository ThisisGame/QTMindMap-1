#pragma once
#include <string>
#include <list>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class MindMapGUIScene;

class Component
{
    public:
        Component();
        ~Component();
        int getId();
        void setId(int);
        void setDescription(string);
        string getType();
        string getDescription();
        void setSelected(bool);
        bool getSelected();
        void setPoint(int, int);
        vector<int> getPoint();
        void setHeightAndWidth(int, int);
        void draw(MindMapGUIScene*);
        int getHeight();
        int getWidth();
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
        virtual void drawComponent(MindMapGUIScene*) = 0;
        virtual void calculatePos(int&, int, MindMapGUIScene*, string) = 0;
        virtual void setChildrenYPoint(int) = 0;
        virtual void setChildrenXPoint(int, bool) = 0;
        virtual Component* getDecorator() = 0;
        virtual void changeNodeByNode(Component*, Component*) = 0;
        virtual bool isDecorator() = 0;
    protected:
        int _id;
        vector<int> _point;
        bool _selected;
        string _description;
        string _type;
        int _height;
        int _width;
};

