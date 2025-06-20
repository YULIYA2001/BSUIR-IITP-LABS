.model small
.stack 100h
.data
    old_handle dd ?
    big? db 0
    exit? db 0
.code

 new_handle proc far  
    pushf
    push ds si es di dx cx bx ax

	xor ax, ax 
	in al, 60h				; Получаем скан-код символа

	cmp al, 2Ah				; Нажатие Left Shift
	je big
	cmp al, 0AAh				; Отпускание Left Shift
	je little
	cmp al, 36h				; Нажатие Right Shift
	je big
	cmp al, 0B6h				; Отпускание Right Shift
	je little
	cmp al, 3Ah				; Нажатие Caps Lock
	je big
	cmp al, 0BAh				; Отпускание Caps Lock
	je little

        cmp al, 12h 				; Сравниваем код с кодом буквы e
	mov dl, 'E'
	je new_handler
	cmp al, 15h 				; Сравниваем код с кодом буквы y
	mov dl, 'Y'
	je new_handler
	cmp al, 16h 				; Сравниваем код с кодом буквы u
	mov dl, 'U'
	je new_handler
	cmp al, 17h 				; Сравниваем код с кодом буквы i 
	mov dl, 'I'
	je new_handler
	cmp al, 18h 				; Сравниваем код с кодом буквы o
	mov dl, 'O'
	je new_handler
	cmp al, 1Eh 				; Сравниваем код с кодом буквы a
	mov dl, 'A'
	je new_handler
        cmp al, 01h				; Сравниваем код с кодом esc
        je esc_symbol
        jmp old_handler
       
	big:					; Если флаг big? = 1, то устанавливаем big? = 0 
	    cmp big?, 1				; (случай нажатия Shift при зажатом Caps Lock)
            jne big_then			; Если флаг big? = 0, то устанавливаем big? = 1
	    mov big?, 0				; (все остальные случаи: нажатие Left Shift, Right Shift или Caps Lock)
	    jmp old_handler
            big_then:
	        mov big?, 1
	        jmp old_handler

	little:					; Если флаг big? = 0, то устанавливаем big? = 1
	    cmp big?, 1				; (случай отпускания Shift при зажатом Caps Lock)
            jne little_then			; Если флаг big? = 1, то устанавливаем big? = 0
	    mov big?, 0				; (все остальные случаи: отпускание Left Shift, Right Shift или Caps Lock)
	    jmp old_handler
	    little_then:
	        mov big?, 1
	        jmp old_handler

	esc_symbol:				; Если зажат Esc (выход из программы), устанавливаем флаг exit? = 1
            mov exit?, 1
	    jmp old_handler

        new_handler: 				; Если флаг big? = 1 (буквы большие), печатаем их. Иначе "проглатываем"
	    cmp big?, 1
            jne then
	    mov ah, 02h
	    int 21h
	    then:
            jmp exit
        
        old_handler: 
            pop ax bx cx dx di es si ds
	    popf
            jmp dword ptr cs:old_handle		; Вызов стандартного обработчика прерывания
                
        exit:
            xor ax, ax
            mov al, 20h
            out 20h, al 
            pop ax bx cx dx di es si ds		; Восстановление регистров перед выходом из нашего обработчика прерываний
	    popf    
    iret
new_handle endp

main:
    mov ax, @data
    mov ds, ax

    mov ah, 02h					; Функция перерывания BIOS 
    int 16h					; возвращает значение из 0040:0017h
    shr al, 7					; где 6 бит - состояние Caps Lock
    jnc go					; если при запуске программы Caps Lock включен
    mov big?, 1					; устанавливаем флаг big? = 1
    go:

    mov ax, 3509h				; Сохранение старого обработчика
    int 21h
    mov word ptr old_handle, bx
    mov word ptr old_handle + 2, es

    push ds					; Установка нового обработчика
    mov ax, 2509h
    mov dx, seg new_handle
    mov ds, dx
    mov dx, offset new_handle
    int 21h
    pop ds
    
    cycle:					; Цикл ввода символа, пока не нажат Esc (exit? = 1)
        mov ah, 01h
	int 21h
        
	cmp   exit?, 1
	jne   cycle

    mov dl, 08					; Удаление последнего введенного символа с экрана (удаление знака esc)
    mov ah, 02h
    int 21h
    mov dl, 32
    mov ah, 02h
    int 21h
    mov dl, 08 
    mov ah, 02h
    int 21h

    push ds					; Возващение старого обработчика 9 перрывания
    mov dx, word ptr old_handle
    mov bx, word ptr old_handle+2
    mov ds, bx
    mov ax, 2509h
    int 21h  
    pop ds
    
    mov ax, 4c00h
    int 21h
end main