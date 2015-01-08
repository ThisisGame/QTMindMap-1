#include <gtest/gtest.h>
#include "MindMapModel.h"
#include "InsertSiblingCommand.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class InsertSiblingCommandTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _node = new Node(1);
                _sibling = new Node(2);
                _model = new MindMapModel();
                _model->doInsertNode(_root);
                _model->doInsertNode(_node);
                _root->addChild(_node);
                _command = new InsertSiblingCommand(_node, _sibling, _model);
                _commandRoot = new InsertSiblingCommand(_root, NULL, _model);
            }
            virtual void TearDown()
            {
                delete _command;
                delete _model;
                delete _commandRoot;
            }
            Root* _root;
            Node* _node;
            Node* _sibling;
            MindMapModel* _model;
            InsertSiblingCommand* _command;
            InsertSiblingCommand* _commandRoot;
    };

    TEST_F(InsertSiblingCommandTest, testExecute)
    {
        ASSERT_THROW(_commandRoot->execute(), char*);
        ASSERT_EQ(1, _root->getNodeList().size());
        ASSERT_EQ(2, _model->getNodeList().size());
        _command->execute();
        ASSERT_EQ(_root, _sibling->getParent());
        ASSERT_EQ(2, _root->getNodeList().size());
        ASSERT_EQ(3, _model->getNodeList().size());
        _root->clearNodeList();
        _root->addChild(_node);
        _model->doUninsertNode(_sibling);
    }

    TEST_F(InsertSiblingCommandTest, testUnexcute)
    {
        ASSERT_EQ(2, _model->getNodeList().size());
        _command->execute();
        _command->unexcute();
        ASSERT_EQ(2, _model->getNodeList().size());
        ASSERT_EQ(_root, _node->getParent());
    }
}