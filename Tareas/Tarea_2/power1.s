.section .text

.globl _start

_start:
    pushl $3            ;#push second argument
    pushl $2            ;# push first argument
    call power          ;# call the function
    addl $8, %esp       ;# move the stack pointer back
                        ;# esp siempre debe apuntar a la cima
    pushl %eax
    
    pushl $2            ;# push second argument
    pushl $5            ;# push first argument
    call power          ;# call the function
    addl $8, %esp       ;# move the stack pointer back
    
    popl %ebx           ;# restore the base pointer
    
    addl %eax, %ebx     ;# sume el contenido de %eax y %ebx
                        ;# y se guarda en %ebx para echo
    
    movl $1, %eax
    int $0x80
