#include "MindMapGUIView.h"
#include "MindMapModel.h"
#include <iostream>
#include <QtWidgets/QMessageBox>
using namespace std;

MindMapGUIView::MindMapGUIView(MindMapModel* model, QWidget* parent) : QMainWindow(parent)
{
    _pModel = new GUIPresentationModel(model);
    _pModel->attach(this);
    this->setWindowTitle("MindMap");
    this->resize(600, 400);
    //Actions
    createActions();
    //MenuBar
    _menuBar = new QMenuBar(this);
    _fileMenuBar = _menuBar->addMenu("File");
    _editMenuBar = _menuBar->addMenu("Edit");
    _helpMenuBar = _menuBar->addMenu("Help");
    this->setMenuBar(_menuBar);
    //fileMenu
    _fileMenuBar->addAction(_createNewMindMapAction);
    _fileMenuBar->addAction(_openMindMapAction);
    _fileMenuBar->addAction(_saveMindMapAction);
    //editMenu
    _editMenuBar->addAction(_editNodeAction);
    _editMenuBar->addAction(_deleteNodeAction);
    _editMenuBar->addSeparator();
    _editMenuBar->addAction(_insertChildAction);
    _editMenuBar->addAction(_insertSiblingAction);
    _editMenuBar->addAction(_insertParentAction);
    //helpMenu
    _helpMenuBar->addAction(_aboutAction);
    //ToolBar
    _mainToolBar = new QToolBar(this);
    this->addToolBar(_mainToolBar);
    _mainToolBar->addAction(_createNewMindMapAction);
    _mainToolBar->addAction(_openMindMapAction);
    _mainToolBar->addAction(_saveMindMapAction);
    _mainToolBar->addSeparator();
    _mainToolBar->addAction(_editNodeAction);
    _mainToolBar->addAction(_deleteNodeAction);
    _mainToolBar->addSeparator();
    _mainToolBar->addAction(_insertChildAction);
    _mainToolBar->addAction(_insertSiblingAction);
    _mainToolBar->addAction(_insertParentAction);
    //view
    _scene = new MindMapGUIScene(_pModel, this);
    _view = new QGraphicsView(_scene);
    this->setCentralWidget(_view);
    //connectEven
    connect(_openMindMapAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(_editNodeAction, SIGNAL(triggered()), this, SLOT(editDescription()));
    connect(_createNewMindMapAction, SIGNAL(triggered()), this, SLOT(createMindMap()));
    connect(_deleteNodeAction, SIGNAL(triggered()), this, SLOT(deleteComponent()));
    connect(_insertParentAction, SIGNAL(triggered()), this, SLOT(insertParent()));
    connect(_insertChildAction, SIGNAL(triggered()), this, SLOT(insertChild()));
    connect(_insertSiblingAction, SIGNAL(triggered()), this, SLOT(insertSibling()));
    connect(_saveMindMapAction, SIGNAL(triggered()), this, SLOT(saveFile()));
}


MindMapGUIView::~MindMapGUIView()
{
}

void MindMapGUIView::createActions()
{
    _createNewMindMapAction = new QAction(QIcon("icons/createNewMindMap.png"), "Create a new mind map", this);
    _openMindMapAction = new QAction(QIcon("icons/openMindMap.png"), "Open a mind map", this);
    _saveMindMapAction = new QAction(QIcon("icons/saveMindMap.png"), "Save a mind map", this);
    _editNodeAction = new QAction(QIcon("icons/editNode.png"), "Edit", this);
    _deleteNodeAction = new QAction(QIcon("icons/deleteNode.png"), "Delete", this);
    _insertChildAction = new QAction(QIcon("icons/insertChild.png"), "Insert a Child", this);
    _insertSiblingAction = new QAction(QIcon("icons/insertSibling.png"), "Insert a Sibling", this);
    _insertParentAction = new QAction(QIcon("icons/insertParent.png"), "Insert a Parent", this);
    _aboutAction = new QAction(QIcon("icons/about.png"), "About", this);
    updateActions();
}

void MindMapGUIView::updateView()
{
    updateActions();
    _scene->draw();
}

void MindMapGUIView::updateError()
{
    QMessageBox::critical(this, "Error", QString::fromStdString(_pModel->getMessage()));
}

void MindMapGUIView::updateActions()
{
    _saveMindMapAction->setEnabled(_pModel->getSaveMindMapActionEnable());
    _editNodeAction->setEnabled(_pModel->getEditNodeActionEnable());
    _deleteNodeAction->setEnabled(_pModel->getDeleteNodeActionEnable());
    _insertChildAction->setEnabled(_pModel->getInsertChildActionEnable());
    _insertSiblingAction->setEnabled(_pModel->getInsertSiblingActionEnable());
    _insertParentAction->setEnabled(_pModel->getInsertParentActionEnable());
}

void MindMapGUIView::openFile()
{
    QString filePath;
    filePath = QFileDialog::getOpenFileName(this, "Open File", "C:\\", "MindMap Files (*.mm)");
    _pModel->loadMindMap(filePath.toStdString());
}

void MindMapGUIView::saveFile()
{
    QString filePath;
    filePath = QFileDialog::getSaveFileName(this, "Save File", ".\\", "MindMap Files (*.mm)");
    //_pModel->save(filePath.toStdString());
}

void MindMapGUIView::editDescription()
{
    QString text = QInputDialog::getText(this, "Input", "Please input your description", QLineEdit::Normal);
    _pModel->editDescription(text.toStdString());
}

void MindMapGUIView::createMindMap()
{
    QString text = QInputDialog::getText(this, "Input", "Please input your topic", QLineEdit::Normal);
    _pModel->createMindMap(text.toStdString());
}

void MindMapGUIView::insertParent()
{
    QString text = QInputDialog::getText(this, "Input", "Please input your description", QLineEdit::Normal);
    _pModel->insertNode('a', text.toStdString());
}

void MindMapGUIView::insertChild()
{
    QString text = QInputDialog::getText(this, "Input", "Please input your description", QLineEdit::Normal);
    _pModel->insertNode('b', text.toStdString());
}

void MindMapGUIView::insertSibling()
{
    QString text = QInputDialog::getText(this, "Input", "Please input your description", QLineEdit::Normal);
    _pModel->insertNode('c', text.toStdString());
}

void MindMapGUIView::deleteComponent()
{
    _pModel->deleteComponent();
}

void MindMapGUIView::mousePressEvent(QMouseEvent* event)
{
    QMainWindow::mousePressEvent(event);
    _pModel->disableSelected();
}

void MindMapGUIView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QMainWindow::mouseDoubleClickEvent(event);
}
