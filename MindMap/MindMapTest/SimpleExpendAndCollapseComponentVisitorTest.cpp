#include <gtest/gtest.h>
#include "SimpleExpendAndCollapseComponentVisitor.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"
#include "TriangleDecorator.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class SimpleExpendAndCollapseComponentVisitorTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _node = new Node(1);
                _circleDecorator = new CircleDecorator(2);
                _rectangleDecorator = new RectangleDecorator(3);
                _triangleDecorator = new TriangleDecorator(4);
                _root->addChild(_node);
                _root->addDecorator(_circleDecorator);
                _node->addDecorator(_rectangleDecorator);
                _rectangleDecorator->addDecorator(_triangleDecorator);
            }
            virtual void TearDown()
            {
                delete _circleDecorator;
            }
            Root* _root;
            Node* _node;
            CircleDecorator* _circleDecorator;
            RectangleDecorator* _rectangleDecorator;
            TriangleDecorator* _triangleDecorator;
            SimpleExpendAndCollapseComponentVisitor _visitor;

    };

    TEST_F(SimpleExpendAndCollapseComponentVisitorTest, testVisitorNode)
    {
        ASSERT_TRUE(_node->isExpend());
        _visitor.visitor(_node);
        ASSERT_FALSE(_node->isExpend());
        _visitor.visitor(_node);
        ASSERT_TRUE(_node->isExpend());
    }

    TEST_F(SimpleExpendAndCollapseComponentVisitorTest, testVisitorRoot)
    {
        ASSERT_TRUE(_root->isExpend());
        _visitor.visitor(_root);
        ASSERT_FALSE(_root->isExpend());
        _visitor.visitor(_root);
        ASSERT_TRUE(_root->isExpend());
    }

    TEST_F(SimpleExpendAndCollapseComponentVisitorTest, testVisitorTriangleDecorator)
    {
        ASSERT_TRUE(_node->isExpend());
        _visitor.visitor(_triangleDecorator);
        ASSERT_TRUE(_node->isExpend());
    }

    TEST_F(SimpleExpendAndCollapseComponentVisitorTest, testVisitorCircleDecorator)
    {
        ASSERT_TRUE(_root->isExpend());
        _visitor.visitor(_circleDecorator);
        ASSERT_TRUE(_root->isExpend());
    }

    TEST_F(SimpleExpendAndCollapseComponentVisitorTest, testVisitorRectangleDecorator)
    {
        ASSERT_TRUE(_node->isExpend());
        _visitor.visitor(_rectangleDecorator);
        ASSERT_TRUE(_node->isExpend());
    }
}