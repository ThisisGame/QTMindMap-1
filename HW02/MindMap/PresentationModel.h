#pragma once
#include <string>
#include <sstream>
#include "MindMapModel.h"
#include "ConstString.h"
#include "ConstVariables.h"

class PresentationModel
{
    public:
        PresentationModel();
        PresentationModel(MindMapModel*);
        ~PresentationModel();
        int getMode();
        string getMessage();
        void display();
        void insertMode(char);
        void editMode(char);
        void loadMindMap();
        void saveMindMap();
        void selectMode(char);
        void selectComponent(string);
        void exitMode(char);
        void setDescription(string, int);
        void redo();
        void undo();
    private:
        string _message;
        MindMapModel* _model;
        int _mode;
        int _previousMode;
        void setMessage(string);
        void setMode(int);
};

