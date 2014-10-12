#include "Composite.h"

Composite::Composite()
{
}

Composite::Composite(string description, int id)
{
    _description = description;
    _id = id;
}

Composite::Composite(int id)
{
    _id = id;
}

Composite::~Composite()
{
}

void Composite::addChild(Component* node)  //�W�[Node
{
    node->setParent(this);
    for (auto child : _nodelist)
    {
        if (child == node)
        {
            return;
        }
    }
    _nodelist.push_back(node);
}

void Composite::clearNodeList() //�M��NodeList���Ҧ�����
{
    _nodelist.clear();
}

void Composite::addChilds(list<Component*> nodelist)  //���oNodeList
{
    for (auto child : nodelist)
    {
        this->addChild(child);
    }
}

list<Component*> Composite::getNodeList()  //���oNodeList
{
    return _nodelist;
}

void Composite::deleteNodeByNode(Component* component)
{
    _nodelist.remove(component);
}

void Composite::display(stringstream& outputStream, string levelString, bool last) //�B�z��X��
{
    outputStream << "+-" + _description + "(" + _type + ", ID: " << _id << ")" << endl;  //Output Example +-Computer(Root, ID: 0)
    if (last == true)
    {
        levelString += "  ";
    }
    else
    {
        levelString += "| ";
    }
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if (i == --_nodelist.end())
        {
            last = true;
        }
        else
        {
            last = false;
        }
        outputStream << levelString;
        (*i)->display(outputStream, levelString, last);
    }
}