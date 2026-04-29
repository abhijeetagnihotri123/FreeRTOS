MEMORY
{
    FLASH : ORIGIN = 0x0, LENGTH = 128K /*Read only memory*/
    RAM : ORIGIN = 0x20000000, LENGTH = 8K /*Read write memory*/
}

SECTIONS
{
    .text : {
        _stext = .;
        *(.vectors*)
        *(.text*)
        *(.rodata)
        *(.rodata.*)
        _etext = .; /* Size to be determined via current location pointer */
    } > FLASH

    .data : ALIGN(4) {
        _sdata = .;
        _sidata = LOADADDR(.data);
        *(.data*)
        . = ALIGN(4);
        _edata = .; /* Size to be determined via current location pointer */
    } > FLASH AT > RAM

    .bss : ALIGN(4) {
        _sbss = .;
        *(.bss*)
        . = ALIGN(4);
        _ebss = .; /* Size to be determined via current location pointer */
    } > RAM

    __StackTop = ORIGIN(RAM) + LENGTH(RAM);
    PROVIDE(__stack = __StackTop - 4);

}
