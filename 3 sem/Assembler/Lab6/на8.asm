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
        cmp al, 01h				; ���������� ��� � ����� esc
        je esc_symbol
        jmp old_handler
       
	big:					; ���� ���� big? = 1, �� ������������� big? = 0 
	    cmp big?, 1				; (������ ������� Shift ��� ������� Caps Lock)
            jne big_then			; ���� ���� big? = 0, �� ������������� big? = 1
	    mov big?, 0				; (��� ��������� ������: ������� Left Shift, Right Shift ��� Caps Lock)
	    jmp old_handler
            big_then:
	        mov big?, 1
	        jmp old_handler

	little:					; ���� ���� big? = 0, �� ������������� big? = 1
	    cmp big?, 1				; (������ ���������� Shift ��� ������� Caps Lock)
            jne little_then			; ���� ���� big? = 1, �� ������������� big? = 0
	    mov big?, 0				; (��� ��������� ������: ���������� Left Shift, Right Shift ��� Caps Lock)
	    jmp old_handler
	    little_then:
	        mov big?, 1
	        jmp old_handler

	esc_symbol:				; ���� ����� Esc (����� �� ���������), ������������� ���� exit? = 1
            mov exit?, 1
	    jmp old_handler

        new_handler: 				; ���� ���� big? = 1 (����� �������), �������� ��. ����� "������������"
	    cmp big?, 1
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

    mov dl, 08					; �������� ���������� ���������� ������� � ������ (�������� ����� esc)
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