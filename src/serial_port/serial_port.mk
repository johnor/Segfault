VPATH    += $(SRC_DIR)/serial_port
DEPS     += $(DEPS_DIR)/serial_port.d
PROD_OBJ += $(OBJ_DIR)/serial_port.o
CFLAGS   += -I$(SRC_DIR)/serial_port

ifeq ($(VARIANT), UNIT_TEST)
VPATH += $(SRC_DIR)/serial_port/test
UNIT_TEST_BINARIES += $(BIN_DIR)/serial_port$(TEST_SUITE_SUFFIX)
endif