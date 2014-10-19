#include "MindMapModel.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"
#include "InsertChildCommand.h"
#include "InsertParentCommand.h"
#include <regex>

MindMapModel::MindMapModel(void)
{
    _component = NULL;
}

MindMapModel::~MindMapModel(void)
{
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
    for (list <Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        delete *i;
    }
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
        _component->addSibling(newNode);
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
    _component = findNodeByID(id);
    if (_component == NULL)
    {
        return false;
    }
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
    if (parentID == _component->getId())
    {
        throw ERROR_SELECT_ITSELF;
    }
    else if (parent == NULL)
    {
        throw ERROR_SELECT_NODE;
    }
    _commandManager.execute(new ChangeParentCommand(_component, parent));
}

void MindMapModel::deleteComponent()
{
    _commandManager.execute(new DeleteComponentCommand(_component, this));
}

void MindMapModel::doDeleteNode(Component* component)
{
    _nodelist.remove(component);
}

void MindMapModel::doAddNodes(list<Component*> components)
{
    _nodelist = components;
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

void MindMapModel::display()  //顯示MindMap
{
    string content;
    stringstream outputstream(content);
    Component* root = findNodeByID(0);
    if (root == NULL)
    {
        throw ERROR_DISPLAY;
        return;
    }
    outputstream << THE_MIND_MAP << root->getDescription() << DISPLAY_MINDMAP << endl;
    root->display(outputstream, EMPTY_STRING);
    outputstream << endl;
    _message = outputstream.str();
}

void MindMapModel::reOrderNumber()
{
    int i = 0;
    for (auto node : _nodelist)
    {
        node->setId(i);
        i++;
    }
}

void MindMapModel::unOrderNumber(vector<int> idList)
{
    int i = 0;
    for (auto node : _nodelist)
    {
        node->setId(idList[i]);
        i++;
    }
}

vector<int> MindMapModel::getIdList()
{
    vector<int> oldIdList;
    for (auto node : _nodelist)
    {
        oldIdList.push_back(node->getId());
    }
    return oldIdList;
}

void MindMapModel::saveMindMap(string filename)  //存檔MindMap
{
    fstream file;
    vector<int> oldIdList = getIdList();
    reOrderNumber();
    file.open(filename, ios::out);//開啟檔案
    if (_component == NULL)
    {
        throw ERROR_SAVE;
    }
    if (!file) //如果開啟檔案失敗 輸出字串
    {
        throw ERROR_OPEN_FILE;
    }
    for (list<Component*>::iterator node = _nodelist.begin(); node != _nodelist.end(); node++)
    {
        file << (*node)->getId() << SPACE_STRING << DOUBLE_QUOTATION_STRING << (*node)->getDescription() << DOUBLE_QUOTATION_STRING;
        list<Component*> nodeList = (*node)->getNodeList();
        for (list<Component*>::iterator childNode = nodeList.begin(); childNode != nodeList.end(); childNode++)
        {
            file << SPACE_STRING << (*childNode)->getId();
        }
        file << SPACE_STRING << endl;
    }
    file.close();						//關閉檔案
    unOrderNumber(oldIdList);
    display();
    _message += SAVE_FILE_SUCCESS;
}

void MindMapModel::loadMindMap(string filename)  //讀檔
{
    vector<vector<string>> components;
    string inputString;
    fstream file;
    clearList();
    file.open(filename, ios::in);
    if (!file) //如果開啟檔案失敗 輸出字串
    {
        throw ERROR_OPEN_FILE;
    }
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
}

void MindMapModel::createNodesConnectionByList(vector<vector<string>> components)  //建立Node之間的關係
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        Component* parnet = findNodeByID(i);
        for (unsigned int j = 2; j < components[i].size(); j++)
        {
            stringstream childrenString(components[i][2]);
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
        createNode();
        _componentFactory.countId();
        selectComponent(i);
        setDescription(components[i][1]);
    }
}