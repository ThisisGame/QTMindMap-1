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
        void createActions();

};

