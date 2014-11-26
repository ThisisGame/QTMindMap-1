#pragma once
#include "Command.h"
#include "MindMapModel.h"

class PasteNodeCommand : public Command
{
    public:
        PasteNodeCommand(Component*, MindMapModel*);
        ~PasteNodeCommand();
        void execute();
        void unexcute();
    private:
        Component* _component;
        Component* _parent;
        MindMapModel* _model;
        list<Component*> _oldNodeList;
};

