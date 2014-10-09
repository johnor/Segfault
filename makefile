# The order of inclusion of makefiles is important because definitions made in one file
# are likely to be used by its successors
include makefiles/directory_definitions.mk
include makefiles/shell_command_definitions.mk
include makefiles/host_environment.mk
include makefiles/variant_settings.mk
include makefiles/project_definitions.mk

# For Unity and CMock
include makefiles/unity_makefiles.mk

# Project Modules
include makefiles/modules.mk

# Hardware-Software Integration Tests
include makefiles/hsit.mk

# Unit tests - Must succeed anything that is unit tested
include makefiles/unit_test.mk

include makefiles/dependencies.mk

.PHONY : all clean
all : $(VARIANT)
	@echo Done building variant $(VARIANT)
	@echo ' '

clean :
	@echo Cleaning everything
	$(RM) $(BUILD_DIR)
	@echo ' '

$(OBJ_DIR)/%.o : %.c
	@echo 'Compiling "$<" because of "$?"'
	$(CC) $(CFLAGS) -c $< -o $@
	@echo ' '

$(DEPS_DIR)/%.d : %.c
	@echo 'Generating deps for "$<" because of "$?"'
	@set -e; rm -f $@; \
	$(MKDIR) $(DEPS_DIR); \
	$(DEPS_CMD) $< > $@.tmp; \
	sed 's,\($*\)\.o[ :]*,$(OBJ_DIR)/\1.o $@ : ,g' < $@.tmp > $@; \
	rm -f $@.tmp
	@echo ' '

$(MAIN_APPLICATION) : $(MAIN_OBJ) $(PROD_LIB) | $(BIN_DIR)
	@echo 'Linking $@'
	$(CC) -o $@ $^ $(LDLIBS)
	@echo ' '

$(PROD_LIB) : $(PROD_OBJ)
	@echo 'Archiving product object files into "$@"'
	$(AR) $(ARFLAGS) $@ $(PROD_OBJ)
	@echo ' '

.PRECIOUS: $(AUTO_SRC_DIR)/%_test_runner.c
$(AUTO_SRC_DIR)/%_test_runner.c : %$(TEST_SUITE_SUFFIX).c
	@echo Generating test runner $@ because of $?
	$(GEN_TEST_RUNNER) $< $@
	@echo ' '

# Rule to add mock object prerequisites to _test binary rules.
$(DEPS_DIR)/%$(TEST_SUITE_SUFFIX).testdep: %$(TEST_SUITE_SUFFIX).c | $(DEPS_DIR)
# mock_obs contain a list of mock objects extracted from the names of mock headers in the _tests.d file.
	@echo 'Generating test binary deps for "$<" because of "$?"'
	@set -e; \
		mock_objs="$$($(DEPS_CMD) $< | $(GREP) -ow '[^ ]*mock_[^ ]*\.h' | $(SED) 's/\.h$$/.o/' \
		              | $(SED) 's,^.*mock_,$(MOCK_DIR)/mock_,' | $(TR) '\r\n' ' ')"; \
		echo "$(BIN_DIR)/$*$(TEST_SUITE_SUFFIX) $@: $$mock_objs" > $@;
	@echo

$(BIN_DIR)/%$(TEST_SUITE_SUFFIX): $(PROD_LIB) $(UNITY_OBJ) $(CMOCK_OBJ) $(OBJ_DIR)/%_test_runner.o $(OBJ_DIR)/%$(TEST_SUITE_SUFFIX).o
	@echo "Linking tester $@"
# We need the symbols used by tests to appear after the tests to be able to link
# Right now doing this in the hackish way by assuring that prod_lib.a is the last item
	$(CC) $(filter-out %.a,$^) $(filter %.a,$^) -o $@ $(CFLAGS)
	@echo

$(OBJ_DIR) $(DEPS_DIR) $(LIB_DIR) $(BIN_DIR) $(BUILD_OUTPUT_DIR) $(MOCK_DIR) :
	@$(MKDIR) $@
	@echo ' '

include makefiles/variant_targets.mk
