#include "MindMapGUIView.h"
#include "MindMapModel.h"
#include <iostream>
#include <QtWidgets/QMessageBox>
using namespace std;

MindMapGUIView::MindMapGUIView(MindMapModel* model, QWidget* parent) : QMainWindow(parent)
{
    this->setWindowTitle("MindMap");
    this->resize(600, 400);
    _pModel = new GUIPresentationModel(model);
    _pModel->attach(this);
    //setup
    setupString();
    createActions();
    setupMenu();
    setupToolbar();
    setupView();
    connectEvents();
    updateActions();
}

MindMapGUIView::~MindMapGUIView()
{
}

void MindMapGUIView::setupMenu()
{
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
    _editMenuBar->addSeparator();
    _editMenuBar->addAction(_cutAction);
    _editMenuBar->addAction(_copyAction);
    _editMenuBar->addAction(_pasteAction);
    //helpMenu
    _helpMenuBar->addAction(_aboutAction);
}

void MindMapGUIView::setupToolbar()
{
    //ToolBar
    _mainToolBar = new QToolBar(this);
    this->addToolBar(_mainToolBar);
    _mainToolBar->addAction(_createNewMindMapAction);
    _mainToolBar->addAction(_openMindMapAction);
    _mainToolBar->addAction(_saveMindMapAction);
    _mainToolBar->addSeparator();
    _mainToolBar->addAction(_cutAction);
    _mainToolBar->addAction(_copyAction);
    _mainToolBar->addAction(_pasteAction);
    _mainToolBar->addSeparator();
    _mainToolBar->addAction(_editNodeAction);
    _mainToolBar->addAction(_deleteNodeAction);
    _mainToolBar->addSeparator();
    _mainToolBar->addAction(_insertChildAction);
    _mainToolBar->addAction(_insertSiblingAction);
    _mainToolBar->addAction(_insertParentAction);
    _mainToolBar->addSeparator();
    _mainToolBar->addAction(_undoAction);
    _mainToolBar->addAction(_redoAction);
    _funcionailToolBar = new QToolBar(this);
    this->addToolBarBreak();
    this->addToolBar(Qt::TopToolBarArea, _funcionailToolBar);
    _funcionailToolBar->addAction(_addRectangleAction);
    _funcionailToolBar->addAction(_addCircleAction);
    _funcionailToolBar->addAction(_addTriangleAction);
    _funcionailToolBar->addSeparator();
    _funcionailToolBar->addAction(_clearDecoratorAction);
    _funcionailToolBar->addSeparator();
    _funcionailToolBar->addAction(_simpleExpendAction);
    _funcionailToolBar->addAction(_allExpendAction);
    _funcionailToolBar->addSeparator();
    _funcionailToolBar->addAction(_upAction);
    _funcionailToolBar->addAction(_downAction);
}

void MindMapGUIView::setupView()
{
    //view
    _scene = new MindMapGUIScene(_pModel, this);
    _view = new QGraphicsView(_scene);
    this->setCentralWidget(_view);
}

void MindMapGUIView::setupString()
{
    INSERT_CHILD_STRING = "Insert a Child";
    INSERT_SIBLING_STRING = "Insert a Sibling";
    INSERT_PARENT_STRING = "Insert a Parent";
    EDIT_STRING = "Edit";
    DELETE_STRING = "Delete";
    OPEN_MINDMAP_STRING = "Open a mind map";
    SAVE_MINEMAP_STRING = "Save a mind map";
    CREATE_MINDMAP_STRING = "Create a new mind map";
    ABOUT_STRING = "About";
    INIT_FILEPATH_STRING = ".\\";
    DEFAULT_FILE_TYPE_STRING = "MindMap Files (*.mm)";
    CUT_STRING = "Cut";
    COPY_STRING = "Copy";
    PASTE_STRING = "Paste";
    REDO_STRING = "Redo";
    UNDO_STRING = "Undo";
    ADD_TRIANGLE_STRING = "Add triangle decorator";
    ADD_CIRCLE_STRING = "Add circle decorator";
    ADD_RECTANGLE_STRING = "Add rectangle decorator";
    CLEAR_DECORATOR_STRING = "Clear all decorator";
    SIMPLE_EXPEND_STRING = "Expend/Collapse";
    ALL_EXPEND_STRING = "Expend/Collapse All";
    UP_STRING = "Up";
    DOWN_STRING = "Down";
}

void MindMapGUIView::connectEvents()
{
    //connectEven
    connect(_openMindMapAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(_editNodeAction, SIGNAL(triggered()), this, SLOT(editDescription()));
    connect(_createNewMindMapAction, SIGNAL(triggered()), this, SLOT(createMindMap()));
    connect(_deleteNodeAction, SIGNAL(triggered()), this, SLOT(deleteComponent()));
    connect(_insertParentAction, SIGNAL(triggered()), this, SLOT(insertParent()));
    connect(_insertChildAction, SIGNAL(triggered()), this, SLOT(insertChild()));
    connect(_insertSiblingAction, SIGNAL(triggered()), this, SLOT(insertSibling()));
    connect(_saveMindMapAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(_aboutAction, SIGNAL(triggered()), this, SLOT(aboutActionClick()));
    connect(_copyAction, SIGNAL(triggered()), this, SLOT(copyComponent()));
    connect(_cutAction, SIGNAL(triggered()), this, SLOT(cutComponent()));
    connect(_pasteAction, SIGNAL(triggered()), this, SLOT(pasteComponent()));
    connect(_undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    connect(_redoAction, SIGNAL(triggered()), this, SLOT(redo()));
    //
    connect(_addTriangleAction, SIGNAL(triggered()), this, SLOT(addTriangleDecorator()));
    connect(_addCircleAction, SIGNAL(triggered()), this, SLOT(addCircleDecorator()));
    connect(_addRectangleAction, SIGNAL(triggered()), this, SLOT(addRectangleDecorator()));
    connect(_clearDecoratorAction, SIGNAL(triggered()), this, SLOT(clearDecorator()));
    connect(_simpleExpendAction, SIGNAL(triggered()), this, SLOT(simpleExpend()));
    connect(_allExpendAction, SIGNAL(triggered()), this, SLOT(allExpend()));
    connect(_upAction, SIGNAL(triggered()), this, SLOT(up()));
    connect(_downAction, SIGNAL(triggered()), this, SLOT(down()));
}
void MindMapGUIView::createActions()
{
    _createNewMindMapAction = new QAction(QIcon("icons/createNewMindMap.png"), CREATE_MINDMAP_STRING, this);
    _openMindMapAction = new QAction(QIcon("icons/openMindMap.png"), OPEN_MINDMAP_STRING, this);
    _saveMindMapAction = new QAction(QIcon("icons/saveMindMap.png"), SAVE_MINEMAP_STRING, this);
    _editNodeAction = new QAction(QIcon("icons/editNode.png"), EDIT_STRING, this);
    _deleteNodeAction = new QAction(QIcon("icons/deleteNode.png"), DELETE_STRING, this);
    _insertChildAction = new QAction(QIcon("icons/insertChild.png"), INSERT_CHILD_STRING, this);
    _insertSiblingAction = new QAction(QIcon("icons/insertSibling.png"), INSERT_SIBLING_STRING, this);
    _insertParentAction = new QAction(QIcon("icons/insertParent.png"), INSERT_PARENT_STRING, this);
    _aboutAction = new QAction(QIcon("icons/about.png"), ABOUT_STRING, this);
    _cutAction = new QAction(QIcon("icons/cut.png"), CUT_STRING, this);
    _copyAction = new QAction(QIcon("icons/copy.png"), COPY_STRING, this);
    _pasteAction = new QAction(QIcon("icons/paste.png"), PASTE_STRING, this);
    _undoAction = new QAction(QIcon("icons/undo.png"), UNDO_STRING, this);
    _redoAction = new QAction(QIcon("icons/redo.png"), REDO_STRING, this);
    //
    _addTriangleAction = new QAction(QIcon("icons/triangle.png"), ADD_TRIANGLE_STRING, this);
    _addCircleAction = new QAction(QIcon("icons/circle.png"), ADD_CIRCLE_STRING, this);
    _addRectangleAction = new QAction(QIcon("icons/rectangle.png"), ADD_RECTANGLE_STRING, this);
    _clearDecoratorAction = new QAction(QIcon("icons/clearDecorator.png"), CLEAR_DECORATOR_STRING, this);
    _simpleExpendAction = new QAction(QIcon("icons/simpleExpend.png"), SIMPLE_EXPEND_STRING, this);
    _allExpendAction = new QAction(QIcon("icons/allExpend.png"), ALL_EXPEND_STRING, this);
    _upAction = new QAction(QIcon("icons/up.png"), UP_STRING, this);
    _downAction = new QAction(QIcon("icons/down.png"), DOWN_STRING, this);
}

void MindMapGUIView::up()
{
    _pModel->up();
}

void MindMapGUIView::down()
{
    _pModel->down();
}

void MindMapGUIView::allExpend()
{
    _pModel->allExpend();
}

void MindMapGUIView::simpleExpend()
{
    _pModel->simpleExpend();
}

void MindMapGUIView::addTriangleDecorator()
{
    _pModel->addTriangleDecorator();
}

void MindMapGUIView::addRectangleDecorator()
{
    _pModel->addRectangleDecorator();
}

void MindMapGUIView::addCircleDecorator()
{
    _pModel->addCircleDecorator();
}

void MindMapGUIView::clearDecorator()
{
    _pModel->clearAllDecorator();
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
    _copyAction->setEnabled(_pModel->getCopyActionEnbale());
    _cutAction->setEnabled(_pModel->getCutActionEnbale());
    _pasteAction->setEnabled(_pModel->getPasteActionEnable());
    _undoAction->setEnabled(_pModel->getUndoActionEnable());
    _redoAction->setEnabled(_pModel->getRedoActionEnable());
    _addRectangleAction->setEnabled(_pModel->getAddDecoratorActionEnable());
    _addCircleAction->setEnabled(_pModel->getAddDecoratorActionEnable());
    _addTriangleAction->setEnabled(_pModel->getAddDecoratorActionEnable());
    _clearDecoratorAction->setEnabled(_pModel->getClearAllDecoratorActionEnable());
    _simpleExpendAction->setEnabled(_pModel->getAddDecoratorActionEnable());
    _allExpendAction->setEnabled(_pModel->getAddDecoratorActionEnable());
    _upAction->setEnabled(_pModel->getUpActionEnable());
    _downAction->setEnabled(_pModel->getDownActionEnable());
    _funcionailToolBar->setVisible(_pModel->getAddDecoratorActionEnable());
}

void MindMapGUIView::aboutActionClick()
{
    QMessageBox::about(NULL, "About", "<center><h2>2014POSD < / h2 > 103598002<br>Kuan - Ting Chen < / center > ");
}

void MindMapGUIView::openFile()
{
    QString filePath;
    filePath = QFileDialog::getOpenFileName(this, OPEN_MINDMAP_STRING, INIT_FILEPATH_STRING, DEFAULT_FILE_TYPE_STRING);
    _pModel->loadMindMap(filePath.toStdString());
}

void MindMapGUIView::saveFile()
{
    QString filePath;
    filePath = QFileDialog::getSaveFileName(this, SAVE_MINEMAP_STRING, INIT_FILEPATH_STRING, DEFAULT_FILE_TYPE_STRING);
    _pModel->saveMindMap(filePath.toStdString());
}

void MindMapGUIView::editDescription()
{
    bool result;
    QString text = QInputDialog::getText(this, EDIT_STRING, "Please input your description", QLineEdit::Normal, QString::null, &result);
    _pModel->editDescription(text.toStdString(), result);
}

void MindMapGUIView::createMindMap()
{
    bool result;
    QString text = QInputDialog::getText(this, "New MindMap", "Please input your topic", QLineEdit::Normal, QString::null, &result);
    _pModel->createMindMap(text.toStdString(), result);
}

void MindMapGUIView::insertParent()
{
    insertNode('a', INSERT_PARENT_STRING);
}

void MindMapGUIView::insertChild()
{
    insertNode('b', INSERT_CHILD_STRING);
}

void MindMapGUIView::insertSibling()
{
    insertNode('c', INSERT_SIBLING_STRING);
}

void MindMapGUIView::insertNode(char mode, QString title)
{
    bool result;
    QString text = QInputDialog::getText(this, title, "Please input your description", QLineEdit::Normal, QString::null, &result);
    _pModel->insertNode(mode, text.toStdString(), result);
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

void MindMapGUIView::copyComponent()
{
    _pModel->copyComponent();
}

void MindMapGUIView::cutComponent()
{
    _pModel->cutComponent();
}

void MindMapGUIView::pasteComponent()
{
    _pModel->pasteComponent();
}

void MindMapGUIView::redo()
{
    _pModel->redo();
}

void MindMapGUIView::undo()
{
    _pModel->undo();
}