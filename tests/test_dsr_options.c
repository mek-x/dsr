#include <string.h>
#include <unity_fixture.h>

#include "dsr_options.h"

TEST_GROUP(test_DSR_options);

uint8_t message_buffer[10];
int length;

TEST_SETUP(test_DSR_options)
{
    memset(message_buffer, 0xa5, sizeof(message_buffer));
    length = 0;
}

TEST_TEAR_DOWN(test_DSR_options)
{
}

TEST(test_DSR_options, createRREQOption)
{
    uint8_t expected_output[] = {2, 2 ,1, 1};
    uint8_t expected_output_with_list[] = {2, 5 ,1, 1, 1, 2 ,3};
    uint8_t addr_list[] = {1, 2, 3};

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 1, 1, NULL, 0);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 1, 1, addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL_MEMORY(expected_output_with_list, message_buffer, length);

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 2, 3, addr_list, sizeof(addr_list));
    expected_output_with_list[2] = 2;
    expected_output_with_list[3] = 3;
    TEST_ASSERT_EQUAL_MEMORY(expected_output_with_list, message_buffer, length);
}

TEST(test_DSR_options, createRREQOptionErrorHandling)
{
    uint8_t addr_list[] = {1, 2, 3};

    length = createRREQMsg(message_buffer, 6, 0, 0, addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRREQMsg(NULL, sizeof(message_buffer), 0, 0, addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRREQMsg(message_buffer, sizeof(message_buffer), 0, 0, NULL, sizeof(addr_list));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options, createRREPOption)
{
    uint8_t expected_output[] = {0x3, 0x03, 0x01, 0x02, 0x03};
    uint8_t addr_list[] = {0x01, 0x02, 0x03};

    length = createRREPMsg(message_buffer, sizeof(message_buffer), addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createRREPOptionErrorHandling)
{
    uint8_t addr_list[] = {0x01, 0x02, 0x03};

    length = createRREPMsg(message_buffer, 4, addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRREPMsg(NULL, sizeof(message_buffer), addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRREPMsg(message_buffer, sizeof(message_buffer), addr_list, 0);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRREPMsg(message_buffer, sizeof(message_buffer), NULL, sizeof(addr_list));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options, createRERROption)
{
    uint8_t expected_output[] = {0x1, 0x3, 0x0, 0x1, 0x2};

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

TEST(test_DSR_options, createRERROptionErrorHandling)
{
    length = createRERRMsg(message_buffer, 4, 0, 0 ,0);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRERRMsg(NULL, sizeof(message_buffer), 0, 0 ,0);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options, createAREQOption)
{
    uint8_t expected_output[] = {0x4, 0x1, 0x1};

    length = createAREQMsg(message_buffer, sizeof(message_buffer), 1);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createAREQOptionErrorHandling)
{
    length = createAREQMsg(message_buffer, 2, 1);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createAREQMsg(NULL, sizeof(message_buffer), 1);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options, createAREPOption)
{
    uint8_t expected_output[] = {0x5, 0x3, 0x0, 0x1, 0x2};

    length = createAREPMsg(message_buffer, sizeof(message_buffer), 0, 1, 2);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createAREPOptionErrorHandling)
{
    length = createAREPMsg(message_buffer, 4, 0, 1, 2);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createAREPMsg(NULL, sizeof(message_buffer), 0, 1, 2);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options, createROUTOption)
{
    uint8_t expected_output[] = {0x6, 0x3, 0x2, 0x1, 0x2};
    uint8_t addr_list[] = {0x01, 0x02};

    length = createROUTMsg(message_buffer, sizeof(message_buffer), addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createROUTOptionErrorHandling)
{
    uint8_t addr_list[] = {0x01, 0x02};

    length = createROUTMsg(message_buffer, 3, addr_list, sizeof(addr_list));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createROUTMsg(NULL, sizeof(message_buffer), addr_list ,sizeof(addr_list));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createROUTMsg(message_buffer, sizeof(message_buffer), addr_list ,0);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createROUTMsg(message_buffer, sizeof(message_buffer), NULL ,sizeof(addr_list));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options, createDATAOption)
{
    uint8_t expected_output[] = {0x7, 0x3, 0xaa, 0x55, 0xaa};
    uint8_t data[] = {0xaa, 0x55, 0xaa};

    length = createDATAMsg(message_buffer, sizeof(message_buffer), data, sizeof(data));
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createDATAOptionErrorHandling)
{
    uint8_t data[] = {0xaa, 0x55, 0xaa};

    length = createDATAMsg(message_buffer, 4, data, sizeof(data));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createDATAMsg(NULL, sizeof(message_buffer), data ,sizeof(data));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createDATAMsg(message_buffer, sizeof(message_buffer), data ,0);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createDATAMsg(message_buffer, sizeof(message_buffer), NULL ,sizeof(data));
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options, createMessageDataWithRoute)
{
    uint8_t expected_output[] = {0x6, 0x3, 0x2, 0x12, 0x31, 0x7, 0x3, 0xaa, 0x55, 0xaa};
    uint8_t addr_list[] = {0x12, 0x31};
    uint8_t data[] = {0xaa, 0x55, 0xaa};

    length = createROUTMsg(message_buffer, sizeof(message_buffer), addr_list, sizeof(addr_list));
    length = createDATAMsg(message_buffer+length, sizeof(message_buffer)-length, data, sizeof(data));

    TEST_ASSERT_NOT_EQUAL(ERROR_CREATE_MSG, length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, sizeof(expected_output));
}
