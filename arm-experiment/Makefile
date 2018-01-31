SRC = $(wildcard *.c)
ELF = testApp.elf
BIN = testApp.bin

# using Ubuntu 16 supplied gcc 
CORTEX_M3_CC = arm-none-eabi-gcc-4.9.3 --specs=nosys.specs -mcpu=cortex-m3 -march=armv7-m -mtune=cortex-m3 -gdwarf-2 -mlittle-endian -mthumb
CORTEX_M3_LINK = $(CORTEX_M3_CC)
# CORTEX_M3_LDFLAGS = -T ./arm.ld  --verbose
CORTEX_M3_LDFLAGS = 
CORTEX_M3_OBJCOPY = arm-none-eabi-objcopy

all: $(BIN)

%.bin: %.elf
	$(CORTEX_M3_OBJCOPY) -O binary $^ $@

%.elf:  %.o
	$(CORTEX_M3_LINK) -o $@ $^ $(CORTEX_M3_LDFLAGS) -lm

%.o: %.c
	$(CORTEX_M3_CC) -c -o $@ $< -O0 -g 

.PRECIOUS: %.elf

clean::
	- rm -f $(ELF) $(BIN)
