.globl power
.type power, @function
power:
    pushl %ebp          ;# sabe old base pointer
    movl %esp, %ebp     ;# make stack pointer the base pointer
    subl $4, %esp       ;# get room for our local storage
                        ;# la pila crece 4 bytes
    movl 8(%ebp), %ebx  ;# put first argument in %ebx
    movl 12(%ebp), %ecx ;# put second argument in %ecx
    
    movl %ebx, -4(%ebp) ;# store current result
                        ;# se guarda en el espacio que se creo
                        ;# en la pila
                        
power_loop_start:
    cmpl $1, %ecx       ;# if the power is 1, we are done
    je end_power
    movl -4(%ebp), %eax ;# move the current result into %eax
    imull %ebx, %eax    ;# multiply the current result by the
                        ;# base number
    movl %eax, -4(%ebp) ;# store the current result
    
    decl %ecx           ;# decrease the  power
    jmp power_loop_start ;#run for the next power
    
end_power:
    movl -4(%ebp), %eax ;# return value foes in %eax
    movl %ebp, %esp     ;# restore the stack pointer
    popl %ebp           ;# restore the base pointer
    ret
    