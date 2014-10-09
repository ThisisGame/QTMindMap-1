#pragma once
#include "Command.h"
#include "Component.h"

class ChangeParentCommand :
    public Command
{
    public:
        ChangeParentCommand(Component*, Component*);
        ChangeParentCommand();
        ~ChangeParentCommand();
        void execute();
        void unexcute();
    private:
        Component* _child;
        Component* _newParent;
        Component* _oldParent;
        list<Component*> _oldParentList;
};

