#include <gtest/gtest.h>
#include "CommandManager.h"
#include "EditComponentCommand.h"
#include "InsertParentCommand.h"
#include "Node.h"
#include "Root.h"

namespace MindMapTest
{
    class CommandManagerTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _commandManager = new CommandManager();
                _root = new Root(0, "Computer");
                _node = new Node(1, "Network");
            }
            virtual void TearDown()
            {
                delete _root;
                delete _commandManager;
            }
            CommandManager* _commandManager;
            Root* _root;
            Node* _node;
    };

    TEST_F(CommandManagerTest, testExecute)
    {
        ASSERT_THROW(_commandManager->execute(new InsertParentCommand(_root, NULL, NULL)), char*);
        _commandManager->execute(new EditComponentCommand("IPV4", _node));
        ASSERT_STREQ("IPV4", _node->getDescription().c_str());
        _commandManager->execute(new EditComponentCommand("IPV6", _node));
        ASSERT_STREQ("IPV6", _node->getDescription().c_str());
        ASSERT_EQ(2, _commandManager->getUndoCommandStack().size());
        _commandManager->undo();
        ASSERT_EQ(1, _commandManager->getRedoCommandStack().size());
        _commandManager->execute(new EditComponentCommand("IP", _node));
        ASSERT_EQ(0, _commandManager->getRedoCommandStack().size());
        ASSERT_EQ(2, _commandManager->getUndoCommandStack().size());
    }

    TEST_F(CommandManagerTest, testRedo)
    {
        ASSERT_THROW(_commandManager->redo(), char*);
        _commandManager->execute(new EditComponentCommand("IPV4", _node));
        _commandManager->execute(new EditComponentCommand("IPV6", _node));
        _commandManager->execute(new EditComponentCommand("IP", _node));
        ASSERT_EQ(0, _commandManager->getRedoCommandStack().size());
        ASSERT_EQ(3, _commandManager->getUndoCommandStack().size());
        ASSERT_STREQ("IP", _node->getDescription().c_str());
        _commandManager->undo();
        ASSERT_EQ(1, _commandManager->getRedoCommandStack().size());
        ASSERT_EQ(2, _commandManager->getUndoCommandStack().size());
        ASSERT_STREQ("IPV6", _node->getDescription().c_str());
        _commandManager->redo();
        ASSERT_STREQ("IP", _node->getDescription().c_str());
        ASSERT_EQ(0, _commandManager->getRedoCommandStack().size());
        ASSERT_EQ(3, _commandManager->getUndoCommandStack().size());
    }

    TEST_F(CommandManagerTest, testUndo)
    {
        Node node(1, "Network");
        ASSERT_THROW(_commandManager->undo(), char*);
        _commandManager->execute(new EditComponentCommand("IPV4", &node));
        _commandManager->execute(new EditComponentCommand("IPV6", &node));
        _commandManager->execute(new EditComponentCommand("IP", &node));
        ASSERT_EQ(0, _commandManager->getRedoCommandStack().size());
        ASSERT_EQ(3, _commandManager->getUndoCommandStack().size());
        ASSERT_STREQ("IP", node.getDescription().c_str());
        _commandManager->undo();
        ASSERT_EQ(1, _commandManager->getRedoCommandStack().size());
        ASSERT_EQ(2, _commandManager->getUndoCommandStack().size());
        ASSERT_STREQ("IPV6", node.getDescription().c_str());
        _commandManager->undo();
        ASSERT_EQ(2, _commandManager->getRedoCommandStack().size());
        ASSERT_EQ(1, _commandManager->getUndoCommandStack().size());
        ASSERT_STREQ("IPV4", node.getDescription().c_str());
        _commandManager->undo();
        ASSERT_EQ(3, _commandManager->getRedoCommandStack().size());
        ASSERT_EQ(0, _commandManager->getUndoCommandStack().size());
        ASSERT_STREQ("Network", node.getDescription().c_str());
        ASSERT_THROW(_commandManager->undo(), char*);
    }

    TEST_F(CommandManagerTest, testClearAllCommand)
    {
        Node node(1, "Network");
        _commandManager->execute(new EditComponentCommand("IPV4", &node));
        _commandManager->execute(new EditComponentCommand("IPV6", &node));
        _commandManager->execute(new EditComponentCommand("IP", &node));
        _commandManager->undo();
        _commandManager->clearAllCommand();
        ASSERT_EQ(0, _commandManager->getRedoCommandStack().size());
        ASSERT_EQ(0, _commandManager->getUndoCommandStack().size());
    }
}