#include "Root.h"
#include "GraphicComponentItem.h"
#include "MindMapGUIScene.h"


Root::Root(int id) : Composite(id)
{
    _type = ROOT_TYPE;
}

Root::Root(int id, string description) : Composite(id)
{
    _type = ROOT_TYPE;
    _description = description;
}

Root::~Root()
{
}

void Root::addParent(Component* parent) //Root不能有Parent
{
    throw ERROR_ROOT_INSERT_PARENT;
}

void Root::addSibling(Component* sibling) //Root不能有Sibling
{
    throw ERROR_ROOT_INSERT_SIBLING;
}

void Root::setParent(Component* parent) //Root不能設定Parent
{
}

bool Root::isParent(Component* parent)
{
    return false;
}

Component* Root::getParent()
{
    return NULL;
}

void Root::draw(vector<int>& position, int level, MindMapGUIScene* scene)
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
    position[level] += 50;
    for (auto child : _nodelist)
    {
        child->draw(position, level + 1, scene);
    }
}