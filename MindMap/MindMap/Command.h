#pragma once
class Command
{
    public:
        Command();
        virtual ~Command();
        virtual void execute() = 0;
        virtual void unexcute() = 0;
        virtual void deleteCommand() = 0;
};

