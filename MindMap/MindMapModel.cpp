#include "MindMapModel.h"

MindMapModel::MindMapModel(void)
{
    _idNumber = 0;
    _component = NULL;
    _isSaved = false;
}

MindMapModel::~MindMapModel(void)
{
}

void MindMapModel::createMindMap(string topic)  //�s�ؤ@��Mindmap
{
    Root* mindMapRoot = new Root(topic, _idNumber++);
    clearList();
    _nodelist.push_back(mindMapRoot);
}

void MindMapModel::clearList()  //�M�Ťw�s��Mindmap
{
    for (list <Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        delete *i;
    }
    _nodelist.clear();
    _component = NULL;
}

void MindMapModel::insertNode(char mode)  //���JChild
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
    _idNumber++;
}

Component* MindMapModel::createNode() //�s�ؤ@��Node
{
    Component* newNode = new Node(_idNumber);
    _nodelist.push_back(newNode);
    return newNode;
}


void MindMapModel::setDescription(string description)
{
    selectComponent(_idNumber - 1);
    _component->setDescription(description);
}

void MindMapModel::selectComponent(int id)  //���Component
{
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if ((*i)->getId() == id)
        {
            _component = *i;
            return;
        }
    }
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
    if (_component->getType() == "Root")
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

void MindMapModel::display()  //���MindMap
{
    string content;
    stringstream outputstream(content);
    selectComponent(0);
    if (_component == NULL)
    {
        throw ERROR_DO_OPERATION;
    }
    outputstream << DISPLAY_MINDMAP << endl;
    _component->display(outputstream, 0);
    outputstream << endl;
    _message = outputstream.str();
}

void MindMapModel::saveMindMap()  //�s��MindMap
{
    char filename[] = SAVE_FILE_NAME;
    fstream fp;
    fp.open(filename, ios::out);//�}���ɮ�
    if (_component == NULL)
    {
        throw ERROR_DO_OPERATION;
    }
    if (!fp) //�p�G�}���ɮץ��� ��X�r��
    {
        throw ERROR_OPEN_FILE;
    }
    for (list<Component*>::iterator node = _nodelist.begin(); node != _nodelist.end(); node++)
    {
        fp << (*node)->getId() << " \"" + (*node)->getDescription() + "\"";
        list<Component*> nodeList = (*node)->getNodeList();
        for (list<Component*>::iterator childNode = nodeList.begin(); childNode != nodeList.end(); childNode++)
        {
            fp << " " << (*childNode)->getId();
        }
        fp << endl;
    }
    fp.close();						//�����ɮ�
    _isSaved = true;
    display();
    _message += SAVE_FILE_SUCCESS;
}