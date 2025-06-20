;--------------------- ПЕРЕОПРЕДЕЛЕНИЕ ОБРАБОТЧИКА ПРЕРЫВАНИЯ КЛАВИАТУРЫ (INT 9) ------------------------------
;----------------------- ТАК, ЧТОБЫ НЕ ВВОДИЛИСЬ МАЛЫЕ ЛАТИНСКИЕ ГЛАСНЫЕ БУКВЫ --------------------------------
;------------------------- ПРИ ВВОДЕ "I" ПРИ ЗАПУСКЕ ПРОГЛАТЫВАТЬ МАЛЫЕ БУКВЫ ---------------------------------
;------------------------ ПРИ ВВОДЕ "u" ПРИ ЗАПУСКЕ ПРОГЛАТЫВАТЬ БОЛЬШИЕ БУКВЫ --------------------------------
;-------------------------- ПРИ ВВОДЕ "o" ПРИ ЗАПУСКЕ ПРОГЛАТЫВАТЬ НЕ БУКВЫ -----------------------------------
;----------------------- ПРИ ВВОДЕ "v" ПРИ ЗАПУСКЕ ПРОГЛАТЫВАТЬ ГЛАСНЫЕ БУКВЫ ---------------------------------
;---------------------- ПРИ ВВОДЕ "c" ПРИ ЗАПУСКЕ ПРОГЛАТЫВАТЬ СОГЛАСНЫЕ БУКВЫ --------------------------------

.model small
.stack 100h
.data
    old_handle dd ?
    big? db 0
    exit? db 0
    first db 0					; Для того, чтобы когда при запуске вводим параметр (shift+буква) 
    						; новый обработчик, улавливая отпускание shift ничего не портил 
    flagI db 0
    flagu db 0
    flago db 0
    flagv db 0
    flagc db 0
    choose_mes  db 'Do you want to enter a startup parameter?', 10, 13, '0 - yes, other keys - no: ', 10, 13, '$'
    param_mes db 'Enter "I" to miss small letters', 10, 13, 'Enter "u" to miss big letters', 10, 13, 'Enter "o" to miss not letters', 10, 13, 'Enter "v" to miss vowels', 10, 13, 'Enter "c" to miss consonants', 10, 13,'$'
    error_mes db 10, 13, 'Wrong input, try again', 10, 13, '$'
    enter_mes db 10, 13, '$'
.code
.386

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
	cmp al, 01h				; Сравниваем код с кодом esc
        je esc_symbol
	cmp flagc, 1				; Если установлен флаг "c" (глотать согласные буквы), идем на обработку согласных
	je S

	;-------------------------  Гласные ----------------------------------
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
	cmp flagI, 1				; Если установлен флаг "I" (глотать малые буквы), идем на обработку согласных
	je S
	cmp flagu, 1				; Если установлен флаг "u" (глотать большие буквы), идем на обработку согласных
	je S
	cmp flago, 1				; Если установлен флаг "o" (глотать не буквы), идем на обработку согласных
	je S
        jmp old_handler

	S:
	;------------------------- Согласные ----------------------------------
        cmp al, 10h 				; Сравниваем код с кодом буквы q
	mov dl, 'Q'
	je new_handler
	cmp al, 11h 				; Сравниваем код с кодом буквы w
	mov dl, 'W'
	je new_handler
	cmp al, 13h 				; Сравниваем код с кодом буквы r
	mov dl, 'R'
	je new_handler
	cmp al, 14h 				; Сравниваем код с кодом буквы t 
	mov dl, 'T'
	je new_handler
	cmp al, 19h 				; Сравниваем код с кодом буквы p
	mov dl, 'P'
	je new_handler
	cmp al, 1Fh 				; Сравниваем код с кодом буквы s
	mov dl, 'S'
	je new_handler
	cmp al, 20h 				; Сравниваем код с кодом буквы d
	mov dl, 'D'
	je new_handler
	cmp al, 21h 				; Сравниваем код с кодом буквы f
	mov dl, 'F'
	je new_handler
	cmp al, 22h 				; Сравниваем код с кодом буквы g
	mov dl, 'G'
	je new_handler
	cmp al, 23h 				; Сравниваем код с кодом буквы h 
	mov dl, 'H'
	je new_handler
	cmp al, 24h 				; Сравниваем код с кодом буквы j
	mov dl, 'J'
	je new_handler
	cmp al, 25h 				; Сравниваем код с кодом буквы k
	mov dl, 'K'
	je new_handler
	cmp al, 26h 				; Сравниваем код с кодом буквы l
	mov dl, 'L'
	je new_handler
	cmp al, 2Ch 				; Сравниваем код с кодом буквы z
	mov dl, 'Z'
	je new_handler
	cmp al, 2Dh 				; Сравниваем код с кодом буквы x
	mov dl, 'X'
	je new_handler
	cmp al, 2Eh 				; Сравниваем код с кодом буквы c 
	mov dl, 'C'
	je new_handler
	cmp al, 2Fh 				; Сравниваем код с кодом буквы v
	mov dl, 'V'
	je new_handler
	cmp al, 30h 				; Сравниваем код с кодом буквы b
	mov dl, 'B'
	je new_handler
	cmp al, 31h 				; Сравниваем код с кодом буквы n
	mov dl, 'N'
	je new_handler
	cmp al, 32h 				; Сравниваем код с кодом буквы m
	mov dl, 'M'
	je new_handler
	cmp flago, 1				; Если установлен флаг "o" глотаем не буквы (выход, если не нашли код буквы)
	je exit
	jmp old_handler
       
	big:					; Если флаг big? = 1, то устанавливаем big? = 0
	    cmp big?, 1				; (случай нажатия Shift при зажатом Caps Lock)
            jne big_then			; Если флаг big? = 0, то устанавливаем big? = 1
	    mov big?, 0				; (все остальные случаи: нажатие Left Shift, Right Shift или Caps Lock)
	    jmp old_handler
            big_then:
	        mov big?, 1
	        jmp old_handler

	little:					
	    cmp first, 1			; Проверить: shift "словился" при вводе параметра запуска или его намеренно нажали
            je first_letter			; Если флаг big? = 0, то устанавливаем big? = 1
	    cmp big?, 1				; (случай отпускания Shift при зажатом Caps Lock)
            jne little_then			; Если флаг big? = 1, то устанавливаем big? = 0
	    mov big?, 0				; (все остальные случаи: отпускание Left Shift, Right Shift или Caps Lock)
	    jmp old_handler
	    little_then:
	        mov big?, 1
	        jmp old_handler
	    first_letter:			; Если shift "словился" при вводе параметра запуска, пропускаем его и сбрасываем флаг
	        mov first, 0
	        jmp old_handler

	esc_symbol:				; Если зажат Esc (выход из программы), устанавливаем флаг exit? = 1
            mov exit?, 1
	    jmp old_handler

        new_handler: 
	    cmp flagc, 1			; Если параметр - "c" (глотать согласные буквы)
	    je then
	    cmp flagv, 1			; Если параметр - "v" (глотать гласные буквы)
	    je then
	    cmp flago, 1			; Если параметр - "o" (глотать не буквы)
	    jne miss1
	    cmp big?, 1				; 	если флаг big? = 1, то печатаем большую букву
	    je print
	    add dl, 20h				; 	если флаг big? = 0, то печатаем малую букву
	    print:
	        mov ah, 02h
	        int 21h
		jmp then
	    miss1:		
	        cmp flagu, 1			; Если параметр - "u" (глотать большие буквы)
                jne miss2
	        cmp big?, 1			; 	если флаг big? = 1, то переход в конец (глотать)
                je then
	        add dl, 20h			; 	иначе выводить на экран (малые буквы)
	        mov ah, 02h
	        int 21h
                jmp then
	    miss2:
	        cmp big?, 1			; Иначе - глотать малые, выводить большие
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

    lea dx, choose_mes
    mov ah, 09h
    int 21h
    mov ah, 01h
    int 21h
    cmp al, '0'
    lea dx, enter_mes
    mov ah, 09h
    int 21h
    jne start

    again:
	lea dx, param_mes
	mov ah, 09h
	int 21h
	mov ah, 01h
	int 21h
	cmp al, 'I'
	je find_I
        cmp al, 'u'
        je find_u
	cmp al, 'o'
	je find_o
	cmp al, 'v'
	je find_v
	cmp al, 'c'
	je find_c
        jmp error
        find_I:
            lea dx, enter_mes
	    mov ah, 09h
	    int 21h
	    mov flagI, 1
	    cmp big?, 1				; Если caps lock при запуске был включен, то shift
            je start				; не нажимали, иначе пометить, что был нажат shift
	    mov first, 1
            jmp start
	find_u:
	    lea dx, enter_mes
	    mov ah, 09h
	    int 21h
	    mov flagu, 1
	    cmp big?, 0				; Если caps lock при запуске не был включен, то shift
            je start				; не нажимали, иначе пометить, что был нажат shift
	    mov first, 1
            jmp start
	find_o:
	    lea dx, enter_mes
	    mov ah, 09h
	    int 21h
	    mov flago, 1
	    cmp big?, 0				; Если caps lock при запуске не был включен, то shift
            je start				; не нажимали, иначе пометить, что был нажат shift
	    mov first, 1
            jmp start
	find_v:
	    lea dx, enter_mes
	    mov ah, 09h
	    int 21h
	    mov flagv, 1
	    cmp big?, 0				; Если caps lock при запуске не был включен, то shift
            je start				; не нажимали, иначе пометить, что был нажат shift
	    mov first, 1
            jmp start
	find_c:
	    lea dx, enter_mes
	    mov ah, 09h
	    int 21h
	    mov flagc, 1
	    cmp big?, 0				; Если caps lock при запуске не был включен, то shift
            je start				; не нажимали, иначе пометить, что был нажат shift
	    mov first, 1
            jmp start

    error:
	lea dx, error_mes
        mov ah, 09h
        int 21h
        jmp again

    start:
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

	mov dl, 08				; Удаление последнего введенного символа с экрана (удаление знака esc)
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

