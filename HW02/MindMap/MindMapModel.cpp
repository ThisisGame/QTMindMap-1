#include "MindMapModel.h"
#include "EditComponentCommand.h"

MindMapModel::MindMapModel(void)
{
    _component = NULL;
    _isSaved = false;
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
    selectComponent(_componentFactory.getId() - 1);
}

Component* MindMapModel::createNode() //�s�ؤ@��Node
{
    Component* newNode = _componentFactory.createComponent(NODE_TYPE);
    _nodelist.push_back(newNode);
    return newNode;
}


void MindMapModel::setDescription(string description)
{
    _component->setDescription(description);
}

void MindMapModel::selectComponent(int id)  //���Component
{
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if ((*i)->getId() == id)
        {
            _selectedComponentId = id;
            _component = *i;
            return;
        }
    }
    _selectedComponentId = -1;
    _component = NULL;
}

string MindMapModel::getMessage() //���o�B�z�T��
{
    return _message;
}

bool MindMapModel::isSaved() //�ثeMindMap�O�_�w�x�s
{
    return _isSaved;
}

bool MindMapModel::isRoot() //�P�_�ثe�ҿ����Component�O�_��Root
{
    if (_component->getType() == ROOT_TYPE)
    {
        return true;
    }
    return false;
}

bool MindMapModel::isSelectedComponent() //�P�_�ثe�O�_�������Component
{
    if (_component != NULL)
    {
        return true;
    }
    return false;
}

void MindMapModel::changeDescription(string newDescription)
{
    _commandManager.execute(new EditComponentCommand(_selectedComponentId, newDescription, _component->getDescription(), this));
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
    selectComponent(0);
    if (_component == NULL)
    {
        throw ERROR_DISPLAY;
    }
    outputstream << THE_MIND_MAP << _component->getDescription() << DISPLAY_MINDMAP << endl;
    _component->display(outputstream, EMPTY_STRING);
    outputstream << endl;
    _message = outputstream.str();
}

void MindMapModel::saveMindMap()  //�s��MindMap
{
    char filename[] = SAVE_FILE_NAME;
    fstream file;
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
    _isSaved = true;
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
                selectComponent(i);
                Component* parnet = _component;
                selectComponent(atoi(inputString.c_str()));
                parnet->addChild(_component);
            }
        }
    }
}