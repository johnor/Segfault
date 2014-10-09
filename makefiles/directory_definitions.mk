BUILD_DIR=build
DEBUG_BUILD_OUTPUT_DIR = $(BUILD_DIR)/debug
RELEASE_BUILD_OUTPUT_DIR = $(BUILD_DIR)/release
UNIT_TEST_BUILD_OUTPUT_DIR = $(BUILD_DIR)/unit_test
HSIT_MASTER_BUILD_OUTPUT_DIR = $(BUILD_DIR)/hsit_master
HSIT_SLAVE_BUILD_OUTPUT_DIR = $(BUILD_DIR)/hsit_slave
MOCK_DIR = $(UNIT_TEST_BUILD_OUTPUT_DIR)/mocks

SRC_DIR = src
TEST_SRC_DIR = $(SRC_DIR)/test
OBJ_DIR = $(BUILD_OUTPUT_DIR)/obj

DEPS_DIR = $(BUILD_OUTPUT_DIR)/deps

LIB_DIR = $(BUILD_OUTPUT_DIR)/lib

BIN_DIR  = $(BUILD_OUTPUT_DIR)/bin

UNITY_DIR = $(TEST_SRC_DIR)/unity
CMOCK_DIR = $(TEST_SRC_DIR)/cmock