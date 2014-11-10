#include <gtest/gtest.h>
#include "MindMapModel.h"
#include "InsertChildCommand.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class InsertChildCommandTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _component = new Root(0);
                _child = new Node(1);
                _model = new MindMapModel();
                _model->doInsertNode(_component);
                _command = new InsertChildCommand(_component, _child, _model);
            }
            virtual void TearDown()
            {
                delete _command;
                delete _model;
            }
            Root* _component;
            Node* _child;
            MindMapModel* _model;
            InsertChildCommand* _command;
    };

    TEST_F(InsertChildCommandTest, testExecute)
    {
        ASSERT_EQ(1, _model->getNodeList().size());
        _command->execute();
        ASSERT_EQ(2, _model->getNodeList().size());
        ASSERT_EQ(1, _component->getNodeList().size());
        ASSERT_EQ(_component, _child->getParent());
        _model->doUninsertNode(_child);
    }

    TEST_F(InsertChildCommandTest, testUnexcute)
    {
        ASSERT_EQ(1, _model->getNodeList().size());
        _command->execute();
        _command->unexcute();
        ASSERT_EQ(1, _model->getNodeList().size());
        ASSERT_EQ(0, _component->getNodeList().size());
    }
}