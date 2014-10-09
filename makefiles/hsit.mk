ifeq ($(VARIANT), HSIT_MASTER)
include $(TEST_SRC_DIR)/hsit/hsit.mk
endif

ifeq ($(VARIANT), HSIT_SLAVE)
include $(TEST_SRC_DIR)/hsit/hsit.mk
endif

ifeq ($(VARIANT), UNIT_TEST)
include $(TEST_SRC_DIR)/hsit/hsit.mk
endif
