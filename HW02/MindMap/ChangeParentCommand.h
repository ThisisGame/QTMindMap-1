#pragma once
#include "Command.h"
#include "MindMapModel.h"

class ChangeParentCommand :
    public Command
{
    public:
        ChangeParentCommand(int, int, int, MindMapModel*);
        ChangeParentCommand();
        ~ChangeParentCommand();
        void execute();
        void unexcute();
    private:
        MindMapModel* _model;
        int _id;
        int _newParent;
        int _oldParent;
};

