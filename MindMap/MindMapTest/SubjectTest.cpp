#include <gtest/gtest.h>
#include "Subject.h"
#include "Observer.h"

namespace MindMapTest
{
    class SubjectTest : public testing::Test
    {
        protected:
            // Fields
            Subject* _subject;
            Observer* _observer1;
            Observer* _observer2;

            // Methods
            virtual void SetUp()
            {
                _subject = new Subject();
                _observer1 = new Observer();
                _observer2 = new Observer();
            }
            virtual void TearDown()
            {
                delete _subject;
                delete _observer1;
                delete _observer2;
            }

            bool hasAttach(Observer* observer)
            {
                return _subject->hasAttach(observer);
            }

            int getObserverSize()
            {
                return _subject->_observers.size();
            }
    };

    TEST_F(SubjectTest, testSttach)
    {
        // Check current observers
        EXPECT_EQ(0, getObserverSize());
        // Attach NULL
        _subject->attach(NULL);
        EXPECT_EQ(0, getObserverSize());
        // Attach observer1
        _subject->attach(_observer1);
        EXPECT_EQ(1, getObserverSize());
        // Attach observer1 again
        _subject->attach(_observer1);
        EXPECT_EQ(1, getObserverSize());
        // Attach observer2
        _subject->attach(_observer2);
        EXPECT_EQ(2, getObserverSize());
    }

    TEST_F(SubjectTest, testDetach)
    {
        // Check current observers
        EXPECT_EQ(0, getObserverSize());
        // Attach observer1 and observer2
        _subject->attach(_observer1); // Warn: call other method.
        _subject->attach(_observer2); // Warn: call other method.
        EXPECT_EQ(2, getObserverSize());
        // Detach
        _subject->detach(_observer2);
        EXPECT_EQ(1, getObserverSize());
    }

    TEST_F(SubjectTest, testNotify)
    {
        _subject->attach(_observer1); // Warn: call other method.
        _subject->attach(_observer2); // Warn: call other method.
        _subject->notifyUpdateView();
        _subject->notifyUpdateError();
    }

    TEST_F(SubjectTest, testHasAttach)
    {
        // Check current observers
        EXPECT_EQ(0, getObserverSize());
        // Attach observer1
        _subject->attach(_observer1); // Warn: call other method.
        EXPECT_EQ(1, getObserverSize());
        // Check
        EXPECT_TRUE(hasAttach(_observer1));
        EXPECT_FALSE(hasAttach(_observer2));
    }
}