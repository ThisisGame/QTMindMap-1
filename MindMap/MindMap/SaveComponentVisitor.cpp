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
    file.open(filename, ios::out);//開啟檔案
    if (!file) //如果開啟檔案失敗 輸出字串
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
    file.close();						//關閉檔案
    unOrderNumber(oldIdList);
}

void SaveComponentVisitor::reOrderNumber()   //重新排序
{
    int i = 0;
    for (auto node : _saveList)
    {
        node->setId(i);
        i++;
    }
}

void SaveComponentVisitor::unOrderNumber(vector<int> idList)   //還原原本排序
{
    int i = 0;
    for (auto node : _saveList)
    {
        node->setId(idList[i]);
        i++;
    }
}

vector<int> SaveComponentVisitor::getIdList()  //取得ID排序
{
    vector<int> oldIdList;
    for (auto node : _saveList)
    {
        oldIdList.push_back(node->getId());
    }
    return oldIdList;
}

