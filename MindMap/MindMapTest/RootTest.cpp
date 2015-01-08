#include <gtest/gtest.h>
#include "MockMindMapScene.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class RootTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _rootComputer = new Root(0, "Computer");
                _nodeNetwork = new Node(1, "Network");
                _nodeIPV4 = new Node(2, "IPV4");
                _nodeIPV6 = new Node(3, "IPV6");
                _nodeOS = new Node(4, "OS");
                _nodeMicrosoft = new Node(5, "Microsoft");
                _nodeOSX = new Node(6, "OSX");
                ASSERT_EQ(0, _rootComputer->getId());
            }
            virtual void TearDown()
            {
                delete _rootComputer;
            }
            Root* _rootComputer;
            Node* _nodeNetwork;
            Node* _nodeIPV4;
            Node* _nodeIPV6;
            Node* _nodeOS;
            Node* _nodeMicrosoft;
            Node* _nodeOSX;
    };

    TEST_F(RootTest, testConstruction)
    {
        Root* root = new Root(0, "Computer");
        ASSERT_STREQ("Computer", root->getDescription().c_str());
        delete root;
    }

    TEST_F(RootTest, testAddParent)
    {
        ASSERT_THROW(_rootComputer->addParent(NULL), char*);
    }

    TEST_F(RootTest, testAddSibling)
    {
        ASSERT_THROW(_rootComputer->addSibling(NULL), char*);
    }

    TEST_F(RootTest, testSetParent)
    {
        _rootComputer->setParent(NULL);
        ASSERT_EQ(NULL, _rootComputer->getParent());
    }

    TEST_F(RootTest, testIsParent)
    {
        ASSERT_FALSE(_rootComputer->isParent(NULL));
    }

    TEST_F(RootTest, testGetParent)
    {
        ASSERT_EQ(NULL, _rootComputer->getParent());
    }

    TEST_F(RootTest, testSetSelected)
    {
        _rootComputer->setSelected(true);
        ASSERT_TRUE(_rootComputer->getSelected());
        _rootComputer->setSelected(false);
        ASSERT_FALSE(_rootComputer->getSelected());
    }

    TEST_F(RootTest, testClone)
    {
        ASSERT_EQ(NULL, _rootComputer->clone());
    }

    TEST_F(RootTest, testCalculatePos)
    {
        _rootComputer->addChild(_nodeNetwork);
        _rootComputer->addChild(_nodeIPV4);
        _rootComputer->addChild(_nodeIPV6);
        int position = 0;
        MockMindMapScene scene;
        _rootComputer->calculatePos(position, 0, &scene, "None");
        ASSERT_EQ(0, _rootComputer->getPoint()[0]);
        ASSERT_EQ(62, _rootComputer->getPoint()[1]);
        ASSERT_STREQ("None", _rootComputer->getSide().c_str());
        ASSERT_EQ(75, _nodeNetwork->getPoint()[0]);
        ASSERT_EQ(0, _nodeNetwork->getPoint()[1]);
        ASSERT_STREQ("Right", _nodeNetwork->getSide().c_str());
        ASSERT_EQ(-75, _nodeIPV4->getPoint()[0]);
        ASSERT_EQ(62, _nodeIPV4->getPoint()[1]);
        ASSERT_STREQ("Left", _nodeIPV4->getSide().c_str());
        ASSERT_EQ(75, _nodeIPV6->getPoint()[0]);
        ASSERT_EQ(125, _nodeIPV6->getPoint()[1]);
        ASSERT_STREQ("Right", _nodeIPV6->getSide().c_str());
        _nodeIPV4->addChild(_nodeOS);
        _nodeIPV4->addChild(_nodeMicrosoft);
        _nodeIPV4->addChild(_nodeOSX);
        position = 0;
        _rootComputer->calculatePos(position, 0, &scene, "None");
        ASSERT_EQ(0, _rootComputer->getPoint()[0]);
        ASSERT_EQ(125, _rootComputer->getPoint()[1]);
        ASSERT_STREQ("None", _rootComputer->getSide().c_str());
        //RIGHT
        ASSERT_EQ(75, _nodeNetwork->getPoint()[0]);
        ASSERT_EQ(63, _nodeNetwork->getPoint()[1]);
        ASSERT_STREQ("Right", _nodeNetwork->getSide().c_str());
        ASSERT_EQ(75, _nodeIPV6->getPoint()[0]);
        ASSERT_EQ(188, _nodeIPV6->getPoint()[1]);
        ASSERT_STREQ("Right", _nodeIPV6->getSide().c_str());
        //LEFT
        ASSERT_EQ(-75, _nodeIPV4->getPoint()[0]);
        ASSERT_EQ(125, _nodeIPV4->getPoint()[1]);
        ASSERT_STREQ("Left", _nodeIPV4->getSide().c_str());
        ASSERT_EQ(-150, _nodeOS->getPoint()[0]);
        ASSERT_EQ(0, _nodeOS->getPoint()[1]);
        ASSERT_STREQ("Left", _nodeOS->getSide().c_str());
        ASSERT_EQ(-150, _nodeMicrosoft->getPoint()[0]);
        ASSERT_EQ(125, _nodeMicrosoft->getPoint()[1]);
        ASSERT_STREQ("Left", _nodeMicrosoft->getSide().c_str());
        ASSERT_EQ(-150, _nodeOSX->getPoint()[0]);
        ASSERT_EQ(250, _nodeOSX->getPoint()[1]);
        ASSERT_STREQ("Left", _nodeOSX->getSide().c_str());
    }

    TEST_F(RootTest, testSetChildrenXPoint)
    {
        ASSERT_EQ(0, _rootComputer->getPoint()[0]);
        ASSERT_EQ(0, _nodeNetwork->getPoint()[0]);
        ASSERT_EQ(0, _nodeIPV4->getPoint()[0]);
        ASSERT_EQ(0, _nodeIPV6->getPoint()[0]);
        _rootComputer->addChild(_nodeNetwork);
        _rootComputer->addChild(_nodeIPV4);
        _rootComputer->addChild(_nodeIPV6);
        _rootComputer->setChildrenXPoint(5, false);
        ASSERT_EQ(5, _rootComputer->getPoint()[0]);
        ASSERT_EQ(5, _nodeNetwork->getPoint()[0]);
        ASSERT_EQ(-5, _nodeIPV4->getPoint()[0]);
        ASSERT_EQ(5, _nodeIPV6->getPoint()[0]);
        _rootComputer->setChildrenXPoint(8, true);
        ASSERT_EQ(5, _rootComputer->getPoint()[0]);
        ASSERT_EQ(13, _nodeNetwork->getPoint()[0]);
        ASSERT_EQ(-13, _nodeIPV4->getPoint()[0]);
        ASSERT_EQ(13, _nodeIPV6->getPoint()[0]);
    }

    TEST_F(RootTest, testUp)
    {
        _rootComputer->addChild(_nodeNetwork);
        _rootComputer->addChild(_nodeIPV4);
        _rootComputer->addChild(_nodeIPV6);
        ASSERT_EQ(3, (*--_rootComputer->getNodeList().end())->getId());
        _rootComputer->up(_nodeMicrosoft);
        ASSERT_EQ(3, (*--_rootComputer->getNodeList().end())->getId());
        _rootComputer->up(_nodeNetwork);
        ASSERT_EQ(3, (*--_rootComputer->getNodeList().end())->getId());
        _rootComputer->up(_nodeIPV6);
        ASSERT_EQ(2, (*--_rootComputer->getNodeList().end())->getId());
    }

    TEST_F(RootTest, testDown)
    {
        _rootComputer->addChild(_nodeNetwork);
        _rootComputer->addChild(_nodeIPV4);
        _rootComputer->addChild(_nodeIPV6);
        ASSERT_EQ(1, (*_rootComputer->getNodeList().begin())->getId());
        _rootComputer->down(_nodeMicrosoft);
        ASSERT_EQ(1, (*_rootComputer->getNodeList().begin())->getId());
        _rootComputer->down(_nodeNetwork);
        ASSERT_EQ(3, (*_rootComputer->getNodeList().begin())->getId());
        _rootComputer->down(_nodeNetwork);
        ASSERT_EQ(1, (*--_rootComputer->getNodeList().end())->getId());
    }

    TEST_F(RootTest, testIsUpComonent)
    {
        _rootComputer->addChild(_nodeNetwork);
        _rootComputer->addChild(_nodeIPV4);
        _rootComputer->addChild(_nodeIPV6);
        ASSERT_TRUE(_rootComputer->isUpComonent(_nodeNetwork));
        ASSERT_TRUE(_rootComputer->isUpComonent(_nodeIPV4));
        ASSERT_FALSE(_rootComputer->isUpComonent(_nodeIPV6));
    }

    TEST_F(RootTest, testIsUnderComonent)
    {
        _rootComputer->addChild(_nodeNetwork);
        _rootComputer->addChild(_nodeIPV4);
        _rootComputer->addChild(_nodeIPV6);
        ASSERT_FALSE(_rootComputer->isUnderComonent(_nodeNetwork));
        ASSERT_TRUE(_rootComputer->isUnderComonent(_nodeIPV4));
        ASSERT_TRUE(_rootComputer->isUnderComonent(_nodeIPV6));
    }
}