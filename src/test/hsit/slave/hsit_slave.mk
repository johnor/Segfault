VPATH  += $(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave
CFLAGS += -I$(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave
VPATH  += $(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave/master_connection
CFLAGS += -I$(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave/master_connection
VPATH  += $(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave/run_serial_hsit_slave
CFLAGS += -I$(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave/run_serial_hsit_slave
VPATH  += $(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave/test_control
CFLAGS += -I$(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave/test_control

DEPS                   += $(DEPS_DIR)/serial_hsit_slave.d
SERIAL_HSIT_SLAVE_OBJ  = $(OBJ_DIR)/serial_hsit_slave.o
DEPS                   += $(DEPS_DIR)/run_serial_hsit_slave.d
PROD_OBJ               += $(OBJ_DIR)/run_serial_hsit_slave.o
DEPS                   += $(DEPS_DIR)/master_connection.d
PROD_OBJ               += $(OBJ_DIR)/master_connection.o
DEPS                   += $(DEPS_DIR)/test_control.d
PROD_OBJ               += $(OBJ_DIR)/test_control.o
DEPS                   += $(DEPS_DIR)/wait_for_start.d
PROD_OBJ               += $(OBJ_DIR)/wait_for_start.o
DEPS                   += $(DEPS_DIR)/log_start_command.d
PROD_OBJ               += $(OBJ_DIR)/log_start_command.o
DEPS                   += $(DEPS_DIR)/poll_master_for_start_command.d
PROD_OBJ               += $(OBJ_DIR)/poll_master_for_start_command.o
DEPS                   += $(DEPS_DIR)/hsit_performance_log.d
PROD_OBJ               += $(OBJ_DIR)/hsit_performance_log.o

ifeq ($(VARIANT), UNIT_TEST)
VPATH += $(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave/master_connection/test
UNIT_TEST_BINARIES += $(BIN_DIR)/master_connection$(TEST_SUITE_SUFFIX)
VPATH += $(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave/run_serial_hsit_slave/test
UNIT_TEST_BINARIES += $(BIN_DIR)/run_serial_hsit_slave$(TEST_SUITE_SUFFIX)
VPATH += $(TEST_SRC_DIR)/hsit/slave/serial_hsit_slave/test_control/test
UNIT_TEST_BINARIES += $(BIN_DIR)/test_control$(TEST_SUITE_SUFFIX)
UNIT_TEST_BINARIES += $(BIN_DIR)/wait_for_start$(TEST_SUITE_SUFFIX)
UNIT_TEST_BINARIES += $(BIN_DIR)/log_start_command$(TEST_SUITE_SUFFIX)
UNIT_TEST_BINARIES += $(BIN_DIR)/poll_master_for_start_command$(TEST_SUITE_SUFFIX)
UNIT_TEST_BINARIES += $(BIN_DIR)/hsit_performance_log$(TEST_SUITE_SUFFIX)
endif

ifeq ($(VARIANT), HSIT_SLAVE)
HSIT_SLAVE_BINARIES += $(BIN_DIR)/serial_hsit_slave

$(BIN_DIR)/serial_hsit_slave : $(BIN_DIR) $(PROD_LIB) $(SERIAL_HSIT_SLAVE_OBJ)
	@echo 'Linking $@'
	$(CC) -o $@ $(SERIAL_HSIT_SLAVE_OBJ) $(PROD_LIB)
	@echo ' '
endif
