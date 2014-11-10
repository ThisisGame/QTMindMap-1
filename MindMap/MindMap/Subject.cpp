#include "Subject.h"

Subject::Subject()
{
}

Subject::~Subject()
{
}

void Subject::attach(Observer* observer)
{
    if (observer != NULL && !hasAttach(observer))
        _observers.push_back(observer);
}

void Subject::detach(Observer* observer)
{
    for (int i = 0; i < _observers.size(); i++)
    {
        if (_observers.at(i) == observer)
            _observers.erase(_observers.begin() + i);
    }
}

void Subject::notifyUpdateView()
{
    for (int i = 0; i < _observers.size(); i++)
        _observers.at(i)->updateView();
}

void Subject::notifyUpdateError()
{
    for (int i = 0; i < _observers.size(); i++)
        _observers.at(i)->updateError();
}

bool Subject::hasAttach(Observer* observer)
{
    for (int i = 0; i < _observers.size(); i++)
    {
        if (_observers.at(i) == observer)
            return true;
    }
    return false;
}