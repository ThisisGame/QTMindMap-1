#include <gtest/gtest.h>
#include "Node.h"
#include "Root.h"
#include "TriangleDecorator.h"
#include "SimpleExpendAndCollapseComponentVisitor.h"

namespace MindMapTest
{
    class TriangleDecoratorTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
            }
            virtual void TearDown()
            {
            }
    };

    TEST_F(TriangleDecoratorTest, testConstruction)
    {
        TriangleDecorator decorator(0);
        ASSERT_EQ(0, decorator.getId());
        ASSERT_EQ(NULL, decorator.getParent());
        ASSERT_EQ(1, decorator.getNodeList().size());
        ASSERT_STREQ("Triangle", decorator.getType().c_str());
    }

    TEST_F(TriangleDecoratorTest, testClone)
    {
        TriangleDecorator decorator(0);
        Node* node = new Node(1);
        node->addDecorator(&decorator);
        Component* cloneDecorator = decorator.clone();
        ASSERT_EQ(0, cloneDecorator->getId());
        ASSERT_EQ(NULL, cloneDecorator->getParent());
        ASSERT_EQ(1, cloneDecorator->getNodeList().size());
        ASSERT_STREQ("Triangle", cloneDecorator->getType().c_str());
    }

    TEST_F(TriangleDecoratorTest, testaAcept)
    {
        SimpleExpendAndCollapseComponentVisitor visitor;
        TriangleDecorator decorator(0);
        decorator.accept(&visitor);
    }
}