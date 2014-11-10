#pragma once
#include "Command.h"
#include <stack>
using namespace std;

class CommandManager
{
    public:
        CommandManager();
        ~CommandManager();
        void execute(Command*);
        void redo();
        void undo();
        stack<Command*> getRedoCommandStack();
        stack<Command*> getUndoCommandStack();
        void clearAllCommand();
    private:
        stack<Command*> _redoCommand;
        stack<Command*> _undoCommand;
};

