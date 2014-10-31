#pragma once
#include "Command.h"
#include "Component.h"
#include "MindMapModel.h"

class InsertParentCommand :
    public Command
{
    public:
        InsertParentCommand(Component*, Component*, MindMapModel*);
        ~InsertParentCommand();
        void execute();
        void unexcute();
    private:
        Component* _component;
        Component* _newParent;
        Component* _oldParent;
        MindMapModel* _model;
};

