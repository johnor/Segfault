VPATH    += $(SRC_DIR)/log
VPATH    += $(SRC_DIR)/log/test
DEPS     += $(DEPS_DIR)/log.d
PROD_OBJ += $(OBJ_DIR)/log.o
CFLAGS   += -I$(SRC_DIR)/log

UNIT_TEST_BINARIES += $(BIN_DIR)/log$(TEST_SUITE_SUFFIX)
