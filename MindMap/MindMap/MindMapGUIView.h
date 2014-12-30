#pragma once
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>
#include "MindMapGUIScene.h"
#include "GUIPresentationModel.h"
#include "Observer.h"

QT_BEGIN_NAMESPACE

class MindMapGUIView : public QMainWindow, public Observer
{
        Q_OBJECT
    public:
        MindMapGUIView(MindMapModel*, QWidget* parent = 0);
        ~MindMapGUIView();
        void updateView();
        void updateError();
    private slots:
        void openFile();
        void updateActions();
        void editDescription();
        void createMindMap();
        void deleteComponent();
        void insertSibling();
        void insertParent();
        void insertChild();
        void saveFile();
        void aboutActionClick();
        void copyComponent();
        void cutComponent();
        void pasteComponent();
        void redo();
        void undo();
        void addRectangleDecorator();
        void addCircleDecorator();
        void addTriangleDecorator();
        void clearDecorator();
        void simpleExpend();
        void allExpend();
        void up();
        void down();
    protected:
        virtual void mousePressEvent(QMouseEvent*);
        virtual void mouseDoubleClickEvent(QMouseEvent*);
    private:
        GUIPresentationModel* _pModel;
        QMenuBar* _menuBar;
        QMenu* _fileMenuBar;
        QMenu* _editMenuBar;
        QMenu* _helpMenuBar;
        QToolBar* _mainToolBar;
        QToolBar* _funcionailToolBar;
        MindMapGUIScene* _scene;
        QGraphicsView* _view;
        QAction* _createNewMindMapAction;
        QAction* _openMindMapAction;
        QAction* _saveMindMapAction;
        QAction* _editNodeAction;
        QAction* _deleteNodeAction;
        QAction* _insertChildAction;
        QAction* _insertSiblingAction;
        QAction* _insertParentAction;
        QAction* _aboutAction;
        QAction* _cutAction;
        QAction* _copyAction;
        QAction* _pasteAction;
        QAction* _redoAction;
        QAction* _undoAction;
        QAction* _addTriangleAction;
        QAction* _addCircleAction;
        QAction* _addRectangleAction;
        QAction* _clearDecoratorAction;
        QAction* _simpleExpendAction;
        QAction* _allExpendAction;
        QAction* _upAction;
        QAction* _downAction;
        void setupString();
        void setupMenu();
        void setupToolbar();
        void setupView();
        void createActions();
        void connectEvents();
        void insertNode(char, QString);
        QString INSERT_CHILD_STRING;
        QString INSERT_SIBLING_STRING;
        QString INSERT_PARENT_STRING;
        QString EDIT_STRING;
        QString DELETE_STRING;
        QString OPEN_MINDMAP_STRING;
        QString SAVE_MINEMAP_STRING;
        QString CREATE_MINDMAP_STRING;
        QString ABOUT_STRING;
        QString INIT_FILEPATH_STRING;
        QString DEFAULT_FILE_TYPE_STRING;
        QString COPY_STRING;
        QString CUT_STRING;
        QString PASTE_STRING;
        QString REDO_STRING;
        QString UNDO_STRING;
        QString ADD_TRIANGLE_STRING;
        QString ADD_CIRCLE_STRING;
        QString ADD_RECTANGLE_STRING;
        QString CLEAR_DECORATOR_STRING;
        QString SIMPLE_EXPEND_STRING;
        QString ALL_EXPEND_STRING;
        QString UP_STRING;
        QString DOWN_STRING;
};

