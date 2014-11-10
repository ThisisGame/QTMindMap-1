#pragma once
#include "MindMapModel.h"
#include "Subject.h"

class MindMapGUIScene;

class GUIPresentationModel : public Subject
{
    public:
        GUIPresentationModel(MindMapModel*);
        ~GUIPresentationModel();
        void loadMindMap(string);
        void selectComponent(int);
        void disableSelected();
        void editDescription(string);
        void createMindMap(string);
        void deleteComponent();
        void insertNode(char, string);
        void saveMindMap(string);
        void draw(MindMapGUIScene*);
        string getMessage();
        bool getSaveMindMapActionEnable();
        bool getEditNodeActionEnable();
        bool getDeleteNodeActionEnable();
        bool getInsertChildActionEnable();
        bool getInsertSiblingActionEnable();
        bool getInsertParentActionEnable();
        Subject* getSubject();
    private:
        MindMapModel* _model;
        string _message;
        bool _saveMindMapActionEnable;
        bool _editNodeActionEnable;
        bool _deleteNodeActionEnable;
        bool _insertChildActionEnable;
        bool _insertSiblingActionEnable;
        bool _insertParentActionEnable;
        void disableAction();
};

