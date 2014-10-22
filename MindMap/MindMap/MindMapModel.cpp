#include "MindMapModel.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"
#include "InsertChildCommand.h"
#include "InsertParentCommand.h"
#include "InsertSiblingCommand.h"
#include <regex>

MindMapModel::MindMapModel(void)
{
    _component = NULL;
}

MindMapModel::~MindMapModel(void)
{
}

void MindMapModel::createMindMap(string topic)  //�s�ؤ@��Mindmap
{
    clearList();
    Component* root = _componentFactory.createComponent(ROOT_TYPE);
    _componentFactory.countId();
    root->setDescription(topic);
    _nodelist.push_back(root);
}

void MindMapModel::clearList()  //�M�Ťw�s��Mindmap
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

void MindMapModel::insertNode(char mode)  //���JNode
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

Component* MindMapModel::createNode() //�s�ؤ@��Node
{
    Component* newNode = _componentFactory.createComponent(NODE_TYPE);
    return newNode;
}

void MindMapModel::setDescription(string description)
{
    int lastID = _componentFactory.getId() - 1;
    findNodeByID(lastID)->setDescription(description);
}

Component* MindMapModel::findNodeByID(int id)  //���Component
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

bool MindMapModel::selectComponent(int id)  //���Component
{
    _component = findNodeByID(id);
    if (_component == NULL)
    {
        return false;
    }
    return true;
}

string MindMapModel::getMessage() //���o�B�z�T��
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

void MindMapModel::display()  //���MindMap
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

void MindMapModel::saveMindMap(string filename)  //�s��MindMap
{
    fstream file;
    vector<int> oldIdList = getIdList();
    reOrderNumber();
    file.open(filename, ios::out);//�}���ɮ�
    if (_component == NULL)
    {
        throw ERROR_SAVE;
    }
    if (!file) //�p�G�}���ɮץ��� ��X�r��
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
    file.close();						//�����ɮ�
    unOrderNumber(oldIdList);
    display();
    _message += SAVE_FILE_SUCCESS;
}

void MindMapModel::loadMindMap(string filename)  //Ū��
{
    vector<vector<string>> components;
    string inputString;
    fstream file;
    clearList();
    file.open(filename, ios::in);
    if (!file) //�p�G�}���ɮץ��� ��X�r��
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

void MindMapModel::createNodesConnectionByList(vector<vector<string>> components)  //�إ�Node���������Y
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

void MindMapModel::createMindMapByList(vector<vector<string>> components) //��Ū�ɫ�List�ӥ[�JNode
{
    createMindMap(components[0][1]);
    for (unsigned int i = 1; i < components.size(); i++)
    {
        doInsertNode(createNode());
        selectComponent(i);
        setDescription(components[i][1]);
    }
}