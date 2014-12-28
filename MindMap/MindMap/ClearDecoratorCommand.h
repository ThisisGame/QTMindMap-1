#pragma once
#include "Command.h"
#include "MindMapModel.h"

class ClearDecoratorCommand : public Command
{
    public:
        ClearDecoratorCommand(Component*, MindMapModel*);
        ~ClearDecoratorCommand();
        void execute();
        void unexcute();
    private:
        Component* _component;
        Component* _parent;
        Component* _componentParent;
        Component* _decorator;
        MindMapModel* _model;
        list<Component*> _oldNodeList;
        list<Component*> _oldParentList;
};

