;--------------------- ��������������� ����������� ���������� ���������� (INT 9) ------------------------------
;----------------------- ���, ����� �� ��������� ����� ��������� ������� ����� --------------------------------
;------------------------- ��� ����� "I" ��� ������� ������������ ����� ����� ---------------------------------
;------------------------ ��� ����� "u" ��� ������� ������������ ������� ����� --------------------------------
;-------------------------- ��� ����� "o" ��� ������� ������������ �� ����� -----------------------------------
;----------------------- ��� ����� "v" ��� ������� ������������ ������� ����� ---------------------------------
;---------------------- ��� ����� "c" ��� ������� ������������ ��������� ����� --------------------------------

.model small
.stack 100h
.data
    old_handle dd ?
    big? db 0
    exit? db 0
    first db 0					; ��� ����, ����� ����� ��� ������� ������ �������� (shift+�����) 
    						; ����� ����������, ��������� ���������� shift ������ �� ������ 
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
	in al, 60h				; �������� ����-��� �������

	cmp al, 2Ah				; ������� Left Shift
	je big
	cmp al, 0AAh				; ���������� Left Shift
	je little
	cmp al, 36h				; ������� Right Shift
	je big
	cmp al, 0B6h				; ���������� Right Shift
	je little
	cmp al, 3Ah				; ������� Caps Lock
	je big
	cmp al, 0BAh				; ���������� Caps Lock
	je little
	cmp al, 01h				; ���������� ��� � ����� esc
        je esc_symbol
	cmp flagc, 1				; ���� ���������� ���� "c" (������� ��������� �����), ���� �� ��������� ���������
	je S

	;-------------------------  ������� ----------------------------------
        cmp al, 12h 				; ���������� ��� � ����� ����� e
	mov dl, 'E'
	je new_handler
	cmp al, 15h 				; ���������� ��� � ����� ����� y
	mov dl, 'Y'
	je new_handler
	cmp al, 16h 				; ���������� ��� � ����� ����� u
	mov dl, 'U'
	je new_handler
	cmp al, 17h 				; ���������� ��� � ����� ����� i 
	mov dl, 'I'
	je new_handler
	cmp al, 18h 				; ���������� ��� � ����� ����� o
	mov dl, 'O'
	je new_handler
	cmp al, 1Eh 				; ���������� ��� � ����� ����� a
	mov dl, 'A'
	je new_handler
	cmp flagI, 1				; ���� ���������� ���� "I" (������� ����� �����), ���� �� ��������� ���������
	je S
	cmp flagu, 1				; ���� ���������� ���� "u" (������� ������� �����), ���� �� ��������� ���������
	je S
	cmp flago, 1				; ���� ���������� ���� "o" (������� �� �����), ���� �� ��������� ���������
	je S
        jmp old_handler

	S:
	;------------------------- ��������� ----------------------------------
        cmp al, 10h 				; ���������� ��� � ����� ����� q
	mov dl, 'Q'
	je new_handler
	cmp al, 11h 				; ���������� ��� � ����� ����� w
	mov dl, 'W'
	je new_handler
	cmp al, 13h 				; ���������� ��� � ����� ����� r
	mov dl, 'R'
	je new_handler
	cmp al, 14h 				; ���������� ��� � ����� ����� t 
	mov dl, 'T'
	je new_handler
	cmp al, 19h 				; ���������� ��� � ����� ����� p
	mov dl, 'P'
	je new_handler
	cmp al, 1Fh 				; ���������� ��� � ����� ����� s
	mov dl, 'S'
	je new_handler
	cmp al, 20h 				; ���������� ��� � ����� ����� d
	mov dl, 'D'
	je new_handler
	cmp al, 21h 				; ���������� ��� � ����� ����� f
	mov dl, 'F'
	je new_handler
	cmp al, 22h 				; ���������� ��� � ����� ����� g
	mov dl, 'G'
	je new_handler
	cmp al, 23h 				; ���������� ��� � ����� ����� h 
	mov dl, 'H'
	je new_handler
	cmp al, 24h 				; ���������� ��� � ����� ����� j
	mov dl, 'J'
	je new_handler
	cmp al, 25h 				; ���������� ��� � ����� ����� k
	mov dl, 'K'
	je new_handler
	cmp al, 26h 				; ���������� ��� � ����� ����� l
	mov dl, 'L'
	je new_handler
	cmp al, 2Ch 				; ���������� ��� � ����� ����� z
	mov dl, 'Z'
	je new_handler
	cmp al, 2Dh 				; ���������� ��� � ����� ����� x
	mov dl, 'X'
	je new_handler
	cmp al, 2Eh 				; ���������� ��� � ����� ����� c 
	mov dl, 'C'
	je new_handler
	cmp al, 2Fh 				; ���������� ��� � ����� ����� v
	mov dl, 'V'
	je new_handler
	cmp al, 30h 				; ���������� ��� � ����� ����� b
	mov dl, 'B'
	je new_handler
	cmp al, 31h 				; ���������� ��� � ����� ����� n
	mov dl, 'N'
	je new_handler
	cmp al, 32h 				; ���������� ��� � ����� ����� m
	mov dl, 'M'
	je new_handler
	cmp flago, 1				; ���� ���������� ���� "o" ������� �� ����� (�����, ���� �� ����� ��� �����)
	je exit
	jmp old_handler
       
	big:					; ���� ���� big? = 1, �� ������������� big? = 0
	    cmp big?, 1				; (������ ������� Shift ��� ������� Caps Lock)
            jne big_then			; ���� ���� big? = 0, �� ������������� big? = 1
	    mov big?, 0				; (��� ��������� ������: ������� Left Shift, Right Shift ��� Caps Lock)
	    jmp old_handler
            big_then:
	        mov big?, 1
	        jmp old_handler

	little:					
	    cmp first, 1			; ���������: shift "��������" ��� ����� ��������� ������� ��� ��� ��������� ������
            je first_letter			; ���� ���� big? = 0, �� ������������� big? = 1
	    cmp big?, 1				; (������ ���������� Shift ��� ������� Caps Lock)
            jne little_then			; ���� ���� big? = 1, �� ������������� big? = 0
	    mov big?, 0				; (��� ��������� ������: ���������� Left Shift, Right Shift ��� Caps Lock)
	    jmp old_handler
	    little_then:
	        mov big?, 1
	        jmp old_handler
	    first_letter:			; ���� shift "��������" ��� ����� ��������� �������, ���������� ��� � ���������� ����
	        mov first, 0
	        jmp old_handler

	esc_symbol:				; ���� ����� Esc (����� �� ���������), ������������� ���� exit? = 1
            mov exit?, 1
	    jmp old_handler

        new_handler: 
	    cmp flagc, 1			; ���� �������� - "c" (������� ��������� �����)
	    je then
	    cmp flagv, 1			; ���� �������� - "v" (������� ������� �����)
	    je then
	    cmp flago, 1			; ���� �������� - "o" (������� �� �����)
	    jne miss1
	    cmp big?, 1				; 	���� ���� big? = 1, �� �������� ������� �����
	    je print
	    add dl, 20h				; 	���� ���� big? = 0, �� �������� ����� �����
	    print:
	        mov ah, 02h
	        int 21h
		jmp then
	    miss1:		
	        cmp flagu, 1			; ���� �������� - "u" (������� ������� �����)
                jne miss2
	        cmp big?, 1			; 	���� ���� big? = 1, �� ������� � ����� (�������)
                je then
	        add dl, 20h			; 	����� �������� �� ����� (����� �����)
	        mov ah, 02h
	        int 21h
                jmp then
	    miss2:
	        cmp big?, 1			; ����� - ������� �����, �������� �������
                jne then
	        mov ah, 02h
	        int 21h
	    then:
                jmp exit
        
        old_handler: 
            pop ax bx cx dx di es si ds
	    popf
            jmp dword ptr cs:old_handle		; ����� ������������ ����������� ����������
                
        exit:
            xor ax, ax
            mov al, 20h
            out 20h, al 
            pop ax bx cx dx di es si ds		; �������������� ��������� ����� ������� �� ������ ����������� ����������
	    popf    
    iret
new_handle endp

main:
    mov ax, @data
    mov ds, ax

    mov ah, 02h					; ������� ����������� BIOS 
    int 16h					; ���������� �������� �� 0040:0017h
    shr al, 7					; ��� 6 ��� - ��������� Caps Lock
    jnc go					; ���� ��� ������� ��������� Caps Lock �������
    mov big?, 1					; ������������� ���� big? = 1
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
	    cmp big?, 1				; ���� caps lock ��� ������� ��� �������, �� shift
            je start				; �� ��������, ����� ��������, ��� ��� ����� shift
	    mov first, 1
            jmp start
	find_u:
	    lea dx, enter_mes
	    mov ah, 09h
	    int 21h
	    mov flagu, 1
	    cmp big?, 0				; ���� caps lock ��� ������� �� ��� �������, �� shift
            je start				; �� ��������, ����� ��������, ��� ��� ����� shift
	    mov first, 1
            jmp start
	find_o:
	    lea dx, enter_mes
	    mov ah, 09h
	    int 21h
	    mov flago, 1
	    cmp big?, 0				; ���� caps lock ��� ������� �� ��� �������, �� shift
            je start				; �� ��������, ����� ��������, ��� ��� ����� shift
	    mov first, 1
            jmp start
	find_v:
	    lea dx, enter_mes
	    mov ah, 09h
	    int 21h
	    mov flagv, 1
	    cmp big?, 0				; ���� caps lock ��� ������� �� ��� �������, �� shift
            je start				; �� ��������, ����� ��������, ��� ��� ����� shift
	    mov first, 1
            jmp start
	find_c:
	    lea dx, enter_mes
	    mov ah, 09h
	    int 21h
	    mov flagc, 1
	    cmp big?, 0				; ���� caps lock ��� ������� �� ��� �������, �� shift
            je start				; �� ��������, ����� ��������, ��� ��� ����� shift
	    mov first, 1
            jmp start

    error:
	lea dx, error_mes
        mov ah, 09h
        int 21h
        jmp again

    start:
	mov ax, 3509h				; ���������� ������� �����������
	int 21h
	mov word ptr old_handle, bx
	mov word ptr old_handle + 2, es

	push ds					; ��������� ������ �����������
	mov ax, 2509h
	mov dx, seg new_handle
	mov ds, dx
	mov dx, offset new_handle
    	int 21h
	pop ds

	cycle:					; ���� ����� �������, ���� �� ����� Esc (exit? = 1)
            mov ah, 01h
	    int 21h
	    cmp   exit?, 1
	    jne   cycle

	mov dl, 08				; �������� ���������� ���������� ������� � ������ (�������� ����� esc)
	mov ah, 02h
	int 21h
	mov dl, 32
	mov ah, 02h
	int 21h
	mov dl, 08 
	mov ah, 02h
	int 21h
	
	push ds					; ���������� ������� ����������� 9 ����������
	mov dx, word ptr old_handle
	mov bx, word ptr old_handle+2
	mov ds, bx
	mov ax, 2509h
	int 21h  
	pop ds
    
    mov ax, 4c00h
    int 21h
end main

