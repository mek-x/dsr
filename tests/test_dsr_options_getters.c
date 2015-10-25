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

TEST(test_DSR_options_getters, getMessageType)
{
    uint8_t type = RREQ_TYPE;
    TEST_ASSERT_EQUAL(RREQ_TYPE, getMsgType(&type));
}

TEST(test_DSR_options_getters, getMessageTypeAndWrongType)
{
    uint8_t type = 0x22;
    TEST_ASSERT_EQUAL(TYPE_ERROR, getMsgType(&type));

    type = 0x08;
    TEST_ASSERT_EQUAL(TYPE_ERROR, getMsgType(&type));

    type = 0x00;
    TEST_ASSERT_EQUAL(TYPE_ERROR, getMsgType(&type));
}

TEST(test_DSR_options_getters, getRREQMessage)
{
    const uint8_t *ptr = NULL;
    uint8_t buf[] = {0x02, 0x02, 0x23, 0x15};
    struct rreq_option hdr = {
        .id = 0,
        .target = 0
    };

    ptr = getRREQMsg(buf, sizeof(buf), &hdr);
    TEST_ASSERT_EQUAL_HEX8(0x23, hdr.id);
    TEST_ASSERT_EQUAL_HEX8(0x15, hdr.target);
    TEST_ASSERT_EQUAL_PTR(buf+5, ptr);
}

TEST(test_DSR_options_getters, getRREQMessageWithAddressList)
{
    uint8_t *ptr = NULL;
    uint8_t buf[] = {0x02, 0x04, 0x44, 0x73, 0x12, 0x10};
    struct rreq_option hdr = {
        .id = 0,
        .target = 0,
        .addr_list = NULL,
        .addr_list_len = 0
    };

    ptr = getRREQMsg(buf, sizeof(buf), &hdr);
    TEST_ASSERT_EQUAL_HEX8(0x44, hdr.id);
    TEST_ASSERT_EQUAL_HEX8(0x73, hdr.target);
    TEST_ASSERT_EQUAL(2, hdr.addr_list_len);
    TEST_ASSERT_EQUAL_PTR(buf+5, hdr.addr_list);
    TEST_ASSERT_EQUAL_PTR(buf+7, ptr);
}
