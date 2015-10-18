#include <unity_fixture.h>

#include "dsr_options.h"

TEST_GROUP(test_DSR_options);


TEST_SETUP(test_DSR_options)
{
}

TEST_TEAR_DOWN(test_DSR_options)
{
}

TEST(test_DSR_options, createRREQOption)
{
    uint8_t message_buffer[10] = {0};
    uint8_t expected_output[] = {0x20, 2 ,0, 0};
    uint8_t length;

    length = createRREQMsg(message_buffer, 10, 0);

    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createRREQsWithDifferentTargets)
{
    uint8_t message_buffer[10] = {0};
    uint8_t expected_output[] = {0x20, 2 ,0, 1};
    uint8_t length;

    length = createRREQMsg(message_buffer, 10, 1);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);

    length = createRREQMsg(message_buffer, 10, 3);
    expected_output[3] = 3;
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}
