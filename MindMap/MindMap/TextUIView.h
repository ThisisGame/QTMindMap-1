#pragma once
#include <iostream>
#include "ConstVariables.h"
#include "TextUIPresentationModel.h"
#include "MindMapModel.h"
using namespace std;

class TextUIView
{
    public:
        TextUIView(MindMapModel*);
        ~TextUIView();
        void run();
    private:
        MindMapModel* _model;
        TextUIPresentationModel* _pModel;
        map <int, void (TextUIView::*)()> _functionList;
        void selectMode();
        //功能一-新增MindMap
        void createNewMindMap();
        //功能二-新增Node
        void insertNewNode();
        void selectInsertMode();
        void enterNodeName();
        //功能三-修改Node
        void editMode();
        void selectEditMode();
        void changeDescription();
        void changeParent();
        //功能四-顯示MindMap
        void display();
        //功能五-儲存MindMap
        void saveMindMap();
        //功能六-讀取MindMap
        void loadMindMap();
        //功能七-重作
        void redo();
        //功能八-復原
        void undo();
        //功能九-離開
        void exitMode();
        //共用型功能
        void messangeMode();
        void selectId(string);
        void enterDescrption(string, int);
        string inputString();
        char inputChar();
};

