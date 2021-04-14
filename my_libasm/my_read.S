    section .text:
    global my_read

my_read:
    mov rax, 0  ; read sycall = 0
    syscall
    ret