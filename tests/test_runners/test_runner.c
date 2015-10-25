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
    RUN_TEST_CASE(test_DSR_options, createRREQOptionEmpty);
    RUN_TEST_CASE(test_DSR_options, createRREQOptionWithAddressList);
    RUN_TEST_CASE(test_DSR_options, createRREPOption);
    RUN_TEST_CASE(test_DSR_options, createRERROption);
    RUN_TEST_CASE(test_DSR_options, createAREQOption);
    RUN_TEST_CASE(test_DSR_options, createAREPOption);
    RUN_TEST_CASE(test_DSR_options, createROUTOption);
    RUN_TEST_CASE(test_DSR_options, createDATAOption);
    RUN_TEST_CASE(test_DSR_options, createMessageDataWithRoute);
}

TEST_GROUP_RUNNER(test_DSR_options_errors)
{
    RUN_TEST_CASE(test_DSR_options_errors, createRREQOptionErrorHandling);
    RUN_TEST_CASE(test_DSR_options_errors, createRREPOptionErrorHandling);
    RUN_TEST_CASE(test_DSR_options_errors, createRERROptionErrorHandling);
    RUN_TEST_CASE(test_DSR_options_errors, createAREQOptionErrorHandling);
    RUN_TEST_CASE(test_DSR_options_errors, createAREPOptionErrorHandling);
    RUN_TEST_CASE(test_DSR_options_errors, createROUTOptionErrorHandling);
    RUN_TEST_CASE(test_DSR_options_errors, createDATAOptionErrorHandling);
}
