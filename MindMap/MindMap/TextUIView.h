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
        //�\��@-�s�WMindMap
        void createNewMindMap();
        //�\��G-�s�WNode
        void insertNewNode();
        void selectInsertMode();
        void enterNodeName();
        //�\��T-�ק�Node
        void editMode();
        void selectEditMode();
        void changeDescription();
        void changeParent();
        //�\��|-���MindMap
        void display();
        //�\�भ-�x�sMindMap
        void saveMindMap();
        //�\�ऻ-Ū��MindMap
        void loadMindMap();
        //�\��C-���@
        void redo();
        //�\��K-�_��
        void undo();
        //�\��E-���}
        void exitMode();
        //�@�Ϋ��\��
        void messangeMode();
        void selectId(string);
        void enterDescrption(string, int);
        string inputString();
        char inputChar();
};

