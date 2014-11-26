#include "Composite.h"
#include "GraphicComponentItem.h"
#include "MindMapGUIScene.h"

Composite::Composite(int id)
{
    _id = id;
}

Composite::~Composite()
{
    for (auto child : _nodelist)
    {
        delete child;
    }
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

void Composite::draw(int& position, int level, MindMapGUIScene* scene)
{
    //AutoLayout�p��϶�
    int x = level * 150;
    int y = position;
    for (auto child : _nodelist)
    {
        child->draw(position, level + 1, scene);
    }
    int height = position - y;
    if (height != 0)
    {
        y = y + (height - 50) / 2;
        position -= 50;
    }
    //ø�Ϫ���϶�
    GraphicComponentItem* item = new GraphicComponentItem(_description, x, y, _id, scene->getPModel());
    setPoint(x + item->getBoundLeft()[0], y + item->getBoundLeft()[1]);
    if (_selected)
    {
        item->setBorder(Qt::red);
    }
    scene->addItem(item);
    for (auto child : _nodelist)
    {
        scene->addLine(x + item->getBoundRight()[0], y + item->getBoundRight()[1], child->getPoint()[0], child->getPoint()[1]);
    }
    position += 50;
}