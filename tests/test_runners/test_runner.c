#include <unity_fixture.h>

TEST_GROUP_RUNNER(test_DSR_api)
{
    RUN_TEST_CASE(test_DSR_api, canSendSomeMessage);
    RUN_TEST_CASE(test_DSR_api, sendingMessageStoresItOnBuffer);
    RUN_TEST_CASE(test_DSR_api, afterInitRouteCacheShouldBeClear);
}