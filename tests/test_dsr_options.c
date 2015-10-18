#include <unity_fixture.h>

#include "dsr_options.h"

TEST_GROUP(test_DSR_options);

uint8_t message_buffer[10] = {0};

TEST_SETUP(test_DSR_options)
{
}

TEST_TEAR_DOWN(test_DSR_options)
{
}

TEST(test_DSR_options, createRREQOption)
{
    uint8_t expected_output[] = {0x20, 2 ,0, 0};
    int length;

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 0, 0);

    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createRREQsWithDifferentTargetsAndIds)
{
    uint8_t expected_output[] = {0x20, 2 ,1, 1};
    int length;

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 1, 1);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 3, 2);
    expected_output[2] = 2;
    expected_output[3] = 3;
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createRREQMsgReturnsErrorWhenBufferTooSmall)
{
    int length;

    length = createRREQMsg(message_buffer, 2, 0, 0);
    TEST_ASSERT_EQUAL(-1, length);
}
