#include <gtest/gtest.h>
#include <list>
#include "MockMindMapScene.h"
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
                _root = new Root(0, "Root");
                _node = new Node(1, "Node");
                _newNode = new Node(5, "NewNode");
                _triangleDecorator = new TriangleDecorator(2);
                _rectangleDecorator = new RectangleDecorator(3);
                _circleDecorator = new CircleDecorator(4);
            }
            virtual void TearDown()
            {
                delete _root;
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

    TEST_F(DecoratorTest, testChangeNodeByNode)
    {
        _root->addChild(_triangleDecorator);
        _triangleDecorator->changeNodeByNode(_node, _circleDecorator);
        for (auto item : _root->getNodeList())
        {
            ASSERT_EQ(_circleDecorator, item);
        }
    }

    TEST_F(DecoratorTest, testAddDecorator)
    {
        _root->addChild(_triangleDecorator);
        for (auto item : _root->getNodeList())
        {
            ASSERT_EQ(_triangleDecorator, item);
        }
        _triangleDecorator->addDecorator(_circleDecorator);
        for (auto item : _root->getNodeList())
        {
            ASSERT_EQ(_circleDecorator, item);
        }
        for (auto item : _circleDecorator->getNodeList())
        {
            ASSERT_EQ(_triangleDecorator, item);
        }
    }

    TEST_F(DecoratorTest, testAddChild)
    {
        _triangleDecorator->addChild(NULL);
        for (auto item : _triangleDecorator->getNodeList())
        {
            ASSERT_EQ(NULL, item);
        }
        _triangleDecorator->addChild(_circleDecorator);
        for (auto item : _triangleDecorator->getNodeList())
        {
            ASSERT_EQ(_circleDecorator, item);
        }
    }

    TEST_F(DecoratorTest, testAddParent)
    {
        _root->addChild(_triangleDecorator);
        _triangleDecorator->addParent(_node);
        for (auto item : _root->getNodeList())
        {
            ASSERT_EQ(_node, item);
        }
        for (auto item : _node->getNodeList())
        {
            ASSERT_EQ(_triangleDecorator, item);
        }
    }

    TEST_F(DecoratorTest, testAddSibling)
    {
        _root->addChild(_triangleDecorator);
        ASSERT_EQ(1, _root->getNodeList().size());
        _triangleDecorator->addSibling(_node);
        ASSERT_EQ(2, _root->getNodeList().size());
    }

    TEST_F(DecoratorTest, testClearNodeList)
    {
        _root->addChild(_node);
        _node->addChild(_newNode);
        _node->addDecorator(_triangleDecorator);
        ASSERT_EQ(1, _node->getNodeList().size());
        _triangleDecorator->clearNodeList();
        ASSERT_EQ(0, _node->getNodeList().size());
    }

    TEST_F(DecoratorTest, testDeleteNodeByNode)
    {
        _root->addChild(_node);
        _node->addChild(_newNode);
        _node->addDecorator(_triangleDecorator);
        ASSERT_EQ(1, _root->getNodeList().size());
        _triangleDecorator->deleteNodeByNode(_triangleDecorator);
        ASSERT_EQ(0, _root->getNodeList().size());
    }

    TEST_F(DecoratorTest, testDisplay)
    {
        _node->addDecorator(_triangleDecorator);
        stringstream output;
        _triangleDecorator->display(output, "", true);
        ASSERT_STREQ("+-Node(Node, ID: 1)\n", output.str().c_str());
    }

    TEST_F(DecoratorTest, testSetAndGetParent)
    {
        _triangleDecorator->setParent(_root);
        ASSERT_EQ(_root, _triangleDecorator->getParent());
    }

    TEST_F(DecoratorTest, testIsParent)
    {
        _triangleDecorator->setParent(_root);
        ASSERT_FALSE(_triangleDecorator->isParent(_root));
    }

    TEST_F(DecoratorTest, testAddChilds)
    {
        list<Component*> childs;
        _root->addDecorator(_triangleDecorator);
        ASSERT_EQ(0, _root->getNodeList().size());
        childs.push_back(_node);
        childs.push_back(_newNode);
        _triangleDecorator->addChilds(childs);
        ASSERT_EQ(2, _root->getNodeList().size());
    }

    TEST_F(DecoratorTest, testCalculatePos)
    {
        MockMindMapScene scene;
        int position = 0;
        _root->addDecorator(_triangleDecorator);
        _triangleDecorator->calculatePos(position, 0, &scene, "None");
        ASSERT_EQ(0, _root->getPoint()[0]);
        ASSERT_EQ(-62, _root->getPoint()[1]);
        ASSERT_STREQ("None", _root->getSide().c_str());
        position = 20;
        _node->addDecorator(_rectangleDecorator);
        _rectangleDecorator->calculatePos(position, 20, &scene, "Left");
        ASSERT_EQ(-25, _node->getPoint()[0]);
        ASSERT_EQ(25, _node->getPoint()[1]);
        ASSERT_STREQ("Left", _node->getSide().c_str());
        ASSERT_STREQ("Left", _rectangleDecorator->getSide().c_str());
    }

    TEST_F(DecoratorTest, testSetChildrenYPoint)
    {
        _node->addDecorator(_rectangleDecorator);
        _rectangleDecorator->setChildrenYPoint(50);
        ASSERT_EQ(50, _rectangleDecorator->getPoint()[1]);
        ASSERT_EQ(50, _node->getPoint()[1]);
    }

    TEST_F(DecoratorTest, testSetChildrenXPoint)
    {
        _node->addDecorator(_rectangleDecorator);
        _rectangleDecorator->setChildrenXPoint(30, false);
        ASSERT_EQ(30, _rectangleDecorator->getPoint()[0]);
        ASSERT_EQ(30, _node->getPoint()[0]);
        _rectangleDecorator->setChildrenXPoint(42, true);
        ASSERT_EQ(30, _rectangleDecorator->getPoint()[0]);
        ASSERT_EQ(30, _node->getPoint()[0]);
    }

    TEST_F(DecoratorTest, testGetDecorator)
    {
        _node->addDecorator(_rectangleDecorator);
        ASSERT_EQ(_rectangleDecorator, _rectangleDecorator->getDecorator());
        _rectangleDecorator->addDecorator(_circleDecorator);
        ASSERT_EQ(_circleDecorator, _rectangleDecorator->getDecorator());
    }


    TEST_F(DecoratorTest, testIsDecorator)
    {
        ASSERT_TRUE(_rectangleDecorator->isDecorator());
    }

    TEST_F(DecoratorTest, testUp)
    {
        _triangleDecorator->up(_root);
    }

    TEST_F(DecoratorTest, testDown)
    {
        _triangleDecorator->down(_root);
    }

    TEST_F(DecoratorTest, testIsUpComonent)
    {
        ASSERT_FALSE(_triangleDecorator->isUpComonent(_root));
        ASSERT_FALSE(_triangleDecorator->isUpComonent(_node));
        ASSERT_FALSE(_triangleDecorator->isUpComonent(_circleDecorator));
    }

    TEST_F(DecoratorTest, testIsUnderComonent)
    {
        ASSERT_FALSE(_triangleDecorator->isUnderComonent(_root));
        ASSERT_FALSE(_triangleDecorator->isUnderComonent(_node));
        ASSERT_FALSE(_triangleDecorator->isUnderComonent(_circleDecorator));
    }
}