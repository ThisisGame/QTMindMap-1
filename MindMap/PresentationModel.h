#pragma once
#include <string>
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
        void saveMindMap();
        void selectMode(char);
        void updateMode();
        void exitMode(char);
    private:
        string _message;
        MindMapModel* _model;
        int _mode;
        void setMessage(string);
};

