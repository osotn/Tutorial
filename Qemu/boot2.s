;org 0x7C00
bits 16

%define ENDL 0x0D, 0x0A
%define ENDS 0x00

start:
	jmp main


cls:
	pusha
	mov al, 03h
	mov ah, 00h
	int 10h
	popa
	ret

printstr:
	push si
	push ax
.loop:
	lodsb
	or al, al
	jz .done

	mov ah, 0Eh
	mov bh, 0
	int 10h

	jmp .loop

.done:
	pop ax
	pop si
	
	ret



main:
        call cls
	mov si, string
	call printstr
.stop:
	hlt
	jmp .stop

string: db "Hello World!", ENDL, ENDS

times 510 - ($-$$) db 0
dw 0x0AA55

