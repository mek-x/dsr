#include <unity_fixture.h>

TEST_GROUP(test);

TEST_SETUP(test)
{
}

TEST_TEAR_DOWN(test)
{
}

TEST(test, sample_test)
{
    TEST_ASSERT_EQUAL(1, 1);
}
