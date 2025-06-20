;----------------------------------------------- ��������� ������ --------------------------------------
model small
.stack 100h
.data

    error_mes db 10, 13, 'Wrong input, try again: $'
    input_mes1 db 'Enter the number of rows of 1 matrix, (<11): $'
    input_mes2 db 'Enter the number of columns of 1 matrix (= rows of 2 matrix), (<11): $'
    input_mes3 db 'Enter the number of columns of 2 matrix, (<11): $'
    output_mes db 10, 13, 'The result of matrix multiplication: $'
    input_elements1 db 10, 13, 'Enter the elements of the first matrix $'
    input_elements2 db 10, 13, 'Enter the elements of the second matrix $'
    end_mes db 10, 13, 'press any key to continue $'
    spaces  db '       $'   
    enter_mes db 10, 13, '$'
    element_mes db ' element: $'
    matrix1_mes db 'First matrix:', 10, 13, '$'
    matrix2_mes db 'Second matrix:', 10, 13, '$'
    res_matrix_mes db 'Result matrix:', 10, 13, '$'
  
    Rows1 dw 0              
    ColsRows dw 0
    Cols2 dw 0                      
    Matrix1 dw 101 dup ('$')   
    Matrix2 dw 101 dup ('$')               
    ResultMatrix dw 101 dup ('$')                  

.code
.386					; �� ����������� jmp

;------------------------------------------------------------------------------------------------------
    ; ��������� ��� ������������� ������ ��������� ����� �� �����

    output proc
        push bx
	push cx
	push dx
        push si
	push di

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

	pop di
        pop si
	pop dx
	pop cx
	pop bx
	ret
    output endp

;-----------------------------------------------------------------------------------------------
    ; ��������� ��� ������������� ����� ��������� ����� �� ����� (��������� backspace, escape)

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
	    cmp al, '-'                 ; �������� �� ������������� �����
	    jz minus
	    cmp al, 13			; �������� �� enter
	    jz lab_enter
	    cmp al, 8			; ��������� backspace
	    jz backspace
	    cmp al, 27			; �������� escape
	    jz escape
	    cmp al, '0'
	    jb delete			; ������� ���� al < 48 (< ���� 0)
	    cmp al, '9'
	    ja delete			; ������� ���� al > 57 (> ���� 9)
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
	        lea dx, error_mes
	        mov ah, 09h
	        int 21h
		jmp begin

	end_cycle:
	    mov ax, bx
	    cmp si, 1
	    jnz go_end
	    neg ax

	go_end:
	    pop cx
            pop si
	    pop dx
	    pop cx
	    pop bx
	    ret
    input endp

;-----------------------------------------------------------------------------------------
    ; ��������� ����� ����������� ������� (� ���������)

    input_size proc
        push bx
	push cx
	push dx

	again:     
        call input
        cmp ax, 1                       ; �������� ������ ����� ����� (0 < Rows1 < 11)
        jb wrong
        cmp ax, 10
        ja wrong
	jmp end_input_size
    
        wrong:				; �������� �� ��������, ��������� � �������� �����                         
	    lea dx, error_mes
	    mov ah, 09h
	    int 21h
            jmp again

        end_input_size:

	pop dx
	pop cx
	pop bx
	ret
    input_size endp

;--------------------------------------------------------------------------------------------------
    ; ��������� ����� ��������� 1 ������� (� �������������� ��������� ����� �������� ����� input proc)

    input_matrix1 proc
        push ax
        push bx
	push cx
	push dx
	push si

        lea dx, input_elements1		; ���� ����� ����� ������ �������
        mov ah, 09h
        int 21h

        mov ax, Rows1                   ; ����� ���������� ��������� 1 �������
	mul ColsRows
        mov bx, ax
        call output			; ����� �� ����� ������ ���������� ��������� � enter 
        lea dx, enter_mes		
        mov ah, 09h
        int 21h                 
        xor cx, cx                       ; ������� ��������� ���������
        ;lea si, Matrix1
        mov si, 0

	matrix1_input:
	    inc cx
	    mov ax, cx
            call output 			; ����� ������ "CX element"		 
            lea dx, element_mes		
            mov ah, 09h
            int 21h
	    call input			; ����� ������� ����� ��������� �����
            mov Matrix1[si], ax		; ���������� ���������
	    inc si
	    inc si
            cmp cx, bx
	    jne matrix1_input


	pop si
	pop dx
	pop cx
	pop bx
        pop ax
	ret
    input_matrix1 endp   

;--------------------------------------------------------------------------------------------------
    ; ��������� ����� ��������� 2 ������� (� �������������� ��������� ����� �������� ����� input proc)

    input_matrix2 proc
        push ax
        push bx
	push cx
	push dx
	push si

        lea dx, input_elements2		; ���� ����� ����� ������ �������
        mov ah, 09h
        int 21h

        mov ax, Cols2			; ����� ���������� ��������� 1 �������
	mul ColsRows
        mov bx, ax
        call output			; ����� �� ����� ������ ���������� ��������� � enter 
        lea dx, enter_mes		
        mov ah, 09h
        int 21h                 
        xor cx, cx                       ; ������� ��������� ���������
        mov si, 0

	matrix2_input:
	    inc cx
	    mov ax, cx
            call output 			; ����� ������ "CX element"		 
            lea dx, element_mes		
            mov ah, 09h
            int 21h
	    call input			; ����� ������� ����� ��������� �����
            mov Matrix2[si], ax		; ���������� ���������
	    inc si
	    inc si
            cmp cx, bx
	    jne matrix2_input

	pop si
	pop dx
	pop cx
	pop bx
        pop ax
	ret
    input_matrix2 endp   

;-------------------------------------------------------------------------------------------------------
    ; ��������� ������ ��������� 1 ������� (� �������������� ��������� ������ �������� ����� output proc)

    output_matrix1 proc
        push ax
        push bx
	push cx
	push dx
	push si

        mov si, 0
        xor bx, bx
        mov ax, ColsRows
        mul Rows1
        mov cx, ax
        output_c_matrix1:
	    mov ax, Matrix1[si]
	    call output
	    lea dx, spaces
            mov ah, 09h
            int 21h
	    add si, 2
            inc bx
            mov ax, bx
	    xor dx, dx
	    div ColsRows
	    cmp dx, 0
	    jne end_output_c_matrix1
            lea dx, enter_mes
            mov ah, 09h
            int 21h
	    xor bx, bx
	end_output_c_matrix1:
        loop output_c_matrix1

	pop si
	pop dx
	pop cx
	pop bx
        pop ax
	ret
    output_matrix1 endp   

;-------------------------------------------------------------------------------------------------------
    ; ��������� ������ ��������� 2 ������� (� �������������� ��������� ������ �������� ����� output proc)

    output_matrix2 proc
        push ax
        push bx
	push cx
	push dx
	push si

        mov si, 0
        xor bx, bx
        mov ax, ColsRows
        mul Cols2
        mov cx, ax
        output_c_matrix2:
	    mov ax, Matrix2[si]
	    call output
	    lea dx, spaces
            mov ah, 09h
            int 21h
	    add si, 2
            inc bx
            mov ax, bx
	    xor dx, dx
	    div Cols2
	    cmp dx, 0
	    jne end_output_c_matrix2
            lea dx, enter_mes
            mov ah, 09h
            int 21h
	    xor bx, bx
	end_output_c_matrix2:
        loop output_c_matrix2

	pop si
	pop dx
	pop cx
	pop bx
        pop ax
	ret
    output_matrix2 endp   

;-------------------------------------------------------------------------------------------------------
    ; ��������� ������ ��������� �������������� ������� (� �������������� ��������� ������ �������� ����� output proc)

    output_res_matrix proc
        push ax
        push bx
	push cx
	push dx
	push si

        mov si, 0
        xor bx, bx
        mov ax, Rows1
        mul Cols2
        mov cx, ax
        output_c_matrix:
	    mov ax, ResultMatrix[si]
	    call output
	    lea dx, spaces
            mov ah, 09h
            int 21h
	    inc si
	    inc si
            inc bx
            mov ax, bx
	    xor dx, dx
	    div Cols2
	    cmp dx, 0
	    jne end_output_c_matrix
            lea dx, enter_mes
            mov ah, 09h
            int 21h
	    xor bx, bx
	end_output_c_matrix:
        loop output_c_matrix

	pop si
	pop dx
	pop cx
	pop bx
        pop ax
	ret
    output_res_matrix endp   

;---------------------------------------------------------------------------------------------------------
    ; ��������� ������������ ������, ������ � �������������� �������

    multiplication proc
        push ax
        push bx
	push cx
	push dx
	push si
	push di

	mov si, 0
	mov cx, Rows1
	external:
	    push cx
            mov di, 0
	    mov cx, Cols2

	    internal:
	        push cx
                xor bx, bx
	        mov cx, ColsRows
		xor ax, ax

		too_internal:
		    push ax
		    push si			;
	            mov ax, ColsRows		;
		    mul si			; mov ax, Matrix1[si*ColsRows][bx]
		    mov si, ax			;
		    mov ax, Matrix1[si][bx]	;
                    pop si			;
		
		    push ax			;
		    push bx			;
	            mov ax, Cols2		;
		    mul bx			; mov dx, Matrix2[bx*Cols2][di]
		    mov bx, ax			;
		    mov dx, Matrix2[bx][di]	;
		    pop bx
                    pop ax			;

		    imul dx			; ax * dx (������� ����)
		    pop dx			; ��� ����� ������������ ����� ��� ��������� ������ �� �������
		    add ax, dx			; ����� ��������� ������� �������������� �������
		    inc bx
		    inc bx
		    loop too_internal

		push ax				;
		mov ax, Cols2			;
		mov bx, si			; mov ResultMatrix[si*Cols2][di], ax
		mul bx				;
	 	mov bx, ax			;
		pop ax				;
		mov ResultMatrix[bx][di], ax	;
		inc di
		inc di
		pop cx
		loop internal
	    
	    inc si
	    inc si
	    pop cx
	    loop external	    
		
	pop di    
	pop si
	pop dx
	pop cx
	pop bx
        pop ax
	ret
    multiplication endp   

;---------------------------------------------------------------------------------------------------------
	; main �������
start:
    mov ax, @data
    mov ds, ax

    
      lea dx, input_mes1		; ���� ����� ����� ������ �������
      mov ah, 09h
      int 21h
    call input_size
    mov Rows1, ax

      lea dx, input_mes2		; ���� ����� �������� ������ ������� (= ����� ������ �������)
      mov ah, 09h
      int 21h
    call input_size
    mov ColsRows, ax

      lea dx, input_mes3		; ���� ����� �������� ������ ������� (= ����� ������ �������)
      mov ah, 09h
      int 21h
    call input_size
    mov Cols2, ax

    call input_matrix1
    call input_matrix2
      lea dx, matrix1_mes
      mov ah, 09h
      int 21h
    call output_matrix1
      lea dx, matrix2_mes
      mov ah, 09h
      int 21h
    call output_matrix2
    call multiplication
      lea dx, res_matrix_mes
      mov ah, 09h
      int 21h
    call output_res_matrix		
      lea dx, end_mes			; �������� ����� �������
      mov ah, 09h
      int 21h
    mov ah, 01h			
    int 21h

    mov ax, 4C00h
    int 21h
end start