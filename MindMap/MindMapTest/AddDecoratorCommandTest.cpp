#include <gtest/gtest.h>
#include "MindMapModel.h"
#include "AddDecoratorCommand.h"
#include "CircleDecorator.h"
#include "RectangleDecorator.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class AddDecoratorCommandTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _node = new Node(1);
                _circleDecorator = new CircleDecorator(2);
                _rectangleDecorator = new RectangleDecorator(3);
                _model = new MindMapModel();
                _model->doInsertNode(_root);
                _model->doInsertNode(_node);
                _root->addChild(_node);
                _command = new AddDecoratorCommand(_node, _circleDecorator, _model);
                _commandRoot = new AddDecoratorCommand(_root, _rectangleDecorator, _model);
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
            AddDecoratorCommand* _command;
            AddDecoratorCommand* _commandRoot;
            CircleDecorator* _circleDecorator;
            RectangleDecorator* _rectangleDecorator;

    };

    TEST_F(AddDecoratorCommandTest, testExecute)
    {
        ASSERT_EQ(2, _model->getNodeList().size());
        _command->execute();
        ASSERT_EQ(_circleDecorator, _node->getParent());
        ASSERT_EQ(3, _model->getNodeList().size());
        _commandRoot->execute();
        ASSERT_EQ(4, _model->getNodeList().size());
        _root->clearNodeList();
        _root->addChild(_node);
        _model->doUninsertNode(_circleDecorator);
        _model->doUninsertNode(_rectangleDecorator);
    }

    TEST_F(AddDecoratorCommandTest, testUnexcute)
    {
        ASSERT_EQ(2, _model->getNodeList().size());
        _command->execute();
        _command->unexcute();
        ASSERT_EQ(2, _model->getNodeList().size());
        ASSERT_EQ(_root, _node->getParent());
        _commandRoot->execute();
        _commandRoot->unexcute();
        ASSERT_EQ(2, _model->getNodeList().size());
        ASSERT_EQ(_root, _root->getDecorator());
    }
}