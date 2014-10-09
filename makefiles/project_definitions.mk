TEST_SUITE_SUFFIX = _tests
PROD_LIB = $(LIB_DIR)/prod.a

DEPS_CMD = $(CC) -MM -MG $(CFLAGS)

# 'PROD_OBJ' lists object files from product sourcefiles
# Contents of this variable will be initially empty and then added to by module makefiles
PROD_OBJ  =
DEPS      =
TEST_DEPS =

MAIN_APPLICATION   = $(BIN_DIR)/HelloRaspberry
GENERAL_TARGET_DEPENDENCIES = $(BUILD_OUTPUT_DIR) $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR) $(PROD_LIB)
