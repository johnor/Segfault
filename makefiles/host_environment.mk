# Select cross compiler executable based on host system
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  # Linux environment
  BCM_CROSS_COMPILER = arm-bcm2708hardfp-linux-gnueabi-gcc
endif
ifeq ($(UNAME), MINGW32_NT-6.1)
  # Windows with MinGW environment
  BCM_CROSS_COMPILER = arm-linux-gnueabihf-gcc
endif
ifeq ($(UNAME), Darwin)
  # Mac
  # Don't link libm
  CFLAGS =
  BCM_CROSS_COMPILER = arm-none-linux-gnueabi-gcc
  AR = arm-none-linux-gnueabi-ar
endif

HOST_CC = gcc
HOST_AR = ar