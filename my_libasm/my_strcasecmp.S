    global my_strcasecmp
    section .text

my_strcasecmp:
    mov rcx, 0
    jmp get_value

get_value:
    mov r8b, BYTE[rsi + rcx]
    mov r9b, BYTE[rdi + rcx]
    jmp loop1

loop1:
    cmp r8b, 0
    je end
    cmp r9b, 0
    je end
    jmp loop2

loop2:
    push rdi
    mov dil, r8b
    call is_letter1
    mov r8b, dil
    mov dil, r9b
    call is_letter1
    mov r9b, dil
    pop rdi
    jmp loop3

loop3:
    inc rcx
    cmp r8b, r9b
    je get_value
    jmp end

is_letter1:
    cmp dil, 'A'
    jge is_letter2
    ret

is_letter2:
    cmp dil, 'Z'
    jle is_letter3
    ret

is_letter3:
    add dil, 32
    ret

end:
    sub r9b, r8b
    movsx eax, r9b
    ret