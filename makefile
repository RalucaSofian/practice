##############################
#
#
#
##############################

OUT_DIR := ./bin
SRC_DIR := ./src
INC_DIR := ./inc

CC := gcc
#PACKAGES :=
CUSTOM_CFLAGS := -Wall -Werror
#CUSTOM_LDFLAGS :=
SOURCES += $(wildcard $(SRC_DIR)/*.c)
INCLUDES += -I$(INC_DIR)
OBJECTS := $(patsubst %.c,%.o, $(SOURCES))
BINARY := $(OUT_DIR)/practice

all: $(BINARY)
$(BINARY): $(SOURCES)
	$(CC) $(SOURCES) $(CUSTOM_CFLAGS) $(INCLUDES) -o $(BINARY)

run:
	@$(BINARY)

clean:
	rm -rf $(OUT_DIR)/*.o
	rm -rf $(BINARY)
