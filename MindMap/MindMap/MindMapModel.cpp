#include "MindMapModel.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"
#include "InsertChildCommand.h"
#include "InsertParentCommand.h"
#include "InsertSiblingCommand.h"
#include "CutNodeCommand.h"
#include "PasteNodeCommand.h"
#include "AddDecoratorCommand.h"
#include "ClearDecoratorCommand.h"
#include "DisplayComponentVisitor.h"
#include "SaveComponentVisitor.h"
#include "SimpleExpendAndCollapseComponentVisitor.h"
#include "AllExpendAndCollapseComponentVisitor.h"
#include <regex>
#include <fstream>

MindMapModel::MindMapModel(void)
{
    _component = NULL;
    _cloneItem = NULL;
}

MindMapModel::~MindMapModel(void)
{
    clearList();
}

void MindMapModel::addRectangleDecorator()
{
    Component* decorator = _componentFactory.createComponent(RECTANGLE_TYPE);
    _commandManager.execute(new AddDecoratorCommand(_component, decorator, this));
}

void MindMapModel::addCircleDecorator()
{
    Component* decorator = _componentFactory.createComponent(CIRCLE_TYPE);
    _commandManager.execute(new AddDecoratorCommand(_component, decorator, this));
}

void MindMapModel::addTriangleDecorator()
{
    Component* decorator = _componentFactory.createComponent(TRIANGLE_TYPE);
    _commandManager.execute(new AddDecoratorCommand(_component, decorator, this));
}

void MindMapModel::clearAllDecorator()
{
    _commandManager.execute(new ClearDecoratorCommand(_component, this));
}

void MindMapModel::createMindMap(string topic)  //新建一個Mindmap
{
    clearList();
    Component* root = _componentFactory.createComponent(ROOT_TYPE);
    _componentFactory.countId();
    root->setDescription(topic);
    _nodelist.push_back(root);
}

void MindMapModel::clearList()  //清空已存的Mindmap
{
    _commandManager.clearAllCommand();
    delete findNodeByID(0);
    _nodelist.clear();
    _component = NULL;
    _componentFactory.setId(0);
}

void MindMapModel::insertNode(char mode)  //插入Node
{
    Component* newNode = createNode();
    if (mode == 'a')
    {
        _commandManager.execute(new InsertParentCommand(_component, newNode, this));
    }
    else if (mode == 'b')
    {
        _commandManager.execute(new InsertChildCommand(_component, newNode, this));
    }
    else if (mode == 'c')
    {
        _commandManager.execute(new InsertSiblingCommand(_component, newNode, this));
    }
}

void MindMapModel::doInsertNode(Component* child)
{
    _nodelist.push_back(child);
    _componentFactory.countId();
}

void MindMapModel::doUninsertNode(Component* child)
{
    doDeleteNode(child);
    _componentFactory.unCountId();
}

Component* MindMapModel::createNode() //新建一個Node
{
    Component* newNode = _componentFactory.createComponent(NODE_TYPE);
    return newNode;
}

void MindMapModel::setDescription(string description)
{
    int lastID = _componentFactory.getId() - 1;
    findNodeByID(lastID)->setDescription(description);
}

Component* MindMapModel::findNodeByID(int id)  //選取Component
{
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if ((*i)->getId() == id)
        {
            return *i;
        }
    }
    return NULL;
}

bool MindMapModel::selectComponent(int id)  //選取Component
{
    disableSelected();
    _component = findNodeByID(id);
    if (_component == NULL)
    {
        return false;
    }
    _component->setSelected(true);
    return true;
}

string MindMapModel::getMessage() //取得處理訊息
{
    return _message;
}

void MindMapModel::changeDescription(string newDescription)
{
    _commandManager.execute(new EditComponentCommand(newDescription, _component));
}

void MindMapModel::changeParent(int parentID)
{
    Component* parent = findNodeByID(parentID);
    _commandManager.execute(new ChangeParentCommand(_component, parent));
}

void MindMapModel::deleteComponent()
{
    _commandManager.execute(new DeleteComponentCommand(_component, this));
}

void MindMapModel::cutComponent()
{
    cloneItem();
    _commandManager.execute(new CutNodeCommand(_component, this));
}

void MindMapModel::pasteComponent()
{
    _commandManager.execute(new PasteNodeCommand(_cloneItem->clone(), this));
}

void MindMapModel::doDeleteNode(Component* component)
{
    _nodelist.remove(component);
}

void MindMapModel::doAddNodes(list<Component*> components)
{
    _nodelist = components;
    _componentFactory.setId(_nodelist.size());
}

list<Component*> MindMapModel::getNodeList()
{
    return _nodelist;
}

void MindMapModel::redo()
{
    _commandManager.redo();
}

void MindMapModel::undo()
{
    _commandManager.undo();
}

bool MindMapModel::isRoot()
{
    if (_component->getType() == ROOT_TYPE)
    {
        return true;
    }
    return false;
}

Component* MindMapModel::getSelectComponent()
{
    return _component;
}

void MindMapModel::display()  //顯示MindMap
{
    string content;
    stringstream outputstream(content);
    Component* root = findNodeByID(0);
    if (root == NULL)
    {
        throw ERROR_DISPLAY;
    }
    outputstream << THE_MIND_MAP << root->getDescription() << DISPLAY_MINDMAP << endl;
    root->display(outputstream, EMPTY_STRING);
    outputstream << endl;
    _message = outputstream.str();
}

void MindMapModel::saveMindMap(string filename)  //存檔MindMap
{
    SaveComponentVisitor visitor;
    if (_nodelist.size() == 0)
    {
        throw ERROR_SAVE;
    }
    Component* root = findNodeByID(0)->getDecorator();
    root->accept(&visitor);
    visitor.saveFile(filename);
    display();
    _message += SAVE_FILE_SUCCESS;
}

void MindMapModel::loadMindMap(string filename)  //讀檔
{
    vector<vector<string>> components;
    string inputString;
    fstream file;
    file.open(filename, ios::in);
    if (!file) //如果開啟檔案失敗 輸出字串
    {
        throw ERROR_OPEN_FILE;
    }
    clearList();
    while (getline(file, inputString))
    {
        regex regA("( \")|(\" )");
        string wordD = "\n";
        stringstream componentString(regex_replace(inputString, regA, wordD)); // Insert the string into a stream
        string componentElement;
        vector<string> component; // Create vector to hold our words
        while (getline(componentString, componentElement, '\n'))
        {
            component.push_back(componentElement);
        }
        components.push_back(component);
    }
    createMindMapByList(components);
    createNodesConnectionByList(components);
    disableSelected();
}

void MindMapModel::createNodesConnectionByList(vector<vector<string>> components)  //建立Node之間的關係
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        Component* parnet = findNodeByID(i);
        for (unsigned int j = 4; j < components[i].size(); j++)
        {
            stringstream childrenString(components[i][4]);
            string child;
            while (childrenString >> child)
            {
                int childID = atoi(child.c_str());
                parnet->addChild(findNodeByID(childID));
            }
        }
    }
}

void MindMapModel::createMindMapByList(vector<vector<string>> components) //由讀檔後List來加入Node
{
    createMindMap(components[0][1]);
    for (unsigned int i = 1; i < components.size(); i++)
    {
        if (components[i][3] != NODE_TYPE)
        {
            Component* decorator = _componentFactory.createComponent(components[i][3]);
            _componentFactory.countId();
            _nodelist.push_back(decorator);
        }
        else
        {
            doInsertNode(createNode());
            selectComponent(i);
            setDescription(components[i][1]);
        }
    }
}

void MindMapModel::draw(MindMapSceneAdapter* scene)  //繪出MindMap
{
    Component* root = findNodeByID(0)->getDecorator();
    if (root == NULL)
    {
        return;
    }
    int position = 0;
    root->calculatePos(position, 0, scene, NONE_SIDE);
    DisplayComponentVisitor visitor(scene);
    root->accept(&visitor);
}

void MindMapModel::disableSelected() //取消選擇
{
    for (auto item : _nodelist)
    {
        item->setSelected(false);
    }
}

void MindMapModel::cloneItem()  //複製Component
{
    delete _cloneItem;
    _cloneItem = _component->getDecorator()->clone();
}

void MindMapModel::doCutNodes(Component* component)  //剪下
{
    _nodelist.remove(component);
    for (auto item : component->getNodeList())
    {
        doCutNodes(item);
    }
}

void MindMapModel::doClearDecorator(Component* decorator, Component* component)  //清除裝飾
{
    if (decorator == component)
    {
        return;
    }
    _nodelist.remove(decorator);
    for (auto item : decorator->getNodeList())
    {
        doClearDecorator(item, component);
    }
}

void MindMapModel::doPasteNodes(Component* component) //貼上
{
    component->setId(_componentFactory.getId());
    _nodelist.push_back(component);
    _componentFactory.countId();
    for (auto item : component->getNodeList())
    {
        doPasteNodes(item);
    }
}

bool MindMapModel::isCanRedo() //確認是否可以Redo
{
    if (_commandManager.getRedoCommandStack().size() != 0)
    {
        return true;
    }
    return false;
}

bool MindMapModel::isCanUndo() //確認是否可以Undo
{
    if (_commandManager.getUndoCommandStack().size() != 0)
    {
        return true;
    }
    return false;
}

bool MindMapModel::isHaveDecorator() //確認是否有裝飾
{
    if (_component == NULL || _component == _component->getDecorator())
    {
        return false;
    }
    return true;
}

void MindMapModel::simpleExpend()
{
    SimpleExpendAndCollapseComponentVisitor visitor;
    _component->accept(&visitor);
}

void MindMapModel::allExpend()
{
    AllExpendAndCollapseComponentVisitor visitor;
    _component->accept(&visitor);
}

void MindMapModel::up()
{
    Component* component = _component->getDecorator();
    component->getParent()->up(component);
}

void MindMapModel::down()
{
    Component* component = _component->getDecorator();
    component->getParent()->down(component);
}

bool MindMapModel::isCanUp()
{
    if (_component->getType() == ROOT_TYPE)
    {
        return false;
    }
    Component* component = _component->getDecorator();
    return !component->getParent()->isUpComonent(component);
}

bool MindMapModel::isCanDown()
{
    if (_component->getType() == ROOT_TYPE)
    {
        return false;
    }
    Component* component = _component->getDecorator();
    return !component->getParent()->isUnderComonent(component);
}