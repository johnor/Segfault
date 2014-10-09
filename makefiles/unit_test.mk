ifeq ($(VARIANT), UNIT_TEST)
# Build test deps list after modules have been included
TEST_DEPS += $(UNIT_TEST_BINARIES:$(BIN_DIR)/%$(TEST_SUITE_SUFFIX)=$(DEPS_DIR)/%$(TEST_SUITE_SUFFIX).d)
TEST_DEPS += $(UNIT_TEST_BINARIES:$(BIN_DIR)/%$(TEST_SUITE_SUFFIX)=$(DEPS_DIR)/%$(TEST_SUITE_SUFFIX).testdep)
endif
