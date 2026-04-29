
[org 0x7c00]

	mov bp, 0x8000	; stack
	mov sp, bp

	mov bx, HELLO_MSG
        call print_string

	mov bx, GOODBYE_MSG
	call print_string

	mov dx, 0x1234
	call print_hex

	jmp $

print_string:
        ; input   bx : string
        ; modify  ax, bx
	mov ah, 0x0e	; int 10, ah=0eh -> scrolling teletype BIOS
	mov al, [bx]
        cmp al, 0
        je done
	
	int 0x10
        inc bx
        jmp print_string
done:
	ret

print_hex:
	; input dx 0xHHHH
	; modify ax, bx, cx, dx

	mov cx, 4	; 4 HEX digits, every by 4 bits

char_loop:
	push cx

	mov ax, dx
	shr ax, 12
	and ax, 0x000f	; get 4 bits

	add al, '0'
	cmp al, '9'
	jle set_char
	add al, 7	; > 9  need 'A' +

set_char:
	mov bx, HEX_OUT
	add bx, 6	; 6 hex char
	sub bx, cx	; index of hex
	mov [bx], al

	shl dx, 4	; next 4 bits
	pop cx
	loop char_loop

        mov bx, HEX_OUT
	call print_string
        ret

HEX_OUT:	db "0x0000", 0

HELLO_MSG:
	db "Hello, World!", 10, 13, 0

GOODBYE_MSG:
	db "Goodbay!", 10, 13, 0


	times 510-($ - $$) db 0
	dw 0xAA55

