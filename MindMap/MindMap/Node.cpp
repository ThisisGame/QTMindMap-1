#include "Node.h"
#include "GraphicComponentItem.h"
#include "MindMapGUIScene.h"

Node::Node(int id) : Composite(id)
{
    _type = NODE_TYPE;
}

Node::Node(int id, string description) : Composite(id)
{
    _type = NODE_TYPE;
    _description = description;
}

Node::~Node()
{
}

void Node::addParent(Component* parent)  //Parent
{
    _parent->deleteNodeByNode(this);
    _parent->addChild(parent);
    parent->addChild(this);
}

void Node::addSibling(Component* sibling) //Sibling
{
    _parent->addChild(sibling);
}

void Node::setParent(Component* parent) //³]©wParent
{
    _parent = parent;
}

bool Node::isParent(Component* parent)
{
    if (parent == _parent)
    {
        return true;
    }
    else
    {
        return _parent->isParent(parent);
    }
}

Component* Node::getParent()
{
    return _parent;
}

void Node::draw(vector<int>& position, int level, MindMapGUIScene* scene)
{
    if (position.size() < (level + 1))
    {
        position.push_back(0);
    }
    GraphicComponentItem* item = new GraphicComponentItem(_description, (level + 1) * 100, position[level], _id, scene->getPModel());
    if (_selected)
    {
        item->setBorder(Qt::red);
    }
    scene->addItem(item);
    scene->addLine((level + 1) * 100 - 5, position[level] - 5, level * 100 - 5, position[level - 1] - 55);
    position[level] += 50;
    for (auto child : _nodelist)
    {
        child->draw(position, level + 1, scene);
    }
}