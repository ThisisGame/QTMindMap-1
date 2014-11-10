#include <gtest/gtest.h>
#include <fstream>
#include "MindMapModel.h"
#include <windows.h>
#include "TextUIPresentationModel.h"
#include "ConstVariables.h"

namespace MindMapTest
{
    class PresentationModelTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                CreateDirectory(L"testData", NULL);
                _model = new MindMapModel();
                _pModel = new TextUIPresentationModel(_model);
                _rootComputer = new Root(0, "Computer");
                _nodeNetwork = new Node(1, "Network");
                _nodeIPV4 = new Node(2, "IPV4");
                _nodeIPV6 = new Node(3, "IPV6");
                _nodeOS = new Node(4, "OS");
                _nodeMicrosoft = new Node(5, "Microsoft");
                _nodeWin7 = new Node(6, "Win7");
                _nodeWin8 = new Node(7, "Win8");
                _nodeOSX = new Node(8, "OSX");
                _rootComputer->addChild(_nodeNetwork);
                _rootComputer->addChild(_nodeOS);
                _nodeNetwork->addChild(_nodeIPV4);
                _nodeNetwork->addChild(_nodeIPV6);
                _nodeOS->addChild(_nodeMicrosoft);
                _nodeOS->addChild(_nodeOSX);
                _nodeMicrosoft->addChild(_nodeWin7);
                _nodeMicrosoft->addChild(_nodeWin8);
                _model->doInsertNode(_rootComputer);
                _model->doInsertNode(_nodeNetwork);
                _model->doInsertNode(_nodeIPV4);
                _model->doInsertNode(_nodeIPV6);
                _model->doInsertNode(_nodeOS);
                _model->doInsertNode(_nodeMicrosoft);
                _model->doInsertNode(_nodeWin7);
                _model->doInsertNode(_nodeWin8);
                _model->doInsertNode(_nodeOSX);
            }
            virtual void TearDown()
            {
                delete _model;
                delete _pModel;
                remove("testData\\test_file1.mm");
                RemoveDirectory(L"testData");
            }
            Root* _rootComputer;
            Node* _nodeNetwork;
            Node* _nodeIPV4;
            Node* _nodeIPV6;
            Node* _nodeOS;
            Node* _nodeMicrosoft;
            Node* _nodeWin7;
            Node* _nodeWin8;
            Node* _nodeOSX;
            MindMapModel* _model;
            TextUIPresentationModel* _pModel;
    };

    TEST_F(PresentationModelTest, testSelectMode)
    {
        _pModel->selectMode('1');
        ASSERT_EQ(CREATE_NEW_MINDMAP_MODE, _pModel->getMode());
        _pModel->selectMode('2');
        ASSERT_EQ(INSERT_NEW_NODE_MODE, _pModel->getMode());
        _pModel->selectMode('3');
        ASSERT_EQ(EDIT_NODE_MODE, _pModel->getMode());
        _pModel->selectMode('4');
        ASSERT_EQ(DISPLAY_MODE, _pModel->getMode());
        _pModel->selectMode('5');
        ASSERT_EQ(SAVE_MIND_MAP_MODE, _pModel->getMode());
        _pModel->selectMode('6');
        ASSERT_EQ(LOAD_MIND_MAP_MODE, _pModel->getMode());
        _pModel->selectMode('7');
        ASSERT_EQ(REDO_MODE, _pModel->getMode());
        _pModel->selectMode('8');
        ASSERT_EQ(UNDO_MODE, _pModel->getMode());
        _pModel->selectMode('9');
        ASSERT_EQ(EXIT_MODE, _pModel->getMode());
        _pModel->selectMode('a');
        ASSERT_STREQ(ERROR_INPUT_COMMAND, _pModel->getMessage().c_str());
    }

    TEST_F(PresentationModelTest, testInsertMode)
    {
        _model->selectComponent(0);
        _pModel->insertMode('a');
        ASSERT_STREQ(ERROR_ROOT_INSERT_PARENT, _pModel->getMessage().c_str());
        _pModel->insertMode('c');
        ASSERT_STREQ(ERROR_ROOT_INSERT_SIBLING, _pModel->getMessage().c_str());
        _pModel->insertMode('b');
        _pModel->insertMode('1');
        ASSERT_STREQ(ERROR_INPUT_COMMAND, _pModel->getMessage().c_str());
    }

    TEST_F(PresentationModelTest, testSetDescription)
    {
        _pModel->setDescription("iOS", ENTER_NODE_NAME_MODE);
        _model->selectComponent(8);
        ASSERT_STREQ("iOS", _model->getSelectComponent()->getDescription().c_str());
        _pModel->setDescription("MacOSX", CHANGE_DESCTIPTION_MODE);
        ASSERT_STREQ("MacOSX", _model->getSelectComponent()->getDescription().c_str());
        _pModel->setDescription("Network", CREATE_NEW_MINDMAP_MODE);
        _model->selectComponent(0);
        ASSERT_STREQ("Network", _model->getSelectComponent()->getDescription().c_str());
    }

    TEST_F(PresentationModelTest, testEditMode)
    {
        _model->selectComponent(0);
        _pModel->editMode('b');
        ASSERT_STREQ(ERROR_ROOT_CHANGE_PARENT, _pModel->getMessage().c_str());
        _pModel->editMode('c');
        ASSERT_STREQ(ERROR_ROOT_DELETE, _pModel->getMessage().c_str());
        _model->selectComponent(1);
        _pModel->editMode('a');
        ASSERT_EQ(CHANGE_DESCTIPTION_MODE, _pModel->getMode());
        _pModel->editMode('b');
        ASSERT_EQ(CHANGE_PARENT_MODE, _pModel->getMode());
        _pModel->editMode('c');
        ASSERT_EQ(MESSANGE_MODE, _pModel->getMode());
        _pModel->editMode('0');
        ASSERT_STREQ(ERROR_INPUT_COMMAND, _pModel->getMessage().c_str());
    }

    TEST_F(PresentationModelTest, testSelectComponent)
    {
        _pModel->selectComponent("a");
        ASSERT_STREQ(ERROR_INPUT_CHAR, _pModel->getMessage().c_str());
        _pModel->setMode(INSERT_NEW_NODE_MODE);
        _pModel->selectComponent("1");
        ASSERT_EQ(SELECT_INSERT_MODE, _pModel->getMode());
        _pModel->setMode(EDIT_NODE_MODE);
        _pModel->selectComponent("10");
        ASSERT_STREQ(ERROR_SELECT_NODE, _pModel->getMessage().c_str());
        _pModel->selectComponent("2");
        ASSERT_EQ(SELECT_EDIT_MODE, _pModel->getMode());
        _model->selectComponent(3);
        _pModel->setMode(CHANGE_PARENT_MODE);
        _pModel->selectComponent("2");
        ASSERT_EQ(MESSANGE_MODE, _pModel->getMode());
        _pModel->setMode(CHANGE_PARENT_MODE);
        _pModel->selectComponent("3");
        ASSERT_STREQ(ERROR_SELECT_ITSELF, _pModel->getMessage().c_str());
        _pModel->selectComponent("10");
        ASSERT_STREQ(ERROR_SELECT_NODE, _pModel->getMessage().c_str());
    }

    TEST_F(PresentationModelTest, testDisplay)
    {
        MindMapModel model;
        TextUIPresentationModel pModel(&model);
        string correctOutput;
        stringstream correntDisplay(correctOutput);
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-Network(Node, ID: 1)" << endl;
        correntDisplay << "  | +-IPV4(Node, ID: 2)" << endl;
        correntDisplay << "  | +-IPV6(Node, ID: 3)" << endl;
        correntDisplay << "  +-OS(Node, ID: 4)" << endl;
        correntDisplay << "    +-Microsoft(Node, ID: 5)" << endl;
        correntDisplay << "    | +-Win7(Node, ID: 6)" << endl;
        correntDisplay << "    | +-Win8(Node, ID: 7)" << endl;
        correntDisplay << "    +-OSX(Node, ID: 8)" << endl << endl;
        pModel.display();
        ASSERT_STREQ(ERROR_DISPLAY, pModel.getMessage().c_str());
        _pModel->display();
        ASSERT_STREQ(correntDisplay.str().c_str(), _pModel->getMessage().c_str());
    }

    TEST_F(PresentationModelTest, testSaveAndLoadMindMap)
    {
        MindMapModel model;
        TextUIPresentationModel pModel(&model);
        pModel.saveMindMap("testData\\test_file1.mm");
        ASSERT_STREQ(ERROR_SAVE, pModel.getMessage().c_str());
        _pModel->saveMindMap("");
        ASSERT_STREQ(ERROR_OPEN_FILE, _pModel->getMessage().c_str());
        _pModel->saveMindMap("testData\\test_file1.mm");
        _pModel->loadMindMap("");
        ASSERT_STREQ(ERROR_OPEN_FILE, _pModel->getMessage().c_str());
        _pModel->loadMindMap("testData\\test_file1.mm");
        string correctOutput;
        stringstream correntDisplay(correctOutput);
        correntDisplay << "The mind map Computer is displayed as follows:" << endl;
        correntDisplay << "+-Computer(Root, ID: 0)" << endl;
        correntDisplay << "  +-Network(Node, ID: 1)" << endl;
        correntDisplay << "  | +-IPV4(Node, ID: 2)" << endl;
        correntDisplay << "  | +-IPV6(Node, ID: 3)" << endl;
        correntDisplay << "  +-OS(Node, ID: 4)" << endl;
        correntDisplay << "    +-Microsoft(Node, ID: 5)" << endl;
        correntDisplay << "    | +-Win7(Node, ID: 6)" << endl;
        correntDisplay << "    | +-Win8(Node, ID: 7)" << endl;
        correntDisplay << "    +-OSX(Node, ID: 8)" << endl << endl;
        ASSERT_STREQ(correntDisplay.str().c_str(), _pModel->getMessage().c_str());
    }

    TEST_F(PresentationModelTest, testRedo)
    {
        _pModel->redo();
        ASSERT_STREQ(ERROR_REDO, _pModel->getMessage().c_str());
        _model->selectComponent(0);
        ASSERT_STREQ("Computer", _model->getSelectComponent()->getDescription().c_str());
        _model->changeDescription("ComputerScience");
        ASSERT_STREQ("ComputerScience", _model->getSelectComponent()->getDescription().c_str());
        _pModel->undo();
        ASSERT_STREQ("Computer", _model->getSelectComponent()->getDescription().c_str());
        _pModel->redo();
        ASSERT_STREQ("ComputerScience", _model->getSelectComponent()->getDescription().c_str());
    }

    TEST_F(PresentationModelTest, testUndo)
    {
        _pModel->undo();
        ASSERT_STREQ(ERROR_UNDO, _pModel->getMessage().c_str());
        _model->selectComponent(0);
        ASSERT_STREQ("Computer", _model->getSelectComponent()->getDescription().c_str());
        _model->changeDescription("ComputerScience");
        ASSERT_STREQ("ComputerScience", _model->getSelectComponent()->getDescription().c_str());
        _pModel->undo();
        ASSERT_STREQ("Computer", _model->getSelectComponent()->getDescription().c_str());
    }

    TEST_F(PresentationModelTest, testExitMode)
    {
        MindMapModel model;
        TextUIPresentationModel pModel(&model);
        _pModel->exitMode('a', "testData\\test_file1.mm");
        _pModel->loadMindMap("testData\\test_file1.mm");
        ASSERT_STREQ(ERROR_OPEN_FILE, _pModel->getMessage().c_str());
        _pModel->exitMode('Y', "testData\\test_file1.mm");
        _pModel->loadMindMap("testData\\test_file1.mm");
        ASSERT_EQ(9, _model->getNodeList().size());
        _pModel->exitMode('y', "testData\\test_file1.mm");
        _pModel->loadMindMap("testData\\test_file1.mm");
        ASSERT_EQ(9, _model->getNodeList().size());
    }
}