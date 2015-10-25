#include <string.h>
#include <unity_fixture.h>

#include "dsr_options.h"

#define MESSAGE_BUFFER_SIZE 10
uint8_t message_buffer[MESSAGE_BUFFER_SIZE];
uint8_t message_buffer_original[MESSAGE_BUFFER_SIZE];
int length;

TEST_GROUP(test_DSR_options_errors);

TEST_SETUP(test_DSR_options_errors)
{
    memset(message_buffer, 0xa5, MESSAGE_BUFFER_SIZE);
    memcpy(message_buffer_original, message_buffer, MESSAGE_BUFFER_SIZE);
    length = 0;
}

TEST_TEAR_DOWN(test_DSR_options_errors)
{
    TEST_ASSERT_EQUAL_MEMORY(message_buffer_original, message_buffer, MESSAGE_BUFFER_SIZE);
}

TEST(test_DSR_options_errors, createRREQOptionErrorHandling)
{
    struct rreq_option hdr = {
        .id = 1,
        .target = 1,
        .addr_list = NULL,
        .addr_list_len = 0
    };

    length = createRREQMsg(message_buffer, MESSAGE_BUFFER_SIZE, NULL);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRREQMsg(NULL, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRREQMsg(message_buffer, 3, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    hdr.addr_list_len = 1;
    length = createRREQMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options_errors, createRREPOptionErrorHandling)
{
    uint8_t addr_list[] = {0x01, 0x02, 0x03};
    struct rrep_option hdr = {
        .addr_list = NULL,
        .addr_list_len = 0
    };

    length = createRREPMsg(message_buffer, MESSAGE_BUFFER_SIZE, NULL);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    hdr.addr_list = addr_list;

    length = createRREPMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    hdr.addr_list_len = sizeof(addr_list);

    length = createRREPMsg(NULL, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRREPMsg(message_buffer, 4, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options_errors, createRERROptionErrorHandling)
{
    struct rerr_option hdr = {
        .err_type = 0,
        .source = 1,
        .target = 2
    };

    length = createRERRMsg(message_buffer, MESSAGE_BUFFER_SIZE, NULL);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRERRMsg(message_buffer, 4, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createRERRMsg(NULL, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options_errors, createAREQOptionErrorHandling)
{
    struct areq_option hdr = {
        .id = 1
    };

    length = createAREQMsg(message_buffer, MESSAGE_BUFFER_SIZE, NULL);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createAREQMsg(message_buffer, 2, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createAREQMsg(NULL, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options_errors, createAREPOptionErrorHandling)
{
    struct arep_option hdr = {
        .id = 0,
        .source = 1,
        .target = 2
    };

    length = createAREPMsg(message_buffer, MESSAGE_BUFFER_SIZE, NULL);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createAREPMsg(message_buffer, 4, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createAREPMsg(NULL, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options_errors, createROUTOptionErrorHandling)
{
    uint8_t addr_list[] = {0x01, 0x02};
    struct rout_option hdr = {
        .segments_left = 2,
        .addr_list = NULL,
        .addr_list_len = 0
    };

    length = createROUTMsg(message_buffer, MESSAGE_BUFFER_SIZE, NULL);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    hdr.addr_list = addr_list;

    length = createROUTMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    hdr.addr_list_len = sizeof(addr_list);

    length = createROUTMsg(NULL, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createROUTMsg(message_buffer, 4, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}

TEST(test_DSR_options_errors, createDATAOptionErrorHandling)
{
    uint8_t data[] = {0xaa, 0x55, 0xaa};
    struct data_option hdr = {
        .data = NULL,
        .data_len = 0
    };

    length = createDATAMsg(message_buffer, MESSAGE_BUFFER_SIZE, NULL);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    hdr.data = data;

    length = createDATAMsg(message_buffer, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    hdr.data_len = sizeof(data);

    length = createDATAMsg(NULL, MESSAGE_BUFFER_SIZE, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);

    length = createDATAMsg(message_buffer, 4, &hdr);
    TEST_ASSERT_EQUAL(ERROR_CREATE_MSG, length);
}
