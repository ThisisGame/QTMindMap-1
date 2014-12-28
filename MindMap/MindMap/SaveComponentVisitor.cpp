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

void SaveComponentVisitor::Visitor(Node* node)
{
    _saveList.push_back(node);
    for (auto item : node->getNodeList())
    {
        item->accept(this);
    }
}

void SaveComponentVisitor::Visitor(Root* root)
{
    _saveList.push_back(root);
    for (auto item : root->getNodeList())
    {
        item->accept(this);
    }
}

void SaveComponentVisitor::Visitor(TriangleDecorator* triangle)
{
    _saveList.push_back(triangle);
    for (auto item : triangle->getNodeList())
    {
        item->accept(this);
    }
}

void SaveComponentVisitor::Visitor(CircleDecorator* circle)
{
    _saveList.push_back(circle);
    for (auto item : circle->getNodeList())
    {
        item->accept(this);
    }
}

void SaveComponentVisitor::Visitor(RectangleDecorator* rectangle)
{
    _saveList.push_back(rectangle);
    for (auto item : rectangle->getNodeList())
    {
        item->accept(this);
    }
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

