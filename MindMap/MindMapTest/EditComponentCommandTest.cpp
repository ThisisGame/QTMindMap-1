#include <gtest/gtest.h>
#include "MindMapModel.h"
#include "EditComponentCommand.h"
#include "Root.h"
#include "Node.h"

namespace MindMapTest
{
    class EditComponentCommandTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _root = new Root(0);
                _root->setDescription("Drawing");
                _node = new Node(1);
                _node->setDescription("IPV6");
                _commandRoot = new EditComponentCommand("Computer", _root);
                _commandNode = new EditComponentCommand("Network", _node);
            }
            virtual void TearDown()
            {
                delete _root;
                delete _node;
                delete _commandRoot;
                delete _commandNode;
            }
            Root* _root;
            Node* _node;
            EditComponentCommand* _commandRoot;
            EditComponentCommand* _commandNode;
    };

    TEST_F(EditComponentCommandTest, testExecute)
    {
        ASSERT_STREQ("Drawing", _root->getDescription().c_str());
        _commandRoot->execute();
        ASSERT_STREQ("Computer", _root->getDescription().c_str());
        ASSERT_STREQ("IPV6", _node->getDescription().c_str());
        _commandNode->execute();
        ASSERT_STREQ("Network", _node->getDescription().c_str());
    }

    TEST_F(EditComponentCommandTest, testUnexcute)
    {
        ASSERT_STREQ("Drawing", _root->getDescription().c_str());
        ASSERT_STREQ("IPV6", _node->getDescription().c_str());
        _commandRoot->execute();
        _commandRoot->unexcute();
        _commandNode->execute();
        _commandNode->unexcute();
        ASSERT_STREQ("Drawing", _root->getDescription().c_str());
        ASSERT_STREQ("IPV6", _node->getDescription().c_str());
    }
}