USERMOD_DIR = $(HOME)/Code/micropython/usermod
USERMODULES_DIR := $(USERMOD_DIR)

# Add all C module files in the SRC_USERMOD environment variable
SRC_USERMOD += $(USERMODULES_DIR)/exmod.c

CFLAGS_USERMOD += -I$(USERMODULES_DIR)