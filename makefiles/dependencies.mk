# Include dependency files, if they exist, unless we're cleaning
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
# Add unit test dependencies
ifeq ($(VARIANT), UNIT_TEST)
-include $(TEST_DEPS)
endif
endif
