#include <gtest/gtest.h>
#include "Node.h"
#include "Root.h"

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
                delete _node;
                delete _newNode;
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
}