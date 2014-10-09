VPATH    += $(SRC_DIR)/vehicle/sabertooth
VPATH    += $(SRC_DIR)/vehicle/sabertooth/test
DEPS     += $(DEPS_DIR)/sabertooth_vehicle_control.d $(DEPS_DIR)/sabertooth_simplified_communication.d
PROD_OBJ += $(OBJ_DIR)/sabertooth_vehicle_control.o $(OBJ_DIR)/sabertooth_simplified_communication.o
CFLAGS   += -I$(SRC_DIR)/vehicle/sabertooth

UNIT_TEST_BINARIES += $(BIN_DIR)/sabertooth_vehicle_control$(TEST_SUITE_SUFFIX) \
                      $(BIN_DIR)/sabertooth_simplified_communication$(TEST_SUITE_SUFFIX)
