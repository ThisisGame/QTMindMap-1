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
        void clearAllCommand();
    private:
        stack<Command*> _redoCommand;
        stack<Command*> _undoCommand;
};

