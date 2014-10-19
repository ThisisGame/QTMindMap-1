#include "CommandManager.h"
#include "ConstString.h"

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
}

void CommandManager::execute(Command* command)
{
    try
    {
        command->execute();
        _undoCommand.push(command);
        while (!_redoCommand.empty())
        {
            delete _redoCommand.top();
            _redoCommand.pop();
        }
    }
    catch (const char* message)
    {
        delete command;
        throw message;
    }
}

void CommandManager::redo()
{
    if (_redoCommand.empty() == true)
    {
        throw ERROR_REDO;
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
        throw ERROR_UNDO;
    }
    Command* command = _undoCommand.top();
    command->unexcute();
    _redoCommand.push(command);
    _undoCommand.pop();
}

void CommandManager::clearAllCommand()   //清除所有Command
{
    while (!_undoCommand.empty())
    {
        undo();
    }
    while (!_redoCommand.empty())
    {
        Command* command = _redoCommand.top();
        command->deleteCommand();
        delete command;
        _redoCommand.pop();
    }
}