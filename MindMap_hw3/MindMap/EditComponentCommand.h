#pragma once
#include "Command.h"
#include "Component.h"

class EditComponentCommand :
    public Command
{
    public:
        EditComponentCommand(string, Component*);
        ~EditComponentCommand();
        void execute();
        void unexcute();
    private:
        Component* _component;
        string _oldDescription;
        string _newDescription;

};

