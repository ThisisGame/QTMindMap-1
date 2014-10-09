#include "MindMapModel.h"
#include "EditComponentCommand.h"
#include "ChangeParentCommand.h"
#include "DeleteComponentCommand.h"

MindMapModel::MindMapModel(void)
{
    _component = NULL;
}

MindMapModel::~MindMapModel(void)
{
}

void MindMapModel::createMindMap(string topic)  //�s�ؤ@��Mindmap
{
    Component* root = _componentFactory.createComponent(ROOT_TYPE);
    clearList();
    _componentFactory.countId();
    root->setDescription(topic);
    _nodelist.push_back(root);
}

void MindMapModel::clearList()  //�M�Ťw�s��Mindmap
{
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
    if (mode == 'a')
    {
        _component->addParent(createNode());
    }
    else if (mode == 'b')
    {
        _component->addChild(createNode());
    }
    else if (mode == 'c')
    {
        _component->addSibling(createNode());
    }
    _componentFactory.countId();
}

Component* MindMapModel::createNode() //�s�ؤ@��Node
{
    Component* newNode = _componentFactory.createComponent(NODE_TYPE);
    _nodelist.push_back(newNode);
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
    _commandManager.execute(new ChangeParentCommand(_component, findNodeByID(parentID)));
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

void MindMapModel::display()  //���MindMap
{
    string content;
    stringstream outputstream(content);
    Component* root = findNodeByID(0);
    if (root == NULL)
    {
        _message = ERROR_DISPLAY;
        return;
    }
    outputstream << THE_MIND_MAP << root->getDescription() << DISPLAY_MINDMAP << endl;
    root->display(outputstream, EMPTY_STRING);
    outputstream << endl;
    _message = outputstream.str();
}

void MindMapModel::reNumber()
{
    int i = 0;
    for (auto node : _nodelist)
    {
        node->setId(i);
        i++;
    }
}

void MindMapModel::saveMindMap()  //�s��MindMap
{
    char filename[] = SAVE_FILE_NAME;
    fstream file;
    reNumber();
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
    display();
    _message += SAVE_FILE_SUCCESS;
}

void MindMapModel::loadMindMap()  //Ū��
{
    vector<string> components;
    string inputString;
    fstream file;
    clearList();
    file.open(SAVE_FILE_NAME, ios::in);
    while (getline(file, inputString, '\"'))
    {
        components.push_back(inputString);
    }
    components.erase(components.begin());
    for (unsigned int i = 0; i < components.size() / 2; i++)
    {
        if (i == 0)
        {
            createMindMap(components[i * 2]);
        }
        else
        {
            createNode();
            _componentFactory.countId();
            selectComponent(i);
            setDescription(components[i * 2]);
        }
    }
    for (unsigned int i = 0; i < components.size() / 2; i++)
    {
        stringstream test(components[i * 2 + 1]);
        while (getline(test, inputString, ' '))
        {
            if (inputString == "" || inputString[0] == '\n')
            {
                continue;
            }
            else
            {
                Component* parnet = findNodeByID(i);
                int childID = atoi(inputString.c_str());
                parnet->addChild(findNodeByID(childID));
            }
        }
    }
}