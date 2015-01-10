#include <gtest/gtest.h>
#include "SaveComponentVisitor.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"
#include "TriangleDecorator.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class SaveComponentVisitorTest : public testing::Test
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
            int getIdListAmount()
            {
                return _visitor.getIdList().size();
            }
            Root* _root;
            Node* _node;
            CircleDecorator* _circleDecorator;
            RectangleDecorator* _rectangleDecorator;
            TriangleDecorator* _triangleDecorator;
            SaveComponentVisitor _visitor;

    };

    TEST_F(SaveComponentVisitorTest, testVisitorNode)
    {
        _visitor.visitor(_node);
        ASSERT_EQ(1, getIdListAmount());
    }

    TEST_F(SaveComponentVisitorTest, testVisitorRoot)
    {
        _visitor.visitor(_root);
        ASSERT_EQ(4, getIdListAmount());
    }

    TEST_F(SaveComponentVisitorTest, testVisitorTriangleDecorator)
    {
        _visitor.visitor(_triangleDecorator);
        ASSERT_EQ(3, getIdListAmount());
    }

    TEST_F(SaveComponentVisitorTest, testVisitorCircleDecorator)
    {
        _visitor.visitor(_circleDecorator);
        ASSERT_EQ(5, getIdListAmount());
    }

    TEST_F(SaveComponentVisitorTest, testVisitorRectangleDecorator)
    {
        _visitor.visitor(_rectangleDecorator);
        ASSERT_EQ(2, getIdListAmount());
    }
}