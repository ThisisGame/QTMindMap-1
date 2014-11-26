#pragma once
#include "Command.h"
#include "MindMapModel.h"

class CutNodeCommand :	public Command
{
    public:
        CutNodeCommand(Component*, MindMapModel*);
        ~CutNodeCommand();
        void execute();
        void unexcute();
    private:
        Component* _component;
        Component* _parent;
        MindMapModel* _model;
        list<Component*> _oldNodeList;
        list<Component*> _oldParentList;
};

