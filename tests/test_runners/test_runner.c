#include <unity_fixture.h>

TEST_GROUP_RUNNER(test_DSR_api)
{
    RUN_TEST_CASE(test_DSR_api, nodeAddrSetAfterInit);
    RUN_TEST_CASE(test_DSR_api, afterDestructionNodeShouldBeNull);
    RUN_TEST_CASE(test_DSR_api, functionsShouldReturnErrorWhenNodeIsNull);
    RUN_TEST_CASE(test_DSR_api, canSetTwoNodesWithDistinctAddresses);
    RUN_TEST_CASE(test_DSR_api, canSendSomeMessage);
    RUN_TEST_CASE(test_DSR_api, sendingMessageStoresItOnBufferWithTargetAddr);
    RUN_TEST_CASE(test_DSR_api, afterInitRouteCacheShouldBeClear);
    RUN_TEST_CASE(test_DSR_api, canReceiveSomeMessage);
    RUN_TEST_CASE(test_DSR_api, storeTwoDifferentMessagesOnBuffer);
    RUN_TEST_CASE(test_DSR_api, sendShouldReturnErrorWhenOverflow);
}

TEST_GROUP_RUNNER(test_DSR_options)
{
    RUN_TEST_CASE(test_DSR_options, createRREQOption);
    RUN_TEST_CASE(test_DSR_options, createRREQsWithDifferentTargets);
}
