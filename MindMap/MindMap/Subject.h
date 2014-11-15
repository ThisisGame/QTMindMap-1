#pragma once
#include <vector>
#include "Observer.h"
using namespace std;

namespace MindMapTest
{
    class SubjectTest;
}

class Subject
{
        friend class MindMapTest::SubjectTest;
    public:
        Subject();
        virtual ~Subject();
        void attach(Observer* observer);
        void detach(Observer* observer);
        void notifyUpdateView();
        void notifyUpdateError();
    private:
        vector<Observer*> _observers;
        bool hasAttach(Observer* observer);
};

