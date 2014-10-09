# Must be before module makefiles
ifeq ($(VARIANT), UNIT_TEST)
include $(UNITY_DIR)/unity.mk
include $(CMOCK_DIR)/cmock.mk
endif
