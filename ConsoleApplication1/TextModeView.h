#pragma once
#include <iostream>
#include "MindMapModel.h"
using namespace std;

class TextModeView
{
    public:
        TextModeView();
        ~TextModeView();
        void run();
    private:
        MindMapModel* _model;
        void selectMode();
        void selectedMode(char);
        void createNewMindMap();
        void insertNewNode();
        void insertNewNodeMode(char);
        void saveMindMap();
        void display();
        string inputString();
};

