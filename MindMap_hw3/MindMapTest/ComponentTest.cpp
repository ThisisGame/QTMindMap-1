#include <gtest/gtest.h>
#include "Node.h"
#include "Root.h"
#include "Component.h"

namespace MindMapTest
{
    class ComponentTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _node = new Node(1);
            }
            virtual void TearDown()
            {
                delete _root;
                delete _node;
            }
            Root* _root;
            Node* _node;
    };

    TEST_F(ComponentTest, testSetDescription)
    {
        _root->setDescription("Computer");
        ASSERT_STREQ("Computer", _root->getDescription().c_str());
    }

    TEST_F(ComponentTest, testGetId)
    {
        ASSERT_EQ(0, _root->getId());
        ASSERT_EQ(1, _node->getId());
    }

    TEST_F(ComponentTest, testSetId)
    {
        _node->setId(2);
        ASSERT_EQ(2, _node->getId());
    }

    TEST_F(ComponentTest, testGetType)
    {
        ASSERT_STREQ("Root", _root->getType().c_str());
        ASSERT_STREQ("Node", _node->getType().c_str());
    }
}