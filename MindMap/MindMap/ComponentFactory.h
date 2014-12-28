#pragma once
#include "Component.h"

class ComponentFactory
{
    public:
        ComponentFactory();
        ~ComponentFactory();
        Component* createComponent(string);
        int getId();
        void setId(int);
        void countId();
        void unCountId();
    private:
        int _id;
};

