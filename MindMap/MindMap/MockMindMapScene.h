#pragma once
#include "MindMapSceneAdapter.h"
#include <string>
using namespace std;

class MockMindMapScene :
    public MindMapSceneAdapter
{
    public:
        MockMindMapScene();
        ~MockMindMapScene();
        void createItem(int, string);
        int getWidth();
        int getHeight();
        void setPos(int, int);
        void deleteItem();
        void addComponentItem();
        void addCircleDecorator(int, int, int, int);
        void addRectDecorator(int, int, int, int);
        void addTriangleDecorator(int, int, int, int);
        void setBorder();
        void addConnectLine(int, int, int, int);
    private:
        string _description;
};

