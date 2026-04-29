PROJECT=main
CPU ?= cortex-m3
BOARD ?= stm32vldiscovery

FREERTOS_PATH = ../FreeRTOS-Kernel

INC = -I$(FREERTOS_PATH)/include \
	  -I$(FREERTOS_PATH)/portable/GCC/ARM_CM3 \
	  -I./ \

SRC = boot.S

C_FILES = start.c

OBJ = boot.o \
	  start.o \
	  portFunctions.o \
	  $(FREERTOS_PATH)/tasks.o \
	  $(FREERTOS_PATH)/list.o \
	  $(FREERTOS_PATH)/portable/GCC/ARM_CM3/port.o \
	  $(FREERTOS_PATH)/portable/MemMang/heap_4.o

%.o: %.S
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -g -c $^ -o $@

%.o: %.c
	arm-none-eabi-gcc $(INC) -mthumb -mcpu=$(CPU) -g -c $^ -o $@

buildFirmware: $(OBJ)
	arm-none-eabi-ld -Tmap.ld $(OBJ) -o $(PROJECT).elf

dumpFirmware:
	arm-none-eabi-objdump -D -S $(PROJECT).elf > $(PROJECT).elf.lst
	arm-none-eabi-readelf -a $(PROJECT).elf > $(PROJECT).elf.debug

qemu:
	qemu-system-arm -S -M $(BOARD) -cpu $(CPU) -nographic -kernel $(PROJECT).elf -gdb tcp::1234

gdb:
	gdb-multiarch -q $(PROJECT).elf -ex "target remote localhost:1234"

clean:
	rm -rf *.out *.elf .gdb_history *.lst *.debug *.o