#pragma once
#include <string>
#include <list>
#include <fstream>
#include "Component.h"
#include "Node.h"
#include "Root.h"
using namespace std;

class MindMapModel
{
    public:
        MindMapModel(void);
        ~MindMapModel(void);
        void createMindMap(string);
        void insertChild();
        void insertParent();
        void insertSibling();
        void saveMindMap();
        void setId(int);
        void setNodeName(string);
        void display();
    private:
        Component* _component;
        Component* _newNode;
        int _idNumber;
        int _id;
        list<Component*> _nodelist;
        void clearList();
        void selectComponent(int);
        list<string> _mindMapDisplay;
        void createNode(string);
        list<string> outputList;
};