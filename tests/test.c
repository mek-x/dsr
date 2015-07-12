#include <unity_fixture.h>

#include "dsr.h"

TEST_GROUP(test);

TEST_SETUP(test)
{
}

TEST_TEAR_DOWN(test)
{
}

TEST(test, CanSendSomeMessage)
{
    uint8_t addr = 1;
    uint8_t buf[5];
    uint8_t buf_len = 5;

    TEST_ASSERT_EQUAL(DSR_send(addr, buf, buf_len), 5);
}
