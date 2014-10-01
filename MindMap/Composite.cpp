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

void Composite::addChild(Component* node)  //¼W¥[Node
{
    node->setParent(this);
    _nodelist.push_back(node);
}

void Composite::clearNodeList()
{
    _nodelist.clear();
}

list<Component*> Composite::getNodeList()
{
    return _nodelist;
}

void Composite::deleteNodeByNode(Component* component)
{
    _nodelist.remove(component);
}

void Composite::display(stringstream& outputstream, int level, bool last)
{
    outputstream << "+-" + _description + "(" + _type + ", ID: " << _id << ")" << endl;
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        for (int j = 0; j <= level; j++)
        {
            if (j == 0 || last == true)
            {
                outputstream << "  ";
            }
            else
            {
                outputstream << "| ";
            }
        }
        if (i == --_nodelist.end() && level == 0)
        {
            (*i)->display(outputstream, level + 1, true);
        }
        else
        {
            (*i)->display(outputstream, level + 1, last);
        }
    }
}