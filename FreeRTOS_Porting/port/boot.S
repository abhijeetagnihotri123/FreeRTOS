.section .vectors
vector_table:
    .word __stack
    .word reset_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word default_handler
    .word xPortSysTickHandler
    .zero 400

    .section .text
    .align 1
    .type reset_handler, %function
reset_handler:
    bl start
    b .

    .section .text
    .align 1
    .type default_handler, %function
default_handler:
    b .