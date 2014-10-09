VPATH  += $(TEST_SRC_DIR)/hsit
CFLAGS += -I$(TEST_SRC_DIR)/hsit
VPATH  += $(TEST_SRC_DIR)/hsit/initiate_hsit_log
CFLAGS += -I$(TEST_SRC_DIR)/hsit/initiate_hsit_log
VPATH  += $(TEST_SRC_DIR)/hsit/terminate_hsit_log
CFLAGS += -I$(TEST_SRC_DIR)/hsit/terminate_hsit_log

DEPS     += $(DEPS_DIR)/initiate_hsit_log.d
PROD_OBJ += $(OBJ_DIR)/initiate_hsit_log.o
DEPS     += $(DEPS_DIR)/terminate_hsit_log.d
PROD_OBJ += $(OBJ_DIR)/terminate_hsit_log.o

ifeq ($(VARIANT), HSIT_MASTER)
include $(TEST_SRC_DIR)/hsit/master/hsit_master.mk
endif

ifeq ($(VARIANT), HSIT_SLAVE)
include $(TEST_SRC_DIR)/hsit/slave/hsit_slave.mk
endif

ifeq ($(VARIANT), UNIT_TEST)
include $(TEST_SRC_DIR)/hsit/master/hsit_master.mk
include $(TEST_SRC_DIR)/hsit/slave/hsit_slave.mk
VPATH += $(TEST_SRC_DIR)/hsit/initiate_hsit_log/test
UNIT_TEST_BINARIES += $(BIN_DIR)/initiate_hsit_log$(TEST_SUITE_SUFFIX)
VPATH += $(TEST_SRC_DIR)/hsit/terminate_hsit_log/test
UNIT_TEST_BINARIES += $(BIN_DIR)/terminate_hsit_log$(TEST_SUITE_SUFFIX)
endif
