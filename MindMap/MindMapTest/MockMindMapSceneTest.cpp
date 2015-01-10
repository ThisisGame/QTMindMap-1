#include <gtest/gtest.h>
#include "MockMindMapScene.h"

namespace MindMapTest
{
    class MockMindMapSceneTest : public testing::Test
    {
        protected:
            virtual void SetUp()
            {
            }
            virtual void TearDown()
            {
            }
            MockMindMapScene _scene;
    };

    TEST_F(MockMindMapSceneTest, testGetWidth)
    {
        ASSERT_EQ(50, _scene.getWidth());
    }

    TEST_F(MockMindMapSceneTest, testGetHeight)
    {
        _scene.createItem(0, "test");
        ASSERT_EQ(100, _scene.getHeight());
        _scene.createItem(0, "testTestTestTestTestTest");
        ASSERT_EQ(600, _scene.getHeight());
    }
}