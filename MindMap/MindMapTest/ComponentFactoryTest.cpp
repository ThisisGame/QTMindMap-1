#include <gtest/gtest.h>
#include "ComponentFactory.h"
#include "Component.h"
using namespace std;

namespace MindMapTest
{
    class ComponentFactoryTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
                _componentFactory = new ComponentFactory();
            }
            virtual void TearDown()
            {
                delete _componentFactory;
            }
            ComponentFactory* _componentFactory;
    };

    TEST_F(ComponentFactoryTest, testSetId)
    {
        _componentFactory->setId(10);
        ASSERT_EQ(10, _componentFactory->getId());
    }

    TEST_F(ComponentFactoryTest, testCountId)
    {
        _componentFactory->countId();
        _componentFactory->countId();
        _componentFactory->countId();
        _componentFactory->countId();
        ASSERT_EQ(4, _componentFactory->getId());
    }

    TEST_F(ComponentFactoryTest, testUnCountId)
    {
        _componentFactory->countId();
        _componentFactory->countId();
        _componentFactory->countId();
        _componentFactory->unCountId();
        ASSERT_EQ(2, _componentFactory->getId());
    }

    TEST_F(ComponentFactoryTest, testCreateComponent)
    {
        Component* component;
        component = _componentFactory->createComponent("Root");
        ASSERT_STREQ("Root", component->getType().c_str());
        delete component;
        component = _componentFactory->createComponent("Node");
        ASSERT_STREQ("Node", component->getType().c_str());
        delete component;
        component = _componentFactory->createComponent("Triangle");
        ASSERT_STREQ("Triangle", component->getType().c_str());
        delete component;
        component = _componentFactory->createComponent("Circle");
        ASSERT_STREQ("Circle", component->getType().c_str());
        delete component;
        component = _componentFactory->createComponent("Rectangle");
        ASSERT_STREQ("Rectangle", component->getType().c_str());
        delete component;
        ASSERT_THROW(_componentFactory->createComponent("NoComponent")->getType().c_str(), char*);
    }
}