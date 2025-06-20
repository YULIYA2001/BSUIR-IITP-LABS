model small
.stack 100h
.data
    text db ' wrong input', 10, 13, 'try again: $'
    mes1 db 10, 13, 'enter the first number a (-32768<=a<32768): $'
    mes2 db 'enter the second number b (-32768<=b<32768): $'
    mes3 db 'the result of dividing a by b', 10, 13, 'quotient: $'
    mes4 db 10, 13, 'remainder: $'
    mes5 db 10, 13, 'error: divide by 0 $'
    mes6 db 10, 13, 'press any key to continue $'

.code
.386					; �� ����������� jmp
    output proc
        push bx
	push cx
	push dx

	xor bx, bx
	test ax, 1000000000000000b	; �������� �� �������������
	jz output_cycle1
	push ax
	mov dx, '-'
	mov ah, 02h
	int 21h 
	pop ax
	neg ax

	output_cycle1:
	    xor dx, dx
            mov cx, 10
            div cx			; ������ ����� �� 10
	    push dx			; ��������� ������� � ����
	    add bx, 1			; ��������� ���-�� �������� � �����
            cmp ax, 0			; ����� �� �����������
            jnz output_cycle1

	output_cycle2:
	    pop cx			; ������� ��������� �����
	    add cx, 48			; �������� ��� 0
	    mov dx, cx			; ������� �� �����
	    mov ah, 02h				
	    int 21h			
	    sub bx, 1			; ��������� ���-�� �������� � �����
	    cmp bx, 0			; �������� �� ���-�� � 0
	    jnz output_cycle2

	pop dx
	pop cx
	pop bx
	ret
    output endp

    input proc
   	push bx
	push cx
	push dx
	push si

        begin:	
	xor bx, bx
        xor si, si
	xor cx, cx
	push cx

	input_cycle:
	    mov ah, 01h
    	    int 21h
	    cmp al, '-'
	    jz minus
	    cmp al, 13			; �������� �� enter
	    jz lab_enter
	    cmp al, 8			; ��������� backspace
	    jz backspace
	    cmp al, 27			; �������� escape
	    jz escape
	    cmp al, '0'
	    jb delete			; ������� ���� al < 48
	    cmp al, '9'
	    ja delete			; ������� ���� al > 57
	    jmp then

	    minus:
		cmp si, 0
		jnz delete
		cmp bx, 0
		jnz delete
		mov si, 1
		jmp input_cycle 

	    lab_enter:
		pop cx
		cmp cx, 0
		push cx
		jz input_cycle
		jmp end_cycle
		
	    backspace:
		pop cx
		cmp cx, 0
		push cx
		jnz not_empty
		cmp si, 1
		jnz go
		mov si, 0
		go:
		    mov dl, 32		; ����� ������� ���� ������� �����
		    mov ah, 02h		; �.�. ���������� ������� 
		    int 21h
		    jmp input_cycle

		not_empty:
		    mov ax, bx		; ���������� ����� ����� backspace
		    mov bx, 10
		    xor dx, dx
		    div bx
		    mov bx, ax
		    mov dl, 32		; ---
		    mov ah, 02h		; ��������
		    int 21h		; ����������
		    mov dl, 08		; �������
		    mov ah, 02h		; � ������
		    int 21h		; ---
		    pop cx
		    sub cx, 1
		    push cx
		    jmp input_cycle

	    escape:
		mov dl, 08		; ---
		mov ah, 02h		; ---
		int 21h			; ---
		mov dl, 32		; ��������
		mov ah, 02h		; ����������
		int 21h			; ����������
		mov dl, 08		; ������� 
		mov ah, 02h		; � ������
		int 21h			; ---
		pop cx
		cmp cx, 0
		jz escape_minus
		mov ax, bx
		mov bx, 10
	        xor dx, dx
		div bx
		mov bx, ax
		sub cx, 1
		push cx
		jmp escape

	    escape_minus:
		cmp si, 0
		jz begin
		mov si, 0
		mov dl, 08		; ---
		mov ah, 02h		; ---
		int 21h			; ---
		mov dl, 32		; ��������
		mov ah, 02h		; ������
		int 21h			; � ������
		mov dl, 08		; ---
		mov ah, 02h		; ---
		int 21h			; ---
		jmp begin

	    delete:	
		mov dl, 08		; ---
		mov ah, 02h		; ---
		int 21h			; ---
		mov dl, 32		; ��������
		mov ah, 02h		; ����������
		int 21h			; ����������
		mov dl, 08		; ������� 
		mov ah, 02h		; � ������
		int 21h			; ---
		jmp input_cycle

	    then:
		cmp bx, 0		; ������ ����� ����� 0
	        jnz not_zero
		pop cx
	        cmp cx, 1
		push cx
		jnz not_zero
	        jmp delete

		not_zero: 
	            pop cx		; ������� ���������� ��������
		    add cx, 1
	            push cx       
	            sub al, '0'		; ������ ��� 0
	            mov ch, 0
	            mov cl, al		; ��������� ��������� ����� � cx
	            mov ax, bx		; ---
	            mov dx, 10		; --- bx = bx * 10 + cx                               ���� ������ - �x ���� ����� ����� �� 1 � ��������� fc
	            mul dx		; ---
		    jc wrong_input	; �������� ������������ (������� ���� ax > 65535)
	            add ax, cx		; ---
		    jc wrong_input	; �������� ������������ (������� ���� ax > 65535)
	            cmp ax, 32768
		    jnz not_32768
		    cmp si, 0
		    jz wrong_input
		    jmp continue

		    not_32768:
	            ja wrong_input	; ������� ���� ax > 32768
		    
		    continue:
	            mov bx, ax
	            jmp input_cycle
	
	    wrong_input:		; ����� bx > 32767 ��� bx < -32768		
		pop cx	
	        lea dx, text
	        mov ah, 09h
	        int 21h
		jmp begin

	end_cycle:
	    mov ax, bx
	    cmp si, 1
	    jnz go_end
	    neg ax

	go_end:
	    pop si
	    pop cx
	    pop dx
	    pop cx
	    pop bx
	    ret
    input endp

start:
    mov ax, @data
    mov ds, ax

    lea dx, mes1		; ���� 1 �����
    mov ah, 09h
    int 21h
    call input
    mov cx, ax

    lea dx, mes2		; ���� 2 �����
    mov ah, 09h
    int 21h
    call input
    cmp ax, 0			; ������� �� 0
    jz err_mes 
    cmp cx, -32768
    jnz jump
    cmp ax, -1
    jz err_mes 

    jump:
        mov bx, ax
        mov ax, cx
    
    cwd				; a / b = 
    idiv bx

    cmp dx, 0
    jnl jump_then
    add dx, bx
    cmp ax, 0
    jl min
    inc ax
    jmp jump_then

    min:
	dec ax

    jump_then:
        push dx			; ��������� ���������
        push ax

    lea dx, mes3		; ����� ��������
    mov ah, 09h
    int 21h
    pop ax
    call output
	
    lea dx, mes4		; ����� �������
    mov ah, 09h
    int 21h
    pop ax
    call output
    jmp next

    err_mes:
	lea dx, mes5		; ��������� � ������� �� 0
        mov ah, 09h
        int 21h

    next:
    lea dx, mes6		
    mov ah, 09h
    int 21h
    mov ah, 01h			; �������� ����� �������
    int 21h

    mov ax, 4C00h
    int 21h
end start