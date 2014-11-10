#pragma once
#include "Command.h"
#include "Component.h"
#include "MindMapModel.h"

class InsertSiblingCommand :
    public Command
{
    public:
        InsertSiblingCommand(Component*, Component*, MindMapModel*);
        ~InsertSiblingCommand();
        void execute();
        void unexcute();
    private:
        Component* _component;
        Component* _sibling;
        Component* _parent;
        MindMapModel* _model;
};

