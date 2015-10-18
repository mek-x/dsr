#include <unity_fixture.h>

static void RunAllTests(void)
{
	RUN_TEST_GROUP(test_DSR_api);
	RUN_TEST_GROUP(test_DSR_options);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}
