#pragma once
#include <string>
#include <map>
#include <list>
#include <fstream>
#include "ConstString.h"
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
        void display();
        void insertNode(char);
        void saveMindMap();
        void setDescription(string);
        void setNodeName(string);
        void selectComponent(int);
        bool isRoot();
        bool isSelectedComponent();
        bool isSaved();
        string getMessage();
    private:
        int _idNumber;
        bool _isSaved;
        Component* _component;
        string _message;
        list<Component*> _nodelist;
        void clearList();
        Component* createNode();

};