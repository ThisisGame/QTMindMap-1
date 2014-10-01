#include "MindMapModel.h"

MindMapModel::MindMapModel(void)
{
    _idNumber = 0;
    _component = NULL;
    _isSaved = false;
}

MindMapModel::~MindMapModel(void)
{
}

void MindMapModel::createMindMap(string topic)  //新建一個Mindmap
{
    Root* mindMapRoot = new Root(topic, _idNumber++);
    clearList();
    _nodelist.push_back(mindMapRoot);
}

void MindMapModel::clearList()  //清空已存的Mindmap
{
    for (list <Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        delete *i;
    }
    _nodelist.clear();
    _component = NULL;
}

void MindMapModel::insertNode(char mode)  //插入Child
{
    if (mode == 'a')
    {
        _component->addParent(createNode());
    }
    else if (mode == 'b')
    {
        _component->addChild(createNode());
    }
    else if (mode == 'c')
    {
        _component->addSibling(createNode());
    }
    _idNumber++;
}

Component* MindMapModel::createNode() //新建一個Node
{
    Component* newNode = new Node(_idNumber);
    _nodelist.push_back(newNode);
    return newNode;
}


void MindMapModel::setDescription(string description)
{
    selectComponent(_idNumber - 1);
    _component->setDescription(description);
}

void MindMapModel::selectComponent(int id)  //選取Component
{
    for (list<Component*>::iterator i = _nodelist.begin(); i != _nodelist.end(); i++)
    {
        if ((*i)->getId() == id)
        {
            _component = *i;
            return;
        }
    }
    _component = NULL;
}

string MindMapModel::getMessage() //取得處理訊息
{
    return _message;
}

bool MindMapModel::isSaved() //目前MindMap是否已儲存
{
    return _isSaved;
}

bool MindMapModel::isRoot() //判斷目前所選取的Component是否為Root
{
    if (_component->getType() == "Root")
    {
        return true;
    }
    return false;
}

bool MindMapModel::isSelectedComponent() //判斷目前是否有選取到Component
{
    if (_component != NULL)
    {
        return true;
    }
    return false;
}

void MindMapModel::display()  //顯示MindMap
{
    string content;
    stringstream outputstream(content);
    selectComponent(0);
    if (_component == NULL)
    {
        throw ERROR_DO_OPERATION;
    }
    outputstream << DISPLAY_MINDMAP << endl;
    _component->display(outputstream, 0);
    outputstream << endl;
    _message = outputstream.str();
}

void MindMapModel::saveMindMap()  //存檔MindMap
{
    char filename[] = SAVE_FILE_NAME;
    fstream fp;
    fp.open(filename, ios::out);//開啟檔案
    if (_component == NULL)
    {
        throw ERROR_DO_OPERATION;
    }
    if (!fp) //如果開啟檔案失敗 輸出字串
    {
        throw ERROR_OPEN_FILE;
    }
    for (list<Component*>::iterator node = _nodelist.begin(); node != _nodelist.end(); node++)
    {
        fp << (*node)->getId() << " \"" + (*node)->getDescription() + "\"";
        list<Component*> nodeList = (*node)->getNodeList();
        for (list<Component*>::iterator childNode = nodeList.begin(); childNode != nodeList.end(); childNode++)
        {
            fp << " " << (*childNode)->getId();
        }
        fp << endl;
    }
    fp.close();						//關閉檔案
    _isSaved = true;
    display();
    _message += SAVE_FILE_SUCCESS;
}