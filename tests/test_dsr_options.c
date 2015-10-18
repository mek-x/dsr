#include <unity_fixture.h>

#include "dsr_options.h"

TEST_GROUP(test_DSR_options);

u

TEST_SETUP(test_DSR_options)
{

}

TEST_TEAR_DOWN(test_DSR_options)
{

}

TEST(test_DSR_options, nodeAddrSetAfterInit)
{
    TEST_ASSERT_EQUAL(NODE_ADDR, getNodeAddr(node));
}
