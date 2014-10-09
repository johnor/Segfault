VPATH    += $(SRC_DIR)/system/system_i2c
DEPS     += $(DEPS_DIR)/system_i2c.d
PROD_OBJ += $(OBJ_DIR)/system_i2c.o
CFLAGS   += -I$(SRC_DIR)/system/system_i2c -Ilib/wiringPi
LDLIBS   += -Llib/wiringPi -lwiringPi