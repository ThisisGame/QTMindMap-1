#include <gtest/gtest.h>
#include "MindMapModel.h"
#include "ClearDecoratorCommand.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"
#include "TriangleDecorator.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class ClearDecoratorCommandTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _node = new Node(1);
                _circleDecorator = new CircleDecorator(2);
                _rectangleDecorator = new RectangleDecorator(3);
                _triangleDecorator = new TriangleDecorator(4);
                _model = new MindMapModel();
                _model->doInsertNode(_root);
                _model->doInsertNode(_node);
                _model->doInsertNode(_circleDecorator);
                _model->doInsertNode(_rectangleDecorator);
                _model->doInsertNode(_triangleDecorator);
                _root->addChild(_node);
                _root->addDecorator(_circleDecorator);
                _node->addDecorator(_rectangleDecorator);
                _rectangleDecorator->addDecorator(_triangleDecorator);
                _command = new ClearDecoratorCommand(_node, _model);
                _commandRoot = new ClearDecoratorCommand(_root, _model);
            }
            virtual void TearDown()
            {
                delete _command;
                delete _commandRoot;
                delete _model;
            }
            Root* _root;
            Node* _node;
            MindMapModel* _model;
            ClearDecoratorCommand* _command;
            ClearDecoratorCommand* _commandRoot;
            CircleDecorator* _circleDecorator;
            RectangleDecorator* _rectangleDecorator;
            TriangleDecorator* _triangleDecorator;

    };

    TEST_F(ClearDecoratorCommandTest, testExecute)
    {
        ASSERT_EQ(_circleDecorator, _root->getParent());
        ASSERT_EQ(_triangleDecorator, _node->getDecorator());
        ASSERT_EQ(5, _model->getNodeList().size());
        _command->execute();
        ASSERT_EQ(_root, _node->getParent());
        ASSERT_EQ(3, _model->getNodeList().size());
        _commandRoot->execute();
        ASSERT_EQ(NULL, _root->getParent());
        ASSERT_EQ(2, _model->getNodeList().size());
    }

    TEST_F(ClearDecoratorCommandTest, testUnexcute)
    {
        ASSERT_EQ(_circleDecorator, _root->getParent());
        ASSERT_EQ(_triangleDecorator, _node->getDecorator());
        ASSERT_EQ(5, _model->getNodeList().size());
        _command->execute();
        _command->unexcute();
        ASSERT_EQ(_circleDecorator, _root->getParent());
        ASSERT_EQ(_triangleDecorator, _node->getDecorator());
        ASSERT_EQ(5, _model->getNodeList().size());
        _commandRoot->execute();
        _commandRoot->unexcute();
        ASSERT_EQ(_circleDecorator, _root->getParent());
        ASSERT_EQ(_triangleDecorator, _node->getDecorator());
        ASSERT_EQ(5, _model->getNodeList().size());
    }
}