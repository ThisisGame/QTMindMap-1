#include <gtest/gtest.h>
#include "AllExpendAndCollapseComponentVisitor.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"
#include "TriangleDecorator.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class AllExpendAndCollapseComponentVisitorTest : public testing::Test
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
            void visitChildren(Component* component)
            {
                _visitor.visitChildren(component);
            }
            Root* _root;
            Node* _node;
            CircleDecorator* _circleDecorator;
            RectangleDecorator* _rectangleDecorator;
            TriangleDecorator* _triangleDecorator;
            AllExpendAndCollapseComponentVisitor _visitor;

    };

    TEST_F(AllExpendAndCollapseComponentVisitorTest, testVisitorNode)
    {
        _visitor.visitor(_node);
        ASSERT_FALSE(_visitor.isExpend());
        _visitor.visitor(_node);
        ASSERT_FALSE(_visitor.isExpend());
        ASSERT_FALSE(_node->isExpend());
        ASSERT_TRUE(_root->isExpend());
    }

    TEST_F(AllExpendAndCollapseComponentVisitorTest, testVisitorRoot)
    {
        _visitor.visitor(_root);
        ASSERT_FALSE(_visitor.isExpend());
        ASSERT_FALSE(_node->isExpend());
        ASSERT_FALSE(_root->isExpend());
    }

    TEST_F(AllExpendAndCollapseComponentVisitorTest, testVisitorTriangleDecorator)
    {
        _visitor.visitor(_triangleDecorator);
        ASSERT_FALSE(_visitor.isExpend());
        ASSERT_FALSE(_node->isExpend());
        ASSERT_TRUE(_root->isExpend());
    }

    TEST_F(AllExpendAndCollapseComponentVisitorTest, testVisitorCircleDecorator)
    {
        _visitor.visitor(_circleDecorator);
        ASSERT_FALSE(_visitor.isExpend());
        ASSERT_FALSE(_node->isExpend());
        ASSERT_FALSE(_root->isExpend());
    }

    TEST_F(AllExpendAndCollapseComponentVisitorTest, testVisitorRectangleDecorator)
    {
        _visitor.visitor(_rectangleDecorator);
        ASSERT_FALSE(_visitor.isExpend());
        ASSERT_FALSE(_node->isExpend());
        ASSERT_TRUE(_root->isExpend());
    }

    TEST_F(AllExpendAndCollapseComponentVisitorTest, testVisitChildren)
    {
        visitChildren(_circleDecorator);
        ASSERT_FALSE(_node->isExpend());
        ASSERT_FALSE(_root->isExpend());
    }
}