VPATH    += $(SRC_DIR)/vehicle
CFLAGS   += -I$(SRC_DIR)/vehicle

include $(SRC_DIR)/vehicle/sabertooth/sabertooth.mk
