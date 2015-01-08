#pragma once
#include <string>
using namespace std;
class MindMapSceneAdapter
{
    public:
        MindMapSceneAdapter();
        virtual ~MindMapSceneAdapter();
        virtual void createItem(int, string) = 0;
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        virtual void setPos(int, int) = 0;
        virtual void deleteItem() = 0;
        virtual void addComponentItem() = 0;
        virtual void addCircleDecorator(int, int, int, int) = 0;
        virtual void addRectDecorator(int, int, int, int) = 0;
        virtual void addTriangleDecorator(int, int, int, int) = 0;
        virtual void setBorder() = 0;
        virtual void addConnectLine(int, int, int, int) = 0;
};

