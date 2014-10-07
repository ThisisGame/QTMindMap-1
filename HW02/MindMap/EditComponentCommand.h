#pragma once
#include "Command.h"
#include "MindMapModel.h"

class EditComponentCommand :
    public Command
{
    public:
        EditComponentCommand(int id, string newDescription, string oldDescription, MindMapModel* model);
        EditComponentCommand();
        ~EditComponentCommand();
        void execute();
        void unexcute();
    private:
        MindMapModel* _model;
        int _id;
        string _oldDescription;
        string _newDescription;

};

