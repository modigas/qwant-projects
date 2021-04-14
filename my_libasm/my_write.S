    global my_write
    section .text

my_write:
    mov rax, 1 ; syscall for write
    syscall
    ret