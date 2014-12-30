#include "SaveComponentVisitor.h"
#include "Node.h"
#include "Root.h"
#include "TriangleDecorator.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"
#include <algorithm>
#include <fstream>

SaveComponentVisitor::SaveComponentVisitor()
{
}

SaveComponentVisitor::~SaveComponentVisitor()
{
}

void SaveComponentVisitor::visitorNode(Component* component)
{
    _saveList.push_back(component);
    for (auto item : component->getNodeList())
    {
        item->accept(this);
    }
}

void SaveComponentVisitor::visitor(Node* node)
{
    visitorNode(node);
}

void SaveComponentVisitor::visitor(Root* root)
{
    visitorNode(root);
}

void SaveComponentVisitor::visitor(TriangleDecorator* triangle)
{
    visitorNode(triangle);
}

void SaveComponentVisitor::visitor(CircleDecorator* circle)
{
    visitorNode(circle);
}

void SaveComponentVisitor::visitor(RectangleDecorator* rectangle)
{
    visitorNode(rectangle);
}

struct SaveComponentVisitor::PointerCompare
{
    bool operator()(const Component* left, const Component* right)
    {
        return *left < *right;
    }
};

void SaveComponentVisitor::saveFile(string filename)
{
    stable_sort(_saveList.begin(), _saveList.end(), PointerCompare());
    fstream file;
    vector<int> oldIdList = getIdList();
    reOrderNumber();
    file.open(filename, ios::out);//�}���ɮ�
    if (!file) //�p�G�}���ɮץ��� ��X�r��
    {
        throw ERROR_OPEN_FILE;
    }
    int i = 0;
    for (auto node : _saveList)
    {
        file << node->getId() << SPACE_STRING << DOUBLE_QUOTATION_STRING << node->getDescription() << DOUBLE_QUOTATION_STRING;
        file << SPACE_STRING << SPACE_STRING << DOUBLE_QUOTATION_STRING << node->getType() << DOUBLE_QUOTATION_STRING;
        list<Component*> children = node->getNodeList();
        for (auto child : children)
        {
            file << SPACE_STRING << child->getId();
        }
        file << SPACE_STRING << endl;
        i++;
    }
    file.close();						//�����ɮ�
    unOrderNumber(oldIdList);
}

void SaveComponentVisitor::reOrderNumber()   //���s�Ƨ�
{
    int i = 0;
    for (auto node : _saveList)
    {
        node->setId(i);
        i++;
    }
}

void SaveComponentVisitor::unOrderNumber(vector<int> idList)   //�٭�쥻�Ƨ�
{
    int i = 0;
    for (auto node : _saveList)
    {
        node->setId(idList[i]);
        i++;
    }
}

vector<int> SaveComponentVisitor::getIdList()  //���oID�Ƨ�
{
    vector<int> oldIdList;
    for (auto node : _saveList)
    {
        oldIdList.push_back(node->getId());
    }
    return oldIdList;
}

