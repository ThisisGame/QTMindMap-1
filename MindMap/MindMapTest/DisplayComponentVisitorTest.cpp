#include <gtest/gtest.h>
#include "DisplayComponentVisitor.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"
#include "TriangleDecorator.h"
#include "Root.h"
#include "Node.h"
#include "MockMindMapScene.h"

namespace MindMapTest
{
    class DisplayComponentVisitorTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _nodeTest1 = new Node(1);
                _nodeTest5 = new Node(5);
                _nodeTest6 = new Node(6);
                _nodeTest7 = new Node(7);
                _circleDecorator = new CircleDecorator(2);
                _rectangleDecorator = new RectangleDecorator(3);
                _triangleDecorator = new TriangleDecorator(4);
                _root->addChild(_nodeTest5);
                _root->addChild(_nodeTest1);
                _nodeTest1->addChild(_nodeTest6);
                _nodeTest1->addChild(_nodeTest7);
                _root->addDecorator(_circleDecorator);
                _nodeTest1->addDecorator(_rectangleDecorator);
                _rectangleDecorator->addDecorator(_triangleDecorator);
                _scene = new MockMindMapScene();
                _visitor = new DisplayComponentVisitor(_scene);
            }
            virtual void TearDown()
            {
                delete _scene;
                delete _visitor;
                delete _circleDecorator;
            }
            Root* _root;
            Node* _nodeTest1;
            Node* _nodeTest5;
            Node* _nodeTest6;
            Node* _nodeTest7;
            CircleDecorator* _circleDecorator;
            RectangleDecorator* _rectangleDecorator;
            TriangleDecorator* _triangleDecorator;
            DisplayComponentVisitor* _visitor;
            MockMindMapScene* _scene;

    };

    TEST_F(DisplayComponentVisitorTest, testVisitorNode)
    {
        ASSERT_TRUE(_nodeTest1->isExpend());
        _visitor->visitor(_nodeTest1);
        _nodeTest1->setExpend(false);
        ASSERT_FALSE(_nodeTest1->isExpend());
        _visitor->visitor(_nodeTest1);
    }

    TEST_F(DisplayComponentVisitorTest, testVisitorRoot)
    {
        ASSERT_TRUE(_root->isExpend());
        _visitor->visitor(_root);
        _root->setExpend(false);
        ASSERT_FALSE(_root->isExpend());
        _visitor->visitor(_root);
    }

    TEST_F(DisplayComponentVisitorTest, testVisitorTriangleDecorator)
    {
        ASSERT_TRUE(_nodeTest1->isExpend());
        _visitor->visitor(_triangleDecorator);
    }

    TEST_F(DisplayComponentVisitorTest, testVisitorCircleDecorator)
    {
        ASSERT_TRUE(_nodeTest1->isExpend());
        _visitor->visitor(_circleDecorator);
    }

    TEST_F(DisplayComponentVisitorTest, testVisitorRectangleDecorator)
    {
        ASSERT_TRUE(_nodeTest1->isExpend());
        _visitor->visitor(_rectangleDecorator);
    }

    TEST_F(DisplayComponentVisitorTest, testCalculatePos)
    {
        int position = 0;
        _circleDecorator->calculatePos(position, 0, _scene, "None");
        _root->setSelected(true);
        _visitor->visitor(_circleDecorator);
    }
}