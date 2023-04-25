############################################################
#
#
# Obs: var DEFS can include compilation flags, e.g.: -DPROD
# Obs: for running custom window, format is: "Testing" 1280 720
#
#
############################################################

OUT_DIR := ./bin
SRC_DIR := ./src
INC_DIR := ./inc

CC := gcc
CUSTOM_CFLAGS := -Wall -Werror
CUSTOM_LDFLAGS := -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl
SOURCES += $(wildcard $(SRC_DIR)/*.c)
INCLUDES += -I$(INC_DIR)
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
