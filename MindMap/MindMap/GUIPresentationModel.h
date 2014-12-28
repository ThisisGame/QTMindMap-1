#pragma once
#include "MindMapModel.h"
#include "Subject.h"

class MindMapGUIScene;

class GUIPresentationModel : public Subject
{
    public:
        GUIPresentationModel(MindMapModel*);
        ~GUIPresentationModel();
        void addRectangleDecorator();
        void addCircleDecorator();
        void addTriangleDecorator();
        void clearAllDecorator
        ();
        void loadMindMap(string);
        void selectComponent(int);
        void disableSelected();
        void editDescription(string, bool);
        void createMindMap(string, bool);
        void deleteComponent();
        void insertNode(char, string, bool);
        void saveMindMap(string);
        void draw(MindMapGUIScene*);
        void copyComponent();
        void cutComponent();
        void pasteComponent();
        string getMessage();
        bool getSaveMindMapActionEnable();
        bool getEditNodeActionEnable();
        bool getDeleteNodeActionEnable();
        bool getInsertChildActionEnable();
        bool getInsertSiblingActionEnable();
        bool getInsertParentActionEnable();
        bool getCopyActionEnbale();
        bool getCutActionEnbale();
        bool getPasteActionEnable();
        bool getUndoActionEnable();
        bool getRedoActionEnable();
        bool getAddDecoratorActionEnable();
        bool getClearAllDecoratorActionEnable();
        void undo();
        void redo();
    private:
        MindMapModel* _model;
        string _message;
        bool _saveMindMapActionEnable;
        bool _editNodeActionEnable;
        bool _deleteNodeActionEnable;
        bool _insertChildActionEnable;
        bool _insertSiblingActionEnable;
        bool _insertParentActionEnable;
        bool _copyActionEnbale;
        bool _cutActionEnbale;
        bool _pasteActionEnable;
        void disableAction();
        bool checkString(string, bool);
        bool _addDecoratorActionEnable;
        bool _clearAllDecoratorActionEnable;
};

