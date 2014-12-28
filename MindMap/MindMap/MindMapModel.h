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
#include "Subject.h"
using namespace std;

namespace MindMapTest
{
    class MindMapModelTest;
}

class MindMapGUIScene;

class MindMapModel
{
        friend class MindMapTest::MindMapModelTest;
    public:
        MindMapModel(void);
        ~MindMapModel(void);
        void createMindMap(string);
        void display();
        void insertNode(char);
        void loadMindMap(string);
        void saveMindMap(string);
        void setDescription(string);
        Component* getSelectComponent();
        bool selectComponent(int);
        string getMessage();

        void addRectangleDecorator();
        void addCircleDecorator();
        void addTriangleDecorator();
        void clearAllDecorator();
        void doClearDecorator(Component*, Component*);

        void redo();
        void undo();
        void changeDescription(string);
        void changeParent(int);
        void deleteComponent();
        void doDeleteNode(Component*);
        void doAddNodes(list<Component*>);
        void doInsertNode(Component*);
        void doUninsertNode(Component*);
        list<Component*> getNodeList();
        bool isRoot();
        bool isCanRedo();
        bool isCanUedo();
        void cloneItem();
        void doCutNodes(Component*);
        void doPasteNodes(Component*);
        void cutComponent();
        void pasteComponent();

        void draw(MindMapGUIScene*);
        void disableSelected();
        bool isHaveDecorator();
    private:
        int _selectedComponentId;
        ComponentFactory _componentFactory;
        Component* _component;
        string _message;
        list<Component*> _nodelist;
        void clearList();
        void reOrderNumber();
        void unOrderNumber(vector<int>);
        void createMindMapByList(vector<vector<string>>);
        void createNodesConnectionByList(vector<vector<string>>);
        Component* createNode();
        CommandManager _commandManager;
        Component* findNodeByID(int);
        vector<int> getIdList();
        Component* _cloneItem;
};