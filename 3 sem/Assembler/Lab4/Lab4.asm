model small
.stack 100h
.data
    
    errormes db 10, 13, 'Wrong input, try again', 10, 13, '$'
    ;inputmes db 'Enter a string (Latin alphabet, no more than 100 characters):', 10, 13, '$'
    ;endmes db 10, 13, 10, 13, 'press any key to continue $'
    s db 101 dup ('$')
    len db 0
    max1 dw ?
    ;resmes db 10, 13, 'Sorted string:', 10, 13, '$'

.code
.386			; не допрыгивает jmp


;          ---- ВВОД СТРОКИ С ПРОВЕРКОЙ ----
input proc

    push ax
    push bx
    push cx
    push dx

     begin:
        ;lea dx, inputmes		; ввод строки пользователем	
        ;mov ah, 09h
        ;int 21h
        xor cx, cx
        lea si, s
        
    right_input:			;проверка на латинские буквы и \r, \n			
        cmp cx, 100
        je end_right_input
        mov ah, 01h
        int 21h
        cmp al, 13
	je end_right_input 
        cmp al, 10
	je end_right_input  
	cmp al, 'A'
        jb wronginput
	cmp al, 'z'
	ja wronginput
	cmp al, 'Z'
        jna right
	cmp al, 'a'
        jnb right
	jmp wronginput

        right:
	    mov [si], al
	    inc si
	    inc cx
	    jmp right_input

    wronginput:				;сообщение о неправильном вводе
	lea dx, errormes
	mov ah, 09h
	int 21h
	jmp begin

    end_right_input:
	cmp cx, 0
        je wronginput
        mov len, cl

    pop dx
    pop cx
    pop bx
    pop ax
    
    ret
input endp

BubbleSort proc
    
    push ax
    push bx
    push cx
    push dx
    push si  
        
    xor ax, ax
    mov al, len
    dec ax             
    mov max1, ax			; max1 = len - 1   

    xor bx, bx				; i = 0
    xor cx, cx 
    
    cycle1:
        cmp bx, max1            	; i < len - 1
 	jnb cycle1_end		
        mov ax, max1			; j = len - 1
        lea si, s
        add si, ax			; указываем на конец строки si - [j]
    
        cycle2:       
            cmp ax, bx			; j > i
	    jna cycle2_end            
            mov dl, [si]
            push dx
            cmp dl, 91
            jnb next1	
            add dl, 32			; dl tolower
            next1:			
            mov cl, [si-1]
            push cx
            cmp cl, 91
            jnb next2
	    add cl, 32			; cl tolower
            next2:	
            cmp cl, dl			; s[j-1] > s[j]
            jna continue
            pop cx
	    pop dx
            mov [si], cl		; swap
            mov [si-1], dl
            jmp next

            continue:
                jne go
                pop cx			; если при tolower буквы равны
		pop dx
                cmp cl, dl			; s[j-1] > s[j]
                jna next
                mov [si], cl		; swap
                mov [si-1], dl
                jmp next
		
	    go:
                pop cx
                pop dx
            next:
	        dec ax			; j--
                dec si		
                jmp cycle2                

        cycle2_end:
	    inc bx			; i++
            jmp cycle1

    cycle1_end:
    
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret
BubbleSort endp

start:
    mov ax, @data
    mov ds, ax

    call input				; ввод строки пользователем

    call BubbleSort

    ;lea dx, resmes			; сортировка строки	
    ;mov ah, 09h
    ;int 21h
    lea dx, s				; вывод отсортированной строки
    mov ah, 09h
    int 21h

    ;lea dx, endmes			; ожидание ввода символа
    ;mov ah, 09h
    ;int 21h
    ;mov ah, 01h			
    ;int 21h

    mov ax, 4C00h
    int 21h
end start