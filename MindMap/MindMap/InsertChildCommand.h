#pragma once
#include "Command.h"
#include "Component.h"
#include "MindMapModel.h"

class InsertChildCommand :
    public Command
{
    public:
        InsertChildCommand(Component*, Component*, MindMapModel*);
        ~InsertChildCommand();
        void execute();
        void unexcute();
    private:
        Component* _component;
        Component* _child;
        MindMapModel* _model;
};

