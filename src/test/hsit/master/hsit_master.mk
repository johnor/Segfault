VPATH  += $(TEST_SRC_DIR)/hsit/master/serial_hsit_master
CFLAGS += -I$(TEST_SRC_DIR)/hsit/master/serial_hsit_master
VPATH  += $(TEST_SRC_DIR)/hsit/master/serial_hsit_master/run_serial_hsit_master
CFLAGS += -I$(TEST_SRC_DIR)/hsit/master/serial_hsit_master/run_serial_hsit_master
VPATH  += $(TEST_SRC_DIR)/hsit/master/serial_hsit_master/slave_connection
CFLAGS += -I$(TEST_SRC_DIR)/hsit/master/serial_hsit_master/slave_connection
VPATH  += $(TEST_SRC_DIR)/hsit/master/serial_hsit_master/test_control_master
CFLAGS += -I$(TEST_SRC_DIR)/hsit/master/serial_hsit_master/test_control_master


DEPS                   += $(DEPS_DIR)/serial_hsit_master.d
SERIAL_HSIT_MASTER_OBJ  = $(OBJ_DIR)/serial_hsit_master.o
DEPS                   += $(DEPS_DIR)/run_serial_hsit_master.d
PROD_OBJ               += $(OBJ_DIR)/run_serial_hsit_master.o
DEPS                   += $(DEPS_DIR)/slave_connection.d
PROD_OBJ               += $(OBJ_DIR)/slave_connection.o
DEPS                   += $(DEPS_DIR)/send_start_command.d
PROD_OBJ               += $(OBJ_DIR)/send_start_command.o


ifeq ($(VARIANT), UNIT_TEST)
VPATH += $(TEST_SRC_DIR)/hsit/master/serial_hsit_master/test
UNIT_TEST_BINARIES += $(BIN_DIR)/serial_hsit_master$(TEST_SUITE_SUFFIX)
VPATH += $(TEST_SRC_DIR)/hsit/master/serial_hsit_master/run_serial_hsit_master/test
UNIT_TEST_BINARIES += $(BIN_DIR)/run_serial_hsit_master$(TEST_SUITE_SUFFIX)
VPATH += $(TEST_SRC_DIR)/hsit/master/serial_hsit_master/slave_connection/test
UNIT_TEST_BINARIES += $(BIN_DIR)/slave_connection$(TEST_SUITE_SUFFIX)
VPATH += $(TEST_SRC_DIR)/hsit/master/serial_hsit_master/test_control_master/test
UNIT_TEST_BINARIES += $(BIN_DIR)/send_start_command$(TEST_SUITE_SUFFIX)
endif

ifeq ($(VARIANT), HSIT_MASTER)
HSIT_MASTER_BINARIES += $(BIN_DIR)/serial_hsit_master

$(BIN_DIR)/serial_hsit_master : $(BIN_DIR) $(PROD_LIB) $(SERIAL_HSIT_MASTER_OBJ)
	@echo 'Linking $@'
	$(CC) -o $@ $(SERIAL_HSIT_MASTER_OBJ) $(PROD_LIB)
	@echo ' '
endif
