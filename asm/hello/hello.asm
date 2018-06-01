
global _start

section .data                     
message: db 'hello, world!', 10

section .text 
_start:                           
    mov     eax, 4          ; system call number should be stored in rax 
    mov     ebx, 1          ; argument #1 in rdi: where to write (descriptor)?
    mov     ecx, message    ; argument #2 in rsi: where does the string start? 
    mov     edx, 14         ; argument #3 in rdx: how many bytes to write? 
    int     0x80
;    syscall    

    mov rax, 60             ; exit
    syscall
