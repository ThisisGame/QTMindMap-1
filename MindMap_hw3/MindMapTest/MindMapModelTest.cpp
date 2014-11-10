#include <gtest/gtest.h>
#include <fstream>
#include "MindMapModel.h"
#include <windows.h>

namespace MindMapTest
{
    class MindMapModelTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                char szDirName[] = "testData";
                CreateDirectory(szDirName, NULL);
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
                delete _nodeNetwork;
                delete _nodeIPV4;
                delete _nodeIPV6;
                delete _nodeOS;
                delete _nodeMicrosoft;
                delete _nodeWin7;
                delete _nodeWin8;
                delete _nodeOSX;
            }

            virtual void TearDown()
            {
                delete _model;
                char szDirName[] = "testData";
                remove("testData\\test_file1.mm");
                RemoveDirectory(szDirName);
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
        _model->setDescription("Network");
        _model->selectComponent(1);
        ASSERT_STREQ("Network", _model->getSelectComponent()->getDescription().c_str());
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
}