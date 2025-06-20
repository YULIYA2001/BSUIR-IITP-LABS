model small
.stack 100h
.data
    string dw 6 dup ('$')
    text db ' is too much', 10, 13, 'try again: $'
    mes1 db 10, 13, 'enter the first number a (0<=a<65536): $'
    mes2 db 'enter the second number b (0<=b<65536): $'
    mes3 db 'the result of division a by b', 10, 13, 'quotient: $'
    mes4 db 10, 13, 'remainder: $'
    mes5 db 10, 13, 'error: division by 0 $'
    mes6 db 10, 13, 'press any key to continue $'

.code
    output proc
        push bx
	push cx
	push dx
    
	lea bx, [string + 10]		; ��������� � bx ����� ���������� ����� ������(6-�� $)

	output_cycle:
	    xor dx, dx
            mov cx, 10
            div cx			; ������ ����� �� 10
            lea bx, [bx-2]		; �������� ����� bx �� ����� �����
            add dx, 48			; �������� ��� 0 � �������
            mov [bx], dx		; ��������� ������� �� ������ bx
            cmp ax, 0
            jnz output_cycle

        lea dx, [bx]
	mov ah, 09h
	int 21h

	pop dx
	pop cx
	pop bx
	ret
    output endp

    input proc
   	push bx
	push cx
	push dx

        begin:	
	xor bx, bx
        xor cx, cx
	push cx

	input_cycle:
	    mov ah, 01h
    	    int 21h
	    cmp al, 13			; �������� �� enter
	    jz lab_enter
	    cmp al, 8			; ��������� backspace
	    jz backspace
	    cmp al, 27			; �������� escape
	    jz escape
	    cmp al, 48
	    jb delete			; ������� ���� al < 48
	    cmp al, 57
	    ja delete			; ������� ���� al > 57
	    jmp then

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
		jz begin
		mov ax, bx
		mov bx, 10
	        xor dx, dx
		div bx
		mov bx, ax
		sub cx, 1
		push cx
		jmp escape

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
	            sub al, 48		; ������ ��� 0
	            mov ch, 0
	            mov cl, al		; ��������� ��������� ����� � cx
	            mov ax, bx		; ---
	            mov dx, 10		; --- bx = bx * 10 + cx
	            mul dx		; ---
	            jc too_much		; ������� ���� bx > 65535
	            add ax, cx		; ---
	            jc too_much		; ������� ���� bx > 65535
	            mov bx, ax
	            jmp input_cycle
	
	    too_much:			; ����� bx > 65535		
		pop cx	
	        lea dx, text
	        mov ah, 09h
	        int 21h
		jmp begin

	end_cycle:
	mov ax, bx

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
    mov bx, ax
    mov ax, cx
    
    xor dx, dx			; a / b = 
    div bx

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