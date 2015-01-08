#include <gtest/gtest.h>
#include "MindMapModel.h"
#include "InsertParentCommand.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class InsertParentCommandTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _node = new Node(1);
                _parent = new Node(2);
                _model = new MindMapModel();
                _model->doInsertNode(_root);
                _model->doInsertNode(_node);
                _root->addChild(_node);
                _command = new InsertParentCommand(_node, _parent, _model);
                _commandRoot = new InsertParentCommand(_root, NULL, _model);
            }
            virtual void TearDown()
            {
                delete _command;
                delete _model;
            }
            Root* _root;
            Node* _node;
            Node* _parent;
            MindMapModel* _model;
            InsertParentCommand* _command;
            InsertParentCommand* _commandRoot;
    };

    TEST_F(InsertParentCommandTest, testExecute)
    {
        ASSERT_THROW(_commandRoot->execute(), char*);
        ASSERT_EQ(2, _model->getNodeList().size());
        _command->execute();
        ASSERT_EQ(_root, _parent->getParent());
        ASSERT_EQ(_parent, _node->getParent());
        ASSERT_EQ(1, _root->getNodeList().size());
        ASSERT_EQ(1, _parent->getNodeList().size());
        ASSERT_EQ(0, _node->getNodeList().size());
        ASSERT_EQ(0, _node->getNodeList().size());
        ASSERT_EQ(3, _model->getNodeList().size());
        _root->clearNodeList();
        _root->addChild(_node);
        _model->doUninsertNode(_parent);
    }

    TEST_F(InsertParentCommandTest, testUnexcute)
    {
        ASSERT_EQ(2, _model->getNodeList().size());
        _command->execute();
        _command->unexcute();
        ASSERT_EQ(2, _model->getNodeList().size());
        ASSERT_EQ(_root, _node->getParent());
    }
}