####################################################################################
#
#
# Obs: var DEFS can include compilation flags, e.g.: -DPROD -DTIME_UPD
# Obs: for running custom window, format is: "Testing" 1280 720
#
#
####################################################################################

OUT_DIR  := ./bin
SRC_DIR  := ./src
INC_DIR  := ./inc

SYST_INC := $(INC_DIR)/systems
SYST_SRC := $(SRC_DIR)/systems

PLTF_INC := $(INC_DIR)/platform
PLTF_SRC := $(SRC_DIR)/platform

UTIL_INC := $(INC_DIR)/utils
UTIL_SRC := $(SRC_DIR)/utils

CC := gcc
CUSTOM_CFLAGS := -Wall -Werror
CUSTOM_LDFLAGS := -lglfw -lGL -lrt -ldl -lm
SOURCES += $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SYST_SRC)/*.c) $(wildcard $(PLTF_SRC)/*.c) $(wildcard $(UTIL_SRC)/*.c)
INCLUDES += -I$(INC_DIR) -I$(SYST_INC) -I$(PLTF_INC) -I$(UTIL_INC)
OBJECTS := $(patsubst %.c,%.o, $(SOURCES))
BINARY := $(OUT_DIR)/practice
DEFS :=

all: $(BINARY)
$(BINARY): $(SOURCES)
	$(CC) $(DEFS) $(SOURCES) $(CUSTOM_CFLAGS) $(CUSTOM_LDFLAGS) $(INCLUDES) -o $(BINARY)

haste:
	@$(BINARY) "Testing" 1280 720

clean:
	rm -rf $(OUT_DIR)/*.o
	rm -rf $(BINARY)
	rm -rf $(OUT_DIR)
	mkdir $(OUT_DIR)
