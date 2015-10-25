#include <string.h>
#include <unity_fixture.h>

#include "dsr_options.h"

TEST_GROUP(test_DSR_options_getters);

TEST_SETUP(test_DSR_options_getters)
{
}

TEST_TEAR_DOWN(test_DSR_options_getters)
{
}

TEST(test_DSR_options_getters, getMsgTypeFromBuffer)
{
    uint8_t type = RREQ_TYPE;
    TEST_ASSERT_EQUAL(RREQ_TYPE, getMsgType(&type));
}

TEST(test_DSR_options_getters, getMsgTypeFromBufferWrongType)
{
    uint8_t type = 0x22;
    TEST_ASSERT_EQUAL(TYPE_ERROR, getMsgType(&type));

    type = 0x08;
    TEST_ASSERT_EQUAL(TYPE_ERROR, getMsgType(&type));

    type = 0x00;
    TEST_ASSERT_EQUAL(TYPE_ERROR, getMsgType(&type));
}
