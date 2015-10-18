#include <string.h>
#include <unity_fixture.h>

#include "dsr_options.h"

TEST_GROUP(test_DSR_options);

uint8_t message_buffer[10];

TEST_SETUP(test_DSR_options)
{
    memset(message_buffer, 0xa5, sizeof(message_buffer));
}

TEST_TEAR_DOWN(test_DSR_options)
{
}

TEST(test_DSR_options, createRREQOption)
{
    uint8_t expected_output[] = {0x2, 2 ,0, 0};
    int length;

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 0, 0);

    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createRREQsWithDifferentTargetsAndIds)
{
    uint8_t expected_output[] = {0x2, 2 ,1, 1};
    int length;

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 1, 1);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 2, 3);
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

TEST(test_DSR_options, createRREPOption)
{
    uint8_t expected_output[] = {0x3, 0x03, 0x01, 0x02, 0x03};
    uint8_t addr_list[] = {0x01, 0x02, 0x03};
    int length;

    length = createRREPMsg(message_buffer, sizeof(message_buffer), addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createRREPMsgReturnsErrorWhenBufferTooSmall)
{
    int length;

    length = createRREPMsg(message_buffer, 2, NULL, 1);
    TEST_ASSERT_EQUAL(-1, length);
}

TEST(test_DSR_options, createRERROption)
{
    uint8_t expected_output[] = {0x1, 0x3, 0x0, 0x1, 0x2};
    int length;

    length = createRERRMsg(message_buffer, 2, 0, 0 ,0);
    TEST_ASSERT_EQUAL(-1, length);

    length = createRERRMsg(message_buffer, sizeof(message_buffer), 0, 1, 2);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);

    expected_output[2] = 1;
    expected_output[3] = 3;
    expected_output[4] = 5;

    length = createRERRMsg(message_buffer, sizeof(message_buffer), 1, 3, 5);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createAREQOption)
{
    uint8_t expected_output[] = {0x4, 0x1, 0x1};
    int length;

    length = createAREQMsg(message_buffer, 2, 0);
    TEST_ASSERT_EQUAL(-1, length);

    length = createAREQMsg(message_buffer, sizeof(message_buffer), 1);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createAREPOption)
{
    uint8_t expected_output[] = {0x5, 0x3, 0x0, 0x1, 0x2};
    int length;

    length = createAREPMsg(message_buffer, 2, 0, 1, 2);
    TEST_ASSERT_EQUAL(-1, length);

    length = createAREPMsg(message_buffer, sizeof(message_buffer), 0, 1, 2);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createROUTOption)
{
    uint8_t expected_output[] = {0x6, 0x3, 0x2, 0x1, 0x2};
    uint8_t addr_list[] = {0x01, 0x02};
    int length;

    length = createROUTMsg(message_buffer, 2, addr_list, 2);
    TEST_ASSERT_EQUAL(-1, length);

    length = createROUTMsg(message_buffer, sizeof(message_buffer), addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createDATAOption)
{
    uint8_t expected_output[] = {0x7, 0x3, 0xaa, 0x55, 0xaa};
    uint8_t data[] = {0xaa, 0x55, 0xaa};
    int length;

    length = createDATAMsg(message_buffer, 2, data, 3);
    TEST_ASSERT_EQUAL(-1, length);

    length = createDATAMsg(message_buffer, sizeof(message_buffer), data, sizeof(data));
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}
