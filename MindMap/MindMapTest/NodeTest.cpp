#include <gtest/gtest.h>
#include "Node.h"
#include "Root.h"
#include "MockMindMapScene.h"

namespace MindMapTest
{
    class NodeTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _node = new Node(1);
                _newNode = new Node(2);
                _root->addChild(_node);
                ASSERT_EQ(2, _newNode->getId());
            }
            virtual void TearDown()
            {
                delete _root;
            }
            Root* _root;
            Node* _node;
            Node* _newNode;
    };

    TEST_F(NodeTest, testConstruction)
    {
        Node* root = new Node(1, "Network");
        ASSERT_STREQ("Network", root->getDescription().c_str());
        delete root;
    }

    TEST_F(NodeTest, testAddParent)
    {
        _node->addParent(_newNode);
        ASSERT_EQ(_newNode, _node->getParent());
        ASSERT_EQ(_root, _newNode->getParent());
    }

    TEST_F(NodeTest, testAddSibling)
    {
        ASSERT_EQ(1, _root->getNodeList().size());
        _node->addSibling(_newNode);
        ASSERT_EQ(2, _root->getNodeList().size());
    }

    TEST_F(NodeTest, testSetParent)
    {
        _node->setParent(_newNode);
        ASSERT_EQ(_newNode, _node->getParent());
    }

    TEST_F(NodeTest, testIsParent)
    {
        ASSERT_TRUE(_node->isParent(_root));
        ASSERT_FALSE(_node->isParent(_newNode));
        _node->addParent(_newNode);
        ASSERT_TRUE(_node->isParent(_root));
    }

    TEST_F(NodeTest, testGetParent)
    {
        ASSERT_EQ(_root, _node->getParent());
    }

    TEST_F(NodeTest, testSetSelected)
    {
        _node->setSelected(true);
        ASSERT_TRUE(_node->getSelected());
        _node->setSelected(false);
        ASSERT_FALSE(_node->getSelected());
    }

    TEST_F(NodeTest, testClone)
    {
        _node->addChild(_newNode);
        Component* cloneItem = _node->clone();
        ASSERT_NE(_node, cloneItem);
        ASSERT_STREQ(cloneItem->getDescription().c_str(), _node->getDescription().c_str());
        ASSERT_EQ(cloneItem->getId(), _node->getId());
        ASSERT_EQ(cloneItem->getNodeList().size(), _node->getNodeList().size());
    }

    TEST_F(NodeTest, testCalculatePos)
    {
        Node firstNode(0, "0");
        Node* secondNode = new Node(1, "1");
        Node* thirdNode = new Node(2, "2");
        Node* fourthNode = new Node(3, "3");
        Node* fifthNode = new Node(4, "4");
        MockMindMapScene scene;
        int position = 98;
        firstNode.calculatePos(position, 65, &scene, "Right");
        ASSERT_EQ(65, firstNode.getPoint()[0]);
        ASSERT_EQ(98, firstNode.getPoint()[1]);
        ASSERT_STREQ("Right", firstNode.getSide().c_str());
        //
        firstNode.addChild(secondNode);
        firstNode.addChild(thirdNode);
        firstNode.addChild(fourthNode);
        firstNode.addChild(fifthNode);
        position = 10;
        firstNode.calculatePos(position, 50, &scene, "Right");
        ASSERT_EQ(50, firstNode.getPoint()[0]);
        ASSERT_EQ(197, firstNode.getPoint()[1]);
        ASSERT_STREQ("Right", firstNode.getSide().c_str());
        //
        ASSERT_EQ(125, secondNode->getPoint()[0]);
        ASSERT_EQ(10, secondNode->getPoint()[1]);
        ASSERT_STREQ("Right", secondNode->getSide().c_str());
        //
        ASSERT_EQ(125, thirdNode->getPoint()[0]);
        ASSERT_EQ(135, thirdNode->getPoint()[1]);
        ASSERT_STREQ("Right", thirdNode->getSide().c_str());
        //
        ASSERT_EQ(125, fourthNode->getPoint()[0]);
        ASSERT_EQ(260, fourthNode->getPoint()[1]);
        ASSERT_STREQ("Right", fourthNode->getSide().c_str());
        //
        ASSERT_EQ(125, fifthNode->getPoint()[0]);
        ASSERT_EQ(385, fifthNode->getPoint()[1]);
        ASSERT_STREQ("Right", fifthNode->getSide().c_str());
        //
        position = 10;
        firstNode.calculatePos(position, 50, &scene, "Left");
        ASSERT_EQ(-50, firstNode.getPoint()[0]);
        ASSERT_EQ(197, firstNode.getPoint()[1]);
        ASSERT_STREQ("Left", firstNode.getSide().c_str());
        //
        ASSERT_EQ(-125, secondNode->getPoint()[0]);
        ASSERT_EQ(10, secondNode->getPoint()[1]);
        ASSERT_STREQ("Left", secondNode->getSide().c_str());
        //
        ASSERT_EQ(-125, thirdNode->getPoint()[0]);
        ASSERT_EQ(135, thirdNode->getPoint()[1]);
        ASSERT_STREQ("Left", thirdNode->getSide().c_str());
        //
        ASSERT_EQ(-125, fourthNode->getPoint()[0]);
        ASSERT_EQ(260, fourthNode->getPoint()[1]);
        ASSERT_STREQ("Left", fourthNode->getSide().c_str());
        //
        ASSERT_EQ(-125, fifthNode->getPoint()[0]);
        ASSERT_EQ(385, fifthNode->getPoint()[1]);
        ASSERT_STREQ("Left", fifthNode->getSide().c_str());
        //
        firstNode.setDescription("0123456789abcdefghijklmn");
        position = 10;
        firstNode.calculatePos(position, 50, &scene, "Right");
        ASSERT_EQ(50, firstNode.getPoint()[0]);
        ASSERT_EQ(-2, firstNode.getPoint()[1]);
        ASSERT_STREQ("Right", firstNode.getSide().c_str());
        //
        ASSERT_EQ(125, secondNode->getPoint()[0]);
        ASSERT_EQ(60, secondNode->getPoint()[1]);
        ASSERT_STREQ("Right", secondNode->getSide().c_str());
        //
        ASSERT_EQ(125, thirdNode->getPoint()[0]);
        ASSERT_EQ(185, thirdNode->getPoint()[1]);
        ASSERT_STREQ("Right", thirdNode->getSide().c_str());
        //
        ASSERT_EQ(125, fourthNode->getPoint()[0]);
        ASSERT_EQ(310, fourthNode->getPoint()[1]);
        ASSERT_STREQ("Right", fourthNode->getSide().c_str());
        //
        ASSERT_EQ(125, fifthNode->getPoint()[0]);
        ASSERT_EQ(435, fifthNode->getPoint()[1]);
        ASSERT_STREQ("Right", fifthNode->getSide().c_str());
    }

    TEST_F(NodeTest, testSetChildrenXPoint)
    {
        Node firstNode(0, "0");
        Node* secondNode = new Node(1, "1");
        Node* thirdNode = new Node(2, "2");
        Node* fourthNode = new Node(3, "3");
        Node* fifthNode = new Node(4, "4");
        firstNode.addChild(secondNode);
        firstNode.addChild(thirdNode);
        firstNode.addChild(fourthNode);
        firstNode.addChild(fifthNode);
        firstNode.setChildrenXPoint(5, false);
        ASSERT_EQ(5, firstNode.getPoint()[0]);
        ASSERT_EQ(5, secondNode->getPoint()[0]);
        ASSERT_EQ(5, thirdNode->getPoint()[0]);
        ASSERT_EQ(5, fourthNode->getPoint()[0]);
        ASSERT_EQ(5, fifthNode->getPoint()[0]);
        firstNode.setChildrenXPoint(10, true);
        ASSERT_EQ(5, firstNode.getPoint()[0]);
        ASSERT_EQ(15, secondNode->getPoint()[0]);
        ASSERT_EQ(15, thirdNode->getPoint()[0]);
        ASSERT_EQ(15, fourthNode->getPoint()[0]);
        ASSERT_EQ(15, fifthNode->getPoint()[0]);
    }

    TEST_F(NodeTest, testUp)
    {
        Node firstNode(0, "0");
        Node* secondNode = new Node(1, "1");
        Node* thirdNode = new Node(2, "2");
        Node* fourthNode = new Node(3, "3");
        Node* fifthNode = new Node(4, "4");
        firstNode.addChild(secondNode);
        firstNode.addChild(thirdNode);
        firstNode.addChild(fourthNode);
        firstNode.addChild(fifthNode);
        ASSERT_EQ(1, (*firstNode.getNodeList().begin())->getId());
        firstNode.up(secondNode);
        ASSERT_EQ(1, (*firstNode.getNodeList().begin())->getId());
        firstNode.up(thirdNode);
        ASSERT_EQ(2, (*firstNode.getNodeList().begin())->getId());
        Node notInListNode(5);
        firstNode.up(&notInListNode);
        ASSERT_EQ(2, (*firstNode.getNodeList().begin())->getId());
    }

    TEST_F(NodeTest, testDown)
    {
        Node firstNode(0, "0");
        Node* secondNode = new Node(1, "1");
        Node* thirdNode = new Node(2, "2");
        Node* fourthNode = new Node(3, "3");
        Node* fifthNode = new Node(4, "4");
        firstNode.addChild(secondNode);
        firstNode.addChild(thirdNode);
        firstNode.addChild(fourthNode);
        firstNode.addChild(fifthNode);
        ASSERT_EQ(4, (*--firstNode.getNodeList().end())->getId());
        firstNode.down(fifthNode);
        ASSERT_EQ(4, (*--firstNode.getNodeList().end())->getId());
        firstNode.down(fourthNode);
        ASSERT_EQ(3, (*--firstNode.getNodeList().end())->getId());
        Node notInListNode(5);
        firstNode.down(&notInListNode);
        ASSERT_EQ(3, (*--firstNode.getNodeList().end())->getId());
    }

    TEST_F(NodeTest, testIsUpComonent)
    {
        Node firstNode(0, "0");
        Node* secondNode = new Node(1, "1");
        Node* thirdNode = new Node(2, "2");
        Node* fourthNode = new Node(3, "3");
        Node* fifthNode = new Node(4, "4");
        Node notInListNode(5);
        firstNode.addChild(secondNode);
        firstNode.addChild(thirdNode);
        firstNode.addChild(fourthNode);
        firstNode.addChild(fifthNode);
        ASSERT_TRUE(firstNode.isUpComonent(secondNode));
        ASSERT_FALSE(firstNode.isUpComonent(fourthNode));
        ASSERT_FALSE(firstNode.isUpComonent(&notInListNode));
    }

    TEST_F(NodeTest, testIsUnderComonent)
    {
        Node firstNode(0, "0");
        Node* secondNode = new Node(1, "1");
        Node* thirdNode = new Node(2, "2");
        Node* fourthNode = new Node(3, "3");
        Node* fifthNode = new Node(4, "4");
        Node notInListNode(5);
        firstNode.addChild(secondNode);
        firstNode.addChild(thirdNode);
        firstNode.addChild(fourthNode);
        firstNode.addChild(fifthNode);
        ASSERT_TRUE(firstNode.isUnderComonent(fifthNode));
        ASSERT_FALSE(firstNode.isUnderComonent(fourthNode));
        ASSERT_FALSE(firstNode.isUnderComonent(&notInListNode));
    }

}