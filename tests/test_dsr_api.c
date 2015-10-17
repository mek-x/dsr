#include <unity_fixture.h>

#include "dsr.h"

TEST_GROUP(test_DSR_api);

uint8_t addr = 1, buf_len = 5;
uint8_t buf[5] = {0xaa, 0x55, 0xaa, 0x55, 0xaa};

#define NODE_ADDR 21
DSR_Node node;

TEST_SETUP(test_DSR_api)
{
    node = DSR_init(NODE_ADDR);
}

TEST_TEAR_DOWN(test_DSR_api)
{
    DSR_destroy(&node);
}

TEST(test_DSR_api, nodeAddrSetAfterInit)
{
    TEST_ASSERT_EQUAL(NODE_ADDR, getNodeAddr(node));
}

TEST(test_DSR_api, afterDestructionNodeShouldBeNull)
{
    DSR_Node node2;
    node2 = DSR_init(33);
    DSR_destroy(&node2);
    TEST_ASSERT_EQUAL(NULL, node2);
}

TEST(test_DSR_api, functionsShouldReturnErrorWhenNodeIsNull)
{
    DSR_destroy(&node);
    TEST_ASSERT_EQUAL(-1, DSR_send(node, addr, buf, buf_len));
    TEST_ASSERT_EQUAL(-1, DSR_getRouteCount(node));
    TEST_ASSERT_EQUAL(-1, DSR_receive(node, NULL, NULL, 0));
}

TEST(test_DSR_api, canSetTwoNodesWithDistinctAddresses)
{
    DSR_Node node2;
    node2 = DSR_init(33);

    TEST_ASSERT_EQUAL(NODE_ADDR, getNodeAddr(node));
    TEST_ASSERT_EQUAL(33, getNodeAddr(node2));

    DSR_destroy(&node2);
}

TEST(test_DSR_api, canSendSomeMessage)
{
    TEST_ASSERT_EQUAL(5, DSR_send(node, addr, buf, buf_len));
}

TEST(test_DSR_api, sendingMessageStoresItOnBufferWithTargetAddr)
{
    DSR_send(node, addr, buf, buf_len);
    TEST_ASSERT_EQUAL_MEMORY(buf, getMsg(node, 0), buf_len);
    TEST_ASSERT_EQUAL(buf_len, getMsgLen(node, 0));
    TEST_ASSERT_EQUAL(addr, getMsgTarget(node, 0));
}

TEST(test_DSR_api, afterInitRouteCacheShouldBeClear)
{
    int routes = DSR_getRouteCount(node);
    TEST_ASSERT_EQUAL(0, routes);
}

TEST(test_DSR_api, canReceiveSomeMessage)
{
    int status;
    uint8_t addr_recv, buf_recv_len = 5;
    uint8_t buf_recv[5] = {0};

    setRcvMsg(node, addr, buf, buf_len);

    status = DSR_receive(node, &addr_recv, buf_recv, buf_recv_len);
    TEST_ASSERT_EQUAL_MEMORY(buf, buf_recv, buf_recv_len);
    TEST_ASSERT_EQUAL(addr_recv, addr);
    TEST_ASSERT_EQUAL(buf_len, status);
}

TEST(test_DSR_api, storeTwoDifferentMessagesOnBuffer)
{
    uint8_t addr2 = 2, buf_len2 = 4;
    uint8_t buf2[] = {0x1, 0x2, 0x3, 0x4};

    DSR_send(node, addr,  buf,  buf_len);
    DSR_send(node, addr2, buf2, buf_len2);

    TEST_ASSERT_EQUAL_MEMORY(buf, getMsg(node, 0), buf_len);
    TEST_ASSERT_EQUAL_MEMORY(buf2, getMsg(node, 1), buf_len2);
    TEST_ASSERT_EQUAL(addr, getMsgTarget(node, 0));
    TEST_ASSERT_EQUAL(addr2, getMsgTarget(node, 1));
    TEST_ASSERT_EQUAL(buf_len, getMsgLen(node, 0));
    TEST_ASSERT_EQUAL(buf_len2, getMsgLen(node, 1));
}

TEST(test_DSR_api, sendShouldReturnErrorWhenOverflow)
{
    for(int i = 0; i < MSG_BUFFER_SIZE; i++) {
        DSR_send(node, addr, buf, buf_len);
    }
    TEST_ASSERT_EQUAL(-1, DSR_send(node, addr, buf, buf_len));
}
