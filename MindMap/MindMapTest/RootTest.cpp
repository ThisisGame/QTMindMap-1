#include <gtest/gtest.h>
#include "Root.h"

namespace MindMapTest
{
    class RootTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                ASSERT_EQ(0, _root->getId());
            }
            virtual void TearDown()
            {
                delete _root;
            }
            Root* _root;
    };

    TEST_F(RootTest, testConstruction)
    {
        Root* root = new Root(0, "Computer");
        ASSERT_STREQ("Computer", root->getDescription().c_str());
        delete root;
    }

    TEST_F(RootTest, testAddParent)
    {
        ASSERT_THROW(_root->addParent(NULL), char*);
    }

    TEST_F(RootTest, testAddSibling)
    {
        ASSERT_THROW(_root->addSibling(NULL), char*);
    }

    TEST_F(RootTest, testSetParent)
    {
        _root->setParent(NULL);
        ASSERT_EQ(NULL, _root->getParent());
    }

    TEST_F(RootTest, testIsParent)
    {
        ASSERT_FALSE(_root->isParent(NULL));
    }

    TEST_F(RootTest, testGetParent)
    {
        ASSERT_EQ(NULL, _root->getParent());
    }

    TEST_F(RootTest, testSetSelected)
    {
        _root->setSelected(true);
        ASSERT_TRUE(_root->getSelected());
        _root->setSelected(false);
        ASSERT_FALSE(_root->getSelected());
    }
}