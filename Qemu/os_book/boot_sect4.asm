
[org 0x7c00]
[BITS 16]
	mov [BOOT_DRIVE], dl	; dl from BIOS is our boot drive number


	mov bp, 0x8000	; stack
	mov sp, bp

	mov bx, HELLO_MSG
        call print_string

	mov bx, GOODBYE_MSG
	call print_string

	mov dx, 0x1234
	call print_hex

	
	mov bx, 0x9000
	mov dh, 2
	mov dl, [BOOT_DRIVE]
	call disk_load	

	mov dx, [0x9000]
	call print_hex
	mov dx, [0x9000 + 512]
	call print_hex

 	mov si, vga_string   ; Адреса рядка
    	mov dh, 5            ; 5-й рядок
    	mov dl, 20           ; 20-й стовпчик
    	mov bl, 0x0E         ; Жовтий текст на чорному фоні
    	call print_string_direct

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

disk_load:
	; load DH sectors to ES:BX from drive DL
	; 
        push dx		; 
	mov ah, 0x02	; BIOS read sector function
	mov al, dh	; DH sectors
	mov ch, 0x00	; cylinder 0
	mov dh, 0x00	; head 0
	mov cl, 0x02	; from 2 sector
	int 0x13	; BIOS read disk

	jc disk_error	; CR if error

	pop dx
	cmp dh, al
	jne disk_error
	ret

disk_error:
	mov bx, DISK_ERROR_MSG
	call print_string
	jmp $

DISK_ERROR_MSG: db "Disk read error!", 0


; Вхідні параметри:
; SI - покажчик на рядок (string pointer), рядок має закінчуватися нулем (null-terminated)
; DH - рядок (row, 0-24)
; DL - стовпчик (column, 0-79)
; BL - атрибут кольору (наприклад, 0x0F - білий на чорному)

print_string_direct:
    pusha               ; Зберігаємо всі регістри загального призначення
    push es             ; Зберігаємо сегментний регістр ES

    ; 1. Налаштовуємо ES на сегмент відеопам'яті
    mov ax, 0xB800
    mov es, ax

    ; 2. Обчислюємо зміщення (offset) у відеопам'яті
    ; Формула: offset = (row * 80 + col) * 2
    ; Спочатку обчислюємо (DH * 80)
    mov al, dh          ; AL = row
    mov cl, 80
    mul cl              ; AX = row * 80
    
    ; Додаємо стовпчик (DL)
    xor ch, ch
    mov cl, dl          ; CX = column
    add ax, cx          ; AX = row * 80 + column
    
    ; Множимо на 2 (кожен символ займає 2 байти)
    shl ax, 1           ; AX = (row * 80 + column) * 2
    mov di, ax          ; DI тепер вказує на потрібне місце в ES:DI

.loop:
    lodsb               ; Завантажуємо символ з [DS:SI] в AL, інкрементуємо SI
    cmp al, 0           ; Перевіряємо на кінець рядка (null-terminator)
    je .done            ; Якщо 0, виходимо

    ; Записуємо символ та колір у відеопам'ять
    mov ah, bl          ; AH = колір
    stosw               ; Записуємо AX (символ + колір) за адресою [ES:DI] та інкрементуємо DI на 2
    
    jmp .loop

.done:
    pop es              ; Повертаємо ES
    popa                ; Повертаємо всі регістри
    ret


[BITS 32]
    mov esi, message_pm
    mov ebx, 6          ; 6-й рядок
    mov ecx, 10         ; 10-й стовпчик
    mov edx, 0x0A       ; Яскраво-зелений на чорному
    call print_string_pm

; Вхідні параметри:
; ESI - покажчик на рядок (null-terminated)
; EBX - рядок (row, 0-24)
; ECX - стовпчик (column, 0-79)
; EDX - колір (атрибут, тільки нижній байт DL)

VIDEO_ADDRESS equ 0x000b8000

print_string_pm:
    pushad              ; Зберігаємо всі загальні регістри (EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI)

    ; Формула: offset = (row * 80 + col) * 2
    mov eax, ebx        ; EAX = row
    mov edi, 80
    mul edi             ; EAX = row * 80
    add eax, ecx        ; EAX = row * 80 + col
    shl eax, 1          ; EAX = (row * 80 + col) * 2

    ; 2. Додаємо базову адресу відеопам'яті
    add eax, VIDEO_ADDRESS
    mov edi, eax        ; EDI тепер вказує на цільову адресу в пам'яті
    ; Підготуємо атрибут кольору в AH для швидкого запису
    mov ah, dl          ; AH = color

.loop:
    lodsb               ; Читаємо байт з [ESI] в AL, ESI++
    cmp al, 0           ; Кінець рядка?
    je .done

    ; Записуємо символ (AL) та колір (AH) за адресою [EDI]
    mov [edi], ax       ; Пишемо відразу 2 байти
    add edi, 2          ; Переходимо до наступної клітинки (символ + колір)
    
    jmp .loop

.done:
    popad               ; Відновлюємо регістри
    ret


HELLO_MSG:
	db "Hello, World!", 10, 13, 0

GOODBYE_MSG:
	db "Goodbay!", 10, 13, 0


vga_string: db "Hello from Video Memory!", 0

message_pm: db "Protected Mode Direct Write!", 0

BOOT_DRIVE: db 0

	times 510-($ - $$) db 0
	dw 0xAA55

times 256 dw 0xdada
times 256 dw 0xface

