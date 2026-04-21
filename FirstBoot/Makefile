PROJECT=main
CPU ?= cortex-m3
BOARD ?= stm32vldiscovery

SRC = boot.S

OBJ = boot.o

%.o: %.S
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -g -c $^ -o $@

%.o: %.c
	arm-none-eabi-as -mthumb -mcpu=$(CPU) -g -c

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