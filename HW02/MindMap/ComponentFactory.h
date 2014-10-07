#pragma once
#include "Node.h"
#include "Root.h"
#include "Component.h"
#include "ConstString.h"

class ComponentFactory
{
    public:
        ComponentFactory();
        ~ComponentFactory();
        Component* createComponent(string);
        int getId();
        void setId(int);
        void countId();
    private:
        int _id;
};

