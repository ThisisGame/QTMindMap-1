#include <gtest/gtest.h>
#include <fstream>
#include "Root.h"
#include "Node.h"
#include "MindMapModel.h"
#include <windows.h>
#include "CircleDecorator.h"
#include "MockMindMapScene.h"

namespace MindMapTest
{
    class MindMapModelTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                CreateDirectory(L"testData", NULL);
                _model = new MindMapModel();
                _rootComputer = new Root(0, "Computer");
                _nodeNetwork = new Node(1, "Network");
                _nodeIPV4 = new Node(2, "IPV4");
                _nodeIPV6 = new Node(3, "IPV6");
                _nodeOS = new Node(4, "OS");
                _nodeMicrosoft = new Node(5, "Microsoft");
                _nodeWin7 = new Node(6, "Win7");
                _nodeWin8 = new Node(7, "Win8");
                _nodeOSX = new Node(8, "OSX");
                _circleDecorator = new CircleDecorator(9);
                _rootComputer->addChild(_nodeNetwork);
                _rootComputer->addChild(_nodeOS);
                _nodeNetwork->addChild(_nodeIPV4);
                _nodeNetwork->addChild(_nodeIPV6);
                _nodeOS->addChild(_nodeMicrosoft);
                _nodeOS->addChild(_nodeOSX);
                _nodeMicrosoft->addChild(_nodeWin7);
                _nodeMicrosoft->addChild(_nodeWin8);
                _components.push_back(_rootComputer);
                _components.push_back(_nodeNetwork);
                _components.push_back(_nodeIPV4);
                _components.push_back(_nodeIPV6);
                _components.push_back(_nodeOS);
                _components.push_back(_nodeMicrosoft);
                _components.push_back(_nodeWin7);
                _components.push_back(_nodeWin8);
                _components.push_back(_nodeOSX);
            }

            void deleteComponents()
            {
                delete _rootComputer;
            }

            Component* getCloneItem()
            {
                return _model->_cloneItem;
            }

            virtual void TearDown()
            {
                delete _model;
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
            CircleDecorator* _circleDecorator;
            list<Component*> _components;
            MindMapModel* _model;
    };

    TEST_F(MindMapModelTest, testCreateMindMap)
    {
        ASSERT_EQ(0, _model->getNodeList().size());
        _model->createMindMap("Computer");
        ASSERT_EQ(1, _model->getNodeList().size());
        _model->createMindMap("Network");
        ASSERT_EQ(1, _model->getNodeList().size());
        deleteComponents();
    }

    TEST_F(MindMapModelTest, testSelectComponent)
    {
        _model->createMindMap("Computer");
        ASSERT_TRUE(_model->selectComponent(0));
        ASSERT_STREQ("Computer", _model->getSelectComponent()->getDescription().c_str());
        ASSERT_FALSE(_model->selectComponent(1));
        ASSERT_EQ(NULL, _model->getSelectComponent());
        deleteComponents();
    }

    TEST_F(MindMapModelTest, testInsertNode)
    {
        _model->createMindMap("Computer");
        _model->selectComponent(0);
        ASSERT_THROW(_model->insertNode('a'), char*);
        ASSERT_THROW(_model->insertNode('c'), char*);
        _model->insertNode('b');
        _model->selectComponent(1);
        _model->insertNode('a');
        ASSERT_EQ(3, _model->getNodeList().size());
        _model->insertNode('b');
        ASSERT_EQ(4, _model->getNodeList().size());
        _model->insertNode('c');
        ASSERT_EQ(5, _model->getNodeList().size());
        deleteComponents();
    }

    TEST_F(MindMapModelTest, testDoInsertNode)
    {
        Node* node = new Node(0, "Network");
        _model->doInsertNode(node);
        ASSERT_EQ(1, _model->getNodeList().size());
        deleteComponents();
    }

    TEST_F(MindMapModelTest, testDoUninsertNode)
    {
        Node node(0, "Network");
        _model->doInsertNode(&node);
        ASSERT_EQ(1, _model->getNodeList().size());
        _model->doUninsertNode(&node);
        ASSERT_EQ(0, _model->getNodeList().size());
        deleteComponents();
    }

    TEST_F(MindMapModelTest, testSetDescription)
    {
        _model->createMindMap("Computer");
        _model->selectComponent(0);
        _model->insertNode('b');
        _model->setDescription("Network");
        _model->selectComponent(1);
        ASSERT_STREQ("Network", _model->getSelectComponent()->getDescription().c_str());
        deleteComponents();
    }

    TEST_F(MindMapModelTest, testChangeDescription)
    {
        _model->createMindMap("Computer");
        _model->selectComponent(0);
        _model->insertNode('b');
        _model->setDescription("IPV4");
        _model->selectComponent(1);
        ASSERT_STREQ("IPV4", _model->getSelectComponent()->getDescription().c_str());
        _model->changeDescription("IPV6");
        ASSERT_STREQ("IPV6", _model->getSelectComponent()->getDescription().c_str());
        deleteComponents();
    }

    TEST_F(MindMapModelTest, testChangeParent)
    {
        _model->createMindMap("Computer");
        _model->selectComponent(0);
        _model->insertNode('b');
        _model->setDescription("Network");
        _model->selectComponent(1);
        _model->insertNode('b');
        _model->setDescription("IPV6");
        _model->selectComponent(1);
        ASSERT_EQ(0, _model->getSelectComponent()->getParent()->getId());
        _model->changeParent(2);
        ASSERT_EQ(2, _model->getSelectComponent()->getParent()->getId());
        deleteComponents();
    }

    TEST_F(MindMapModelTest, testDeleteComponent)
    {
        _model->createMindMap("Computer");
        _model->selectComponent(0);
        _model->insertNode('b');
        _model->setDescription("Network");
        _model->selectComponent(1);
        ASSERT_EQ(2, _model->getNodeList().size());
        _model->deleteComponent();
        ASSERT_EQ(1, _model->getNodeList().size());
        deleteComponents();
    }

    TEST_F(MindMapModelTest, testDoAddNodes)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
    }

    TEST_F(MindMapModelTest, testDoDeleteNode)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
        _model->doDeleteNode(_nodeIPV4);
        ASSERT_EQ(8, _model->getNodeList().size());
    }

    TEST_F(MindMapModelTest, testIsRoot)
    {
        _model->doAddNodes(_components);
        _model->selectComponent(0);
        ASSERT_TRUE(_model->isRoot());
        _model->selectComponent(2);
        ASSERT_FALSE(_model->isRoot());
    }

    TEST_F(MindMapModelTest, testDisplay)
    {
        string correctOutput;
        stringstream correntDisplay(correctOutput);
        ASSERT_THROW(_model->display(), char*);
        _model->doAddNodes(_components);
        _model->display();
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
        ASSERT_STREQ(correntDisplay.str().c_str(), _model->getMessage().c_str());
    }

    TEST_F(MindMapModelTest, testRedo)
    {
        _model->doAddNodes(_components);
        ASSERT_THROW(_model->redo(), char*);
        _model->selectComponent(0);
        ASSERT_STREQ("Computer", _model->getSelectComponent()->getDescription().c_str());
        _model->changeDescription("ComputerScience");
        ASSERT_STREQ("ComputerScience", _model->getSelectComponent()->getDescription().c_str());
        _model->undo();
        ASSERT_STREQ("Computer", _model->getSelectComponent()->getDescription().c_str());
        _model->redo();
        ASSERT_STREQ("ComputerScience", _model->getSelectComponent()->getDescription().c_str());
        ASSERT_THROW(_model->redo(), char*);
    }

    TEST_F(MindMapModelTest, testUndo)
    {
        _model->doAddNodes(_components);
        ASSERT_THROW(_model->undo(), char*);
        _model->selectComponent(0);
        ASSERT_STREQ("Computer", _model->getSelectComponent()->getDescription().c_str());
        _model->changeDescription("ComputerScience");
        ASSERT_STREQ("ComputerScience", _model->getSelectComponent()->getDescription().c_str());
        _model->undo();
        ASSERT_STREQ("Computer", _model->getSelectComponent()->getDescription().c_str());
        ASSERT_THROW(_model->undo(), char*);
    }

    TEST_F(MindMapModelTest, testLoadMindMap)
    {
        string correctOutput;
        stringstream correntDisplay(correctOutput);
        MindMapModel model;
        ASSERT_THROW(_model->saveMindMap("testData\\test_file1.mm"), char*);
        _model->doAddNodes(_components);
        ASSERT_THROW(_model->saveMindMap(""), char*);
        _model->selectComponent(5);
        _model->addCircleDecorator();
        _model->saveMindMap("testData\\test_file1.mm");
        ASSERT_THROW(model.loadMindMap("testData\\file_not_find.mm"), char*);
        model.loadMindMap("testData\\test_file1.mm");
        model.display();
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
        ASSERT_STREQ(correntDisplay.str().c_str(), model.getMessage().c_str());
    }

    TEST_F(MindMapModelTest, testDisableSelected)
    {
        _model->doAddNodes(_components);
        ASSERT_TRUE(_model->selectComponent(0));
        ASSERT_TRUE(_model->getSelectComponent()->getSelected());
        _model->disableSelected();
        ASSERT_FALSE(_model->getSelectComponent()->getSelected());
    }

    TEST_F(MindMapModelTest, testCutComponent)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
        _model->selectComponent(5);
        _model->cutComponent();
        ASSERT_STREQ(getCloneItem()->getDescription().c_str(), _model->getSelectComponent()->getDescription().c_str());
        ASSERT_EQ(6, _model->getNodeList().size());
        ASSERT_NE(getCloneItem(), _model->getSelectComponent());
    }

    TEST_F(MindMapModelTest, testPasteComponent)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
        _model->selectComponent(5);
        _model->cutComponent();
        _model->pasteComponent();
        ASSERT_EQ(9, _model->getNodeList().size());
    }

    TEST_F(MindMapModelTest, testCloneItem)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
        _model->selectComponent(5);
        _model->cloneItem();
        ASSERT_STREQ("Microsoft", getCloneItem()->getDescription().c_str());
        ASSERT_EQ(9, _model->getNodeList().size());
        ASSERT_NE(getCloneItem(), _model->getSelectComponent());
    }

    TEST_F(MindMapModelTest, testDoCutNodes)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
        _model->selectComponent(5);
        _model->doCutNodes(_model->getSelectComponent());
        ASSERT_EQ(6, _model->getNodeList().size());
    }

    TEST_F(MindMapModelTest, testPasteNodes)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
        _model->selectComponent(5);
        _model->cloneItem();
        _model->doPasteNodes(getCloneItem());
        ASSERT_EQ(12, _model->getNodeList().size());
    }

    TEST_F(MindMapModelTest, testIsCanRedo)
    {
        _model->doAddNodes(_components);
        ASSERT_FALSE(_model->isCanRedo());
        _model->selectComponent(0);
        _model->changeDescription("ComputerScience");
        ASSERT_FALSE(_model->isCanRedo());
        _model->undo();
        ASSERT_TRUE(_model->isCanRedo());
        _model->redo();
    }

    TEST_F(MindMapModelTest, testIsCanUedo)
    {
        _model->doAddNodes(_components);
        ASSERT_FALSE(_model->isCanUndo());
        _model->selectComponent(0);
        _model->changeDescription("ComputerScience");
        ASSERT_TRUE(_model->isCanUndo());
    }

    TEST_F(MindMapModelTest, testAddRectangleDecorator)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
        _model->selectComponent(0);
        _model->addRectangleDecorator();
        ASSERT_EQ(10, _model->getNodeList().size());
    }

    TEST_F(MindMapModelTest, testAddCircleDecorator)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
        _model->selectComponent(5);
        _model->addCircleDecorator();
        ASSERT_EQ(10, _model->getNodeList().size());
    }

    TEST_F(MindMapModelTest, testAddTriangleDecorator)
    {
        _model->doAddNodes(_components);
        ASSERT_EQ(9, _model->getNodeList().size());
        _model->selectComponent(2);
        _model->addTriangleDecorator();
        ASSERT_EQ(10, _model->getNodeList().size());
    }

    TEST_F(MindMapModelTest, testClearAllDecorator)
    {
        _model->doAddNodes(_components);
        _model->selectComponent(3);
        _model->addTriangleDecorator();
        _model->addTriangleDecorator();
        _model->addTriangleDecorator();
        ASSERT_EQ(12, _model->getNodeList().size());
        _model->selectComponent(3);
        _model->clearAllDecorator();
        ASSERT_EQ(9, _model->getNodeList().size());
    }

    TEST_F(MindMapModelTest, testIsHaveDecorator)
    {
        _model->doAddNodes(_components);
        _model->selectComponent(8);
        _model->addTriangleDecorator();
        _model->addTriangleDecorator();
        _model->addTriangleDecorator();
        ASSERT_TRUE(_model->isHaveDecorator());
        _model->selectComponent(0);
        ASSERT_FALSE(_model->isHaveDecorator());
        _model->selectComponent(5);
        ASSERT_FALSE(_model->isHaveDecorator());
    }

    TEST_F(MindMapModelTest, testSimpleExpend)
    {
        _model->doAddNodes(_components);
        ASSERT_TRUE(_rootComputer->isExpend());
        ASSERT_TRUE(_nodeNetwork->isExpend());
        ASSERT_TRUE(_nodeOS->isExpend());
        _model->selectComponent(0);
        _model->simpleExpend();
        ASSERT_FALSE(_rootComputer->isExpend());
        ASSERT_TRUE(_nodeNetwork->isExpend());
        ASSERT_TRUE(_nodeOS->isExpend());
        _model->simpleExpend();
        ASSERT_TRUE(_rootComputer->isExpend());
        ASSERT_TRUE(_nodeNetwork->isExpend());
        ASSERT_TRUE(_nodeOS->isExpend());
    }

    TEST_F(MindMapModelTest, testAllExpend)
    {
        _model->doAddNodes(_components);
        ASSERT_TRUE(_rootComputer->isExpend());
        ASSERT_TRUE(_nodeNetwork->isExpend());
        ASSERT_TRUE(_nodeOS->isExpend());
        ASSERT_TRUE(_nodeOSX->isExpend());
        _model->selectComponent(0);
        _model->allExpend();
        ASSERT_FALSE(_rootComputer->isExpend());
        ASSERT_FALSE(_nodeNetwork->isExpend());
        ASSERT_FALSE(_nodeOS->isExpend());
        ASSERT_FALSE(_nodeOSX->isExpend());
        _model->allExpend();
        ASSERT_TRUE(_rootComputer->isExpend());
        ASSERT_TRUE(_nodeNetwork->isExpend());
        ASSERT_TRUE(_nodeOS->isExpend());
        ASSERT_TRUE(_nodeOSX->isExpend());
    }

    TEST_F(MindMapModelTest, testDown)
    {
        _model->doAddNodes(_components);
        _model->selectComponent(6);
        _model->down();
        for (auto item : _nodeMicrosoft->getNodeList())
        {
            ASSERT_EQ(_nodeWin8, item);
            break;
        }
    }

    TEST_F(MindMapModelTest, testUp)
    {
        _model->doAddNodes(_components);
        _model->selectComponent(7);
        _model->up();
        for (auto item : _nodeMicrosoft->getNodeList())
        {
            ASSERT_EQ(_nodeWin8, item);
            break;
        }
    }

    TEST_F(MindMapModelTest, testIsCanUp)
    {
        _model->doAddNodes(_components);
        _model->selectComponent(0);
        ASSERT_FALSE(_model->isCanUp());
        _model->selectComponent(6);
        ASSERT_FALSE(_model->isCanUp());
        _model->selectComponent(7);
        ASSERT_TRUE(_model->isCanUp());
    }

    TEST_F(MindMapModelTest, testIsCanDown)
    {
        _model->doAddNodes(_components);
        _model->selectComponent(0);
        ASSERT_FALSE(_model->isCanDown());
        _model->selectComponent(7);
        ASSERT_FALSE(_model->isCanDown());
        _model->selectComponent(6);
        ASSERT_TRUE(_model->isCanDown());
    }

    TEST_F(MindMapModelTest, testDraw)
    {
        MockMindMapScene scene;
        _model->draw(&scene);
        _model->doAddNodes(_components);
        _model->draw(&scene);
    }
}