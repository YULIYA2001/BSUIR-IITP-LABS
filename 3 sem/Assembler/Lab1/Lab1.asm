.model small
.stack 100h
.data
    a dw 1    ;declare word
    b dw 2
    c dw 3
    d dw 4
.code

main:
    mov ax,@data
    mov ds,ax

    mov ax, a
    add ax, b
    jc else1

    mov bx, c
    or bx, d

    cmp ax, bx
    jz equal
    jmp else1

    equal:
    mov bx, c
    xor bx, d 
    and ax, bx
    jmp lab_end

    else1:
    mov ax, b
    xor ax, c 

    mov bx, a
    or bx, d 
  
    cmp ax, bx
    jz equal2
    jmp else2

    equal2:
    and ax, bx
    jmp lab_end

    else2:
    mov ax, a
    xor ax, b

    mov bx, c
    xor bx, d

    or ax, bx

    lab_end:
    mov ax, 4C00h
    int 21h
end main
