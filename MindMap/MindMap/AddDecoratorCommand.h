#pragma once
#include "Command.h"
#include "Component.h"
#include "MindMapModel.h"

class AddDecoratorCommand :	public Command
{
    public:
        AddDecoratorCommand(Component*, Component*, MindMapModel*);
        ~AddDecoratorCommand();
        void execute();
        void unexcute();
    private:
        Component* _component;
        Component* _decorator;
        Component* _oldParent;
        MindMapModel* _model;
};

