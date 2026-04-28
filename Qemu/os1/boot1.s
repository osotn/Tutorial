org 0x7C00
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

	mov ah, 0x00    ; Функція ініціалізації
	mov al, 0xE3    ; Параметри: 111 (9600) + 00 (немає) + 0 (1 стоп) + 11 (8 біт)
	mov dx, 0x00    ; 0 = COM1
	int 0x14

	; 2. Передача одного символу 'A'
	mov ah, 0x01    ; Функція запису символу
	mov al, 'A'     ; Символ для відправки
	mov dx, 0x00    ; COM1
	int 0x14
.stop:
	hlt
	jmp .stop

string: db "Hello World!", ENDL, ENDS

times 510 - ($-$$) db 0
dw 0x0AA55

