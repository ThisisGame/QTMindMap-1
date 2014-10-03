#pragma once
#include <iostream>
#include "ConstVariables.h"
#include "PresentationModel.h"
#include "MindMapModel.h"
using namespace std;

class TextUIView
{
    public:
        TextUIView();
        ~TextUIView();
        void run();
    private:
        MindMapModel* _model;
        PresentationModel* _pModel;
        void selectMode();
        void exitMode();
        void createNewMindMap();
        void insertNewNode();
        void enterNodeName();
        void saveMindMap();
        void display();
        void selectInsertMode();
        void messangeMode();
        string inputString();
        char inputChar();
        map < int, void (TextUIView::*)()> _functionList;
};

