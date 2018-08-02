;reboot using BIOS.
;nasm -f bin -o reboot.com reboot.asm

org 100h
section .text

start:  int 19h

.end