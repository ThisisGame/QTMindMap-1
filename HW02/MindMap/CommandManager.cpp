#include "CommandManager.h"

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

void CommandManager::execute(Command* command)
{
    command->execute();
    _undoCommand.push(command);
    while (!_redoCommand.empty())
    {
        delete _redoCommand.top();
        _redoCommand.pop();
    }
}

void CommandManager::redo()
{
    if (_redoCommand.empty() == true)
    {
        throw "Can't redo!\n";
    }
    Command* command = _redoCommand.top();
    command->execute();
    _undoCommand.push(command);
    _redoCommand.pop();
}

void CommandManager::undo()
{
    if (_undoCommand.empty() == true)
    {
        throw "Can't undo!\n";
    }
    Command* command = _undoCommand.top();
    command->unexcute();
    _redoCommand.push(command);
    _undoCommand.pop();
}