#pragma once
#include <string>
#include <map>
#include <list>
#include <vector>
#include <fstream>
#include <iterator>
#include <regex>
#include "ConstString.h"
#include "Component.h"
#include "ComponentFactory.h"
#include "CommandManager.h"
using namespace std;

class MindMapModel
{
    public:
        MindMapModel(void);
        ~MindMapModel(void);
        void createMindMap(string);
        void display();
        void insertNode(char);
        void loadMindMap(string);
        void saveMindMap(string);
        void setDescription(string);
        bool selectComponent(int);
        string getMessage();

        void redo();
        void undo();
        void changeDescription(string);
        void changeParent(int);
        void deleteComponent();
        void doDeleteNode(Component*);
        void doAddNodes(list<Component*>);
        list<Component*> getNodeList();
        bool isRoot();
    private:
        int _selectedComponentId;
        ComponentFactory _componentFactory;
        Component* _component;
        string _message;
        list<Component*> _nodelist;
        void clearList();
        void reNumber();
        Component* createNode();
        CommandManager _commandManager;
        Component* findNodeByID(int);

};