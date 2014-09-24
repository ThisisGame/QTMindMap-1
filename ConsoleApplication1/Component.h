#pragma once
#include <string>
#include <list>
#include <sstream>
#include <iostream>
using namespace std;

class Component
{
    public:
        Component();
        ~Component();
        int getId();
        string getDescription();
        string getMessange();
        void setDescription(string);
        void setParent(Component*);
        virtual list<Component*> getNodeList() = 0;
        virtual void addChild(Component*) = 0;
        virtual void addParent(Component*) = 0;
        virtual void addSibling(Component*) = 0;
        virtual void clearNodeList() = 0;
        virtual void deleteNodeByNode(Component*) = 0;
        virtual void setNodeList(list<Component*>) = 0;
        virtual void display(stringstream&, int, bool = false) = 0;
    protected:
        int _id;
        string _description;
        string _messanger;
        string _type;
        Component* _parent;
};

