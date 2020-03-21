.SECONDARY:

TOOLCHAIN := arm-none-eabi-
CC := $(TOOLCHAIN)gcc
LD := $(TOOLCHAIN)ld
OBJDMP := $(TOOLCHAIN)objdump
OBJCPY := $(TOOLCHAIN)objcopy
SRC_DIR := src
BUILD_DIR := build

.PHONY: all
all: nrf52840-starter

.PHONY: nrf52840-starter
nrf52840-starter: $(BUILD_DIR)/nrf52840-starter.bin $(BUILD_DIR)/nrf52840-starter.dump.txt

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: flash
flash: nrf52840-starter-flash

.PHONY: debug
debug: nrf52840-starter-debug

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

include mk/nrfx.mk
include mk/cmsis.mk

INCLUDES += -Iinclude $(NRFX_INC) $(CMSIS_INC)

LDFLAGS += -Wl,-Map=$(BUILD_DIR)/output.map \
		   -Wl,--gc-sections \
		   -Wl,--print-memory-usage \
		   -T link/link.ld

CFLAGS += -mcpu=cortex-m4 \
	  -mthumb \
	  -ffunction-sections \
	  -fdata-sections \
	  -ffreestanding \
	  $(INCLUDES) \
	  -g \
	  -Wall \
	  -Werror

SRC := $(wildcard $(SRC_DIR)/*) $(NRFX_SRCS)
OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC))

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCPY) $< $@ -O binary

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.dump.txt: $(BUILD_DIR)/%.elf
	$(OBJDMP) -D $^ > $@

%-flash: $(BUILD_DIR)/%.elf
	gdb-multiarch -nx --batch \
	-ex 'target extended-remote /dev/ttyACM0' \
	-x flash.scr \
	$(BUILD_DIR)/$(*).elf

%-debug: $(BUILD_DIR)/%.elf
	gdb-multiarch -nx --batch \
	-ex 'target extended-remote /dev/ttyACM0' \
	-x debug.scr \
	$(BUILD_DIR)/$(*).elf