#include <gtest/gtest.h>
#include "CutNodeCommand.h"
#include "MindMapModel.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class CutNodeCommandTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _rootComputer = new Root(0, "Computer");
                _nodeNetwork = new Node(1, "Network");
                _nodeIPV4 = new Node(2, "IPV4");
                _nodeIPV6 = new Node(3, "IPV6");
                _nodeOS = new Node(4, "OS");
                _nodeMicrosoft = new Node(5, "Microsoft");
                _model = new MindMapModel();
                _rootComputer->addChild(_nodeNetwork);
                _rootComputer->addChild(_nodeOS);
                _nodeNetwork->addChild(_nodeIPV4);
                _nodeNetwork->addChild(_nodeIPV6);
                _nodeOS->addChild(_nodeMicrosoft);
                _model->doInsertNode(_rootComputer);
                _model->doInsertNode(_nodeNetwork);
                _model->doInsertNode(_nodeIPV4);
                _model->doInsertNode(_nodeIPV6);
                _model->doInsertNode(_nodeOS);
                _model->doInsertNode(_nodeMicrosoft);
            }
            virtual void TearDown()
            {
                delete _model;
            }
            Root* _rootComputer;
            Node* _nodeNetwork;
            Node* _nodeIPV4;
            Node* _nodeIPV6;
            Node* _nodeOS;
            Node* _nodeMicrosoft;
            MindMapModel* _model;
    };

    TEST_F(CutNodeCommandTest, testExecute)
    {
        CutNodeCommand command(_nodeNetwork, _model);
        ASSERT_EQ(2, _rootComputer->getNodeList().size());
        ASSERT_EQ(6, _model->getNodeList().size());
        command.execute();
        ASSERT_EQ(1, _rootComputer->getNodeList().size());
        ASSERT_EQ(3, _model->getNodeList().size());
        delete _nodeNetwork;
    }

    TEST_F(CutNodeCommandTest, testUnexecute)
    {
        CutNodeCommand command(_nodeNetwork, _model);
        ASSERT_EQ(2, _rootComputer->getNodeList().size());
        ASSERT_EQ(6, _model->getNodeList().size());
        command.execute();
        command.unexcute();
        ASSERT_EQ(2, _rootComputer->getNodeList().size());
        ASSERT_EQ(6, _model->getNodeList().size());
    }
}