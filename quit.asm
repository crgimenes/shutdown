;shutdown via APM without questions or parameters.
;nasm -f bin -o quit.com quit.asm

org 100h
section .text

start:  
        ;chke if APM is ok
        mov ax, 5300h 
        xor bx, bx 
        int 15h 
        jc APM_error

        ;connect to APM API
        mov     ax, 5301h
        xor     bx, bx
        int     15h

        ;try to set APM version (to 1.2)
        mov     ax, 530Eh
        mov     cx, 0102h
        xor     bx, bx
        int     15h

        ;turn off the system
        mov     ax, 5307h
        mov     bx, 0001h
        mov     cx, 0003h
        int     15h
        hlt

APM_error: mov  dx, msgAPMError
           mov  ah, 9
           int  21h

exitError: mov  ax, 4CFFh
           int  21h

msgAPMError db "APM error or not available",0

.end