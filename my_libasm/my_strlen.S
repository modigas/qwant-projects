    global my_strlen
    
    section .text
my_strlen:
    mov rax, 0
    jmp loop

loop:
    cmp BYTE[rdi + rax], 0
    je exit
    inc rax
    jne loop

exit:
    ret