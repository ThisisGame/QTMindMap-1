#pragma once
class Observer
{
    public:
        Observer();
        virtual ~Observer();
        virtual void updateView();
        virtual void updateError();
};

