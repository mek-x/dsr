#include <string.h>
#include <unity_fixture.h>

#include "dsr_options.h"

TEST_GROUP(test_DSR_options);

#define MESSAGE_BUFFER_SIZE 10
uint8_t message_buffer[MESSAGE_BUFFER_SIZE];
int length;

TEST_SETUP(test_DSR_options)
{
    memset(message_buffer, 0xa5, sizeof(message_buffer));
    length = 0;
}

TEST_TEAR_DOWN(test_DSR_options)
{
}

TEST(test_DSR_options, createRREQOptionEmpty)
{
    uint8_t expected_output[] = {2, 2 ,1, 1};

    struct rreq_option hdr = {
        .id = 1,
        .target = 1,
        .addr_list = NULL,
        .addr_list_len = 0
    };

    length = createRREQMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createRREQOptionWithAddressList)
{
    uint8_t expected_output[] = {0x02, 0x05 ,0x01, 0x01, 0x01, 0x02, 0x03};
    uint8_t addr_list[] = {1, 2, 3};

    struct rreq_option hdr = {
        .id = 1,
        .target = 1,
        .addr_list = addr_list,
        .addr_list_len = sizeof(addr_list)
    };

    length = createRREQMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createRREPOption)
{
    uint8_t expected_output[] = {0x3, 0x03, 0x01, 0x02, 0x03};
    uint8_t addr_list[] = {0x01, 0x02, 0x03};

    struct rrep_option hdr = {
        .addr_list = addr_list,
        .addr_list_len = sizeof(addr_list)
    };

    length = createRREPMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createRERROption)
{
    uint8_t expected_output[] = {0x1, 0x3, 0x0, 0x1, 0x2};
    struct rerr_option hdr = {
        .err_type = 0,
        .source = 1,
        .target = 2
    };

    length = createRERRMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createAREQOption)
{
    uint8_t expected_output[] = {0x4, 0x1, 0x1};
    struct areq_option hdr = {
        .id = 1
    };

    length = createAREQMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createAREPOption)
{
    uint8_t expected_output[] = {0x5, 0x3, 0x0, 0x1, 0x2};
    struct arep_option hdr = {
        .id = 0,
        .source = 1,
        .target = 2
    };

    length = createAREPMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createROUTOption)
{
    uint8_t expected_output[] = {0x6, 0x3, 0x2, 0x1, 0x2};
    uint8_t addr_list[] = {0x01, 0x02};
    struct rout_option hdr = {
        .segments_left = 2,
        .addr_list = addr_list,
        .addr_list_len = sizeof(addr_list)
    };

    length = createROUTMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createDATAOption)
{
    uint8_t expected_output[] = {0x7, 0x3, 0xaa, 0x55, 0xaa};
    uint8_t data[] = {0xaa, 0x55, 0xaa};
    struct data_option hdr = {
        .data = data,
        .data_len = sizeof(data)
    };

    length = createDATAMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(sizeof(expected_output), length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, length);
}

TEST(test_DSR_options, createMessageDataWithRoute)
{
    uint8_t expected_output[] = {0x6, 0x3, 0x2, 0x12, 0x31, 0x7, 0x3, 0xaa, 0x55, 0xaa};
    uint8_t addr_list[] = {0x12, 0x31};
    uint8_t data[] = {0xaa, 0x55, 0xaa};

    struct rout_option rout_hdr = {
        .segments_left = 2,
        .addr_list = addr_list,
        .addr_list_len = sizeof(addr_list)
    };

    struct data_option data_hdr = {
        .data = data,
        .data_len = sizeof(data)
    };

    length = createROUTMsg(message_buffer, sizeof(message_buffer), &rout_hdr);
    length = createDATAMsg(message_buffer+length, sizeof(message_buffer)-length, &data_hdr);

    TEST_ASSERT_NOT_EQUAL(ERROR_CREATE_MSG, length);
    TEST_ASSERT_EQUAL_MEMORY(expected_output, message_buffer, sizeof(expected_output));
}
