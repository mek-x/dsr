UNITY_DIR = unity
UNITY_FIXTURE_DIR = unity/unity_fixture
TEST_RUNNERS_DIR = test_runners

CC = gcc
RM = rm

CFLAGS = -std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wmissing-declarations

TEST_TARGET1 = all_tests

SRC_TEST_FILES1=\
  $(UNITY_DIR)/unity.c \
  $(UNITY_FIXTURE_DIR)/unity_fixture.c \
  test_dsr_api.c test_dsr_options.c test_dsr_options_errors.c\
  $(TEST_RUNNERS_DIR)/test_runner.c \
  $(TEST_RUNNERS_DIR)/all_tests.c

DSR_FILES=\
  ../src/dsr.c \
  ../src/dsr_options.c

INC_DIRS=-I../inc -I$(UNITY_DIR) -I$(UNITY_FIXTURE_DIR)


all: clean default

default:
	$(CC) $(CFLAGS) $(INC_DIRS) $(SRC_TEST_FILES1) $(DSR_FILES) -o $(TEST_TARGET1)
	./$(TEST_TARGET1)

clean:
	$(RM) -f $(TEST_TARGET1)
