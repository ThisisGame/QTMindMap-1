#include <gtest/gtest.h>
#include <list>
#include "Decorator.h"
#include "TriangleDecorator.h"
#include "RectangleDecorator.h"
#include "CircleDecorator.h"
#include "Node.h"
#include "Root.h"
using namespace std;

namespace MindMapTest
{
    class DecoratorTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _node = new Node(1);
                _newNode = new Node(5);
                _triangleDecorator = new TriangleDecorator(2);
                _rectangleDecorator = new RectangleDecorator(3);
                _circleDecorator = new CircleDecorator(4);
            }
            virtual void TearDown()
            {
            }
            void init()
            {
            }
            Root* _root;
            Node* _node;
            Node* _newNode;
            TriangleDecorator* _triangleDecorator;
            RectangleDecorator* _rectangleDecorator;
            CircleDecorator* _circleDecorator;
    };

    TEST_F(DecoratorTest, testAddChild)
    {
    }
}