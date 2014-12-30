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

