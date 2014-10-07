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
        void changeDescription(string);
        void display();
        void insertNode(char);
        void loadMindMap();
        void saveMindMap();
        void setDescription(string);
        void setNodeName(string);
        void selectComponent(int);
        bool isRoot();
        bool isSelectedComponent();
        bool isSaved();
        string getMessage();
        void redo();
        void undo();
    private:
        int _selectedComponentId;
        bool _isSaved;
        ComponentFactory _componentFactory;
        Component* _component;
        string _message;
        list<Component*> _nodelist;
        void clearList();
        Component* createNode();
        CommandManager _commandManager;

};