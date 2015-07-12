SRC_DIR = src
INCLUDE_DIR = inc
TEST_DIR = tests

.PHONY: test

test:
	$(MAKE) -C $(TEST_DIR)

clean:
	$(MAKE) -C $(TEST_DIR) clean
