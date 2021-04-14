    global my_memmove
    section .text

my_memmove:
    cmp rdx, 0
    je exit1
    sub rdx, 1
    mov rcx, 0
    jmp allocate_stack_mem

allocate_stack_mem:
    add rdx, 1
    sub rsp, rdx
    sub rdx, 1
    mov r8, rsp
    jmp copy_src

copy_src:
    mov r9b, BYTE[rsi + rcx]
    mov BYTE[r8 + rcx], r9b
    cmp rdx, rcx
    je zero_rcx
    inc rcx
    jmp copy_src

zero_rcx:
    mov rcx, 0
    jmp copy_to_dest

copy_to_dest:
    mov r9b, BYTE[r8 + rcx]
    mov BYTE[rdi + rcx], r9b
    cmp rdx, rcx
    je exit
    inc rcx
    jmp copy_to_dest

exit:
    add rdx, 1
    add rsp, rdx
    sub rdx, 1
    ret

exit1:
    ret