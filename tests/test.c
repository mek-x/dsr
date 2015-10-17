#include <unity_fixture.h>

#include "dsr.h"

TEST_GROUP(test_DSR_api);

uint8_t addr = 1;
uint8_t buf[5] = {0xaa, 0x55, 0xaa, 0x55, 0xaa};
uint8_t buf_len = 5;

TEST_SETUP(test_DSR_api)
{
    DSR_init();
}

TEST_TEAR_DOWN(test_DSR_api)
{
    DSR_destroy();
}

TEST(test_DSR_api, canSendSomeMessage)
{
    TEST_ASSERT_EQUAL(5, DSR_send(addr, buf, buf_len));
}

TEST(test_DSR_api, sendingMessageStoresItOnBufferWithTargetAddr)
{
    DSR_send(addr, buf, buf_len);
    TEST_ASSERT_EQUAL_MEMORY(buf, getMsg(), buf_len);
    TEST_ASSERT_EQUAL(buf_len, getMsgLen());
    TEST_ASSERT_EQUAL(addr, getMsgTarget());
}

TEST(test_DSR_api, afterInitRouteCacheShouldBeClear)
{
    int routes = DSR_getRouteCount();
    TEST_ASSERT_EQUAL(0, routes);
}

TEST(test_DSR_api, canReceiveSomeMessage)
{
    int status;
    uint8_t addr_recv, buf_recv_len = 5;
    uint8_t buf_recv[5] = {0};

    setRcvMsg(addr, buf, buf_len);

    status = DSR_receive(&addr_recv, buf_recv, buf_recv_len);
    TEST_ASSERT_EQUAL_MEMORY(buf, buf_recv, buf_recv_len);
    TEST_ASSERT_EQUAL(addr_recv, addr);
    TEST_ASSERT_EQUAL(buf_len, status);
}
