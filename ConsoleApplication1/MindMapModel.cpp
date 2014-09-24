#include "MindMapModel.h"

MindMapModel::MindMapModel(void)
{
    _idNumber = 0;
    _id = 0;
}

MindMapModel::~MindMapModel(void)
{
}

void MindMapModel::createMindMap(string topic)
{
    Root* mindMapRoot = new Root(topic, _idNumber++);
    _nodelist.push_back(mindMapRoot);
}

void MindMapModel::clearList()
{
    for (list <Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        delete *i;
    }
    _nodelist.clear();
}

void MindMapModel::setId(int id)
{
    _id = id - 48;
}

void MindMapModel::createNode(string description = "newNode")
{
    _newNode = new Node(description, _idNumber++);
    _nodelist.push_back(_newNode);
    selectComponent(_id);
}

void MindMapModel::insertChild()
{
    createNode();
    _component->addChild(_newNode);
}

void MindMapModel::insertSibling()
{
    createNode();
    _component->addSibling(_newNode);
}

void MindMapModel::insertParent()
{
    createNode();
    _component->addParent(_newNode);
}

void MindMapModel::setNodeName(string nodeName)
{
    _newNode->setDescription(nodeName);
}


void MindMapModel::selectComponent(int id)
{
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if ((*i)->getId() == id)
        {
            _component = *i;
        }
    }
}

void MindMapModel::display()
{
    string content;
    stringstream outputstream(content);
    selectComponent(0);
    _component->display(outputstream, 0);
    cout << outputstream.str();
}

void MindMapModel::saveMindMap()
{
    char filename[] = "mindMap.txt";
    fstream fp;
    fp.open(filename, ios::out);//開啟檔案
    if (!fp) //如果開啟檔案失敗 輸出字串
    {
        cout << "Fail to open file: " << filename << endl;
    }
    for (list<Component*>::iterator node = _nodelist.begin(); node != _nodelist.end(); node++)
    {
        fp << (*node)->getId() << "\"" + (*node)->getDescription() + "\"";
        list<Component*> nodeList = (*node)->getNodeList();
        for (list<Component*>::iterator childNode = nodeList.begin(); childNode != nodeList.end(); childNode++)
        {
            fp << " " << (*childNode)->getId();
        }
        fp << endl;
    }
    fp.close();						//關閉檔案
}