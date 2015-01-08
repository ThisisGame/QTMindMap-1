#include <gtest/gtest.h>
#include "Node.h"
#include "Root.h"
#include "RectangleDecorator.h"
#include "SimpleExpendAndCollapseComponentVisitor.h"

namespace MindMapTest
{
    class RectangleDecoratorTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
            }
            virtual void TearDown()
            {
            }
    };

    TEST_F(RectangleDecoratorTest, testConstruction)
    {
        RectangleDecorator decorator(0);
        ASSERT_EQ(0, decorator.getId());
        ASSERT_EQ(NULL, decorator.getParent());
        ASSERT_EQ(1, decorator.getNodeList().size());
        ASSERT_STREQ("Rectangle", decorator.getType().c_str());
    }

    TEST_F(RectangleDecoratorTest, testClone)
    {
        RectangleDecorator decorator(0);
        Node* node = new Node(1);
        node->addDecorator(&decorator);
        Component* cloneDecorator = decorator.clone();
        ASSERT_EQ(0, cloneDecorator->getId());
        ASSERT_EQ(NULL, cloneDecorator->getParent());
        ASSERT_EQ(1, cloneDecorator->getNodeList().size());
        ASSERT_STREQ("Rectangle", cloneDecorator->getType().c_str());
    }

    TEST_F(RectangleDecoratorTest, testaAcept)
    {
        SimpleExpendAndCollapseComponentVisitor visitor;
        RectangleDecorator decorator(0);
        decorator.accept(&visitor);
    }
}