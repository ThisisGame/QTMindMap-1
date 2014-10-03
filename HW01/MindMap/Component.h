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
        void setDescription(string);
        string getType();
        string getDescription();
        virtual void addChild(Component*) = 0;
        virtual void addParent(Component*) = 0;
        virtual void addSibling(Component*) = 0;
        virtual void clearNodeList() = 0;
        virtual void deleteNodeByNode(Component*) = 0;
        virtual void display(stringstream&, string, bool = true) = 0;
        virtual void setParent(Component*) = 0;
        virtual list<Component*> getNodeList() = 0;
    protected:
        int _id;
        string _description;
        string _type;
};

