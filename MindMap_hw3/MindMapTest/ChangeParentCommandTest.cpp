#include <gtest/gtest.h>
#include "ChangeParentCommand.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class ChangeParentCommandTest : public testing::Test
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
                _rootComputer->addChild(_nodeNetwork);
                _rootComputer->addChild(_nodeOS);
                _nodeNetwork->addChild(_nodeIPV4);
                _nodeNetwork->addChild(_nodeIPV6);
                _nodeOS->addChild(_nodeMicrosoft);
            }
            virtual void TearDown()
            {
                delete _rootComputer;
                delete _nodeNetwork;
                delete _nodeIPV4;
                delete _nodeIPV6;
                delete _nodeOS;
                delete _nodeMicrosoft;
            }
            Root* _rootComputer;
            Node* _nodeNetwork;
            Node* _nodeIPV4;
            Node* _nodeIPV6;
            Node* _nodeOS;
            Node* _nodeMicrosoft;
    };

    TEST_F(ChangeParentCommandTest, testExecute)
    {
        ChangeParentCommand command(_nodeNetwork, _nodeOS);
        ASSERT_EQ(1, _nodeOS->getNodeList().size());
        ASSERT_EQ(_rootComputer, _nodeNetwork->getParent());
        command.execute();
        ASSERT_EQ(2, _nodeOS->getNodeList().size());
        ASSERT_EQ(_nodeOS, _nodeNetwork->getParent());
    }

    TEST_F(ChangeParentCommandTest, testExecuteIsParent)
    {
        ChangeParentCommand command(_nodeNetwork, _nodeIPV4);
        ASSERT_EQ(2, _rootComputer->getNodeList().size());
        ASSERT_EQ(_rootComputer, _nodeNetwork->getParent());
        command.execute();
        ASSERT_EQ(3, _rootComputer->getNodeList().size());
        ASSERT_EQ(_nodeIPV4, _nodeNetwork->getParent());
        ASSERT_EQ(_rootComputer, _nodeIPV6->getParent());
        ASSERT_EQ(_rootComputer, _nodeIPV4->getParent());
    }

    TEST_F(ChangeParentCommandTest, testExecuteException)
    {
        ChangeParentCommand commandSelectItself(_nodeNetwork, _nodeNetwork);
        ChangeParentCommand commandSelectError(_nodeNetwork, NULL);
        ASSERT_THROW(commandSelectItself.execute(), char*);
        ASSERT_THROW(commandSelectError.execute(), char*);
    }

    TEST_F(ChangeParentCommandTest, testUnexcute)
    {
        ChangeParentCommand command(_nodeNetwork, _nodeOS);
        ChangeParentCommand commandIsParent(_nodeNetwork, _nodeIPV4);
        ASSERT_EQ(1, _nodeOS->getNodeList().size());
        ASSERT_EQ(2, _rootComputer->getNodeList().size());
        ASSERT_EQ(_rootComputer, _nodeNetwork->getParent());
        command.execute();
        command.unexcute();
        ASSERT_EQ(1, _nodeOS->getNodeList().size());
        ASSERT_EQ(2, _rootComputer->getNodeList().size());
        ASSERT_EQ(_rootComputer, _nodeNetwork->getParent());
        commandIsParent.execute();
        commandIsParent.unexcute();
        ASSERT_EQ(1, _nodeOS->getNodeList().size());
        ASSERT_EQ(2, _rootComputer->getNodeList().size());
        ASSERT_EQ(_rootComputer, _nodeNetwork->getParent());
    }
}