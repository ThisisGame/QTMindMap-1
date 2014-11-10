#pragma once
#include <string>
#include <sstream>
#include "MindMapModel.h"
#include "ConstString.h"
#include "ConstVariables.h"

class TextUIPresentationModel
{
    public:
        TextUIPresentationModel();
        TextUIPresentationModel(MindMapModel*);
        ~TextUIPresentationModel();
        int getMode();
        string getMessage();
        void display();
        void insertMode(char);
        void editMode(char);
        void loadMindMap(string);
        void saveMindMap(string);
        void selectMode(char);
        void selectComponent(string);
        void exitMode(char, string);
        void setDescription(string, int);
        void redo();
        void undo();
        void setMode(int);
    private:
        string _message;
        MindMapModel* _model;
        int _mode;
        void setMessage(string);
};

