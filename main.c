/*
compile with:
tcc -mt -tDc main.c
*/
#include <stdio.h>

// APM installation check
char chkAPM() {
  asm {
    mov ax, 5300h 
    xor bx, bx 
    int 15h 
    jc APM_error
  }
  return 0;
APM_error:
  return -1;
}

void usage() {
  printf("shutdown for DOS\r\n"
         "Cesar Gimenes, @crgimenes\r\n"
         "https://github.com/crgimenes/shutdown\r\n\r\n"
         "Usage:\r\n"
         "\t-h halt require APM\r\n"
         "\t-r reboot (call BIOS int 19h)\r\n");
}

int main(int argc, char *argv[]) {

  if (argc == 1) {
    usage();
    return 1;
  }

  if (strcmp(argv[1], "-r") == 0) {
    asm int 19h
  }

  if (chkAPM()) {
    printf("APM error or not available");
    return 1;
  }

  if (strcmp(argv[1], "-h") == 0) {
    asm {
      /* connect to APM */
      mov     ax, 5301h
      xor     bx, bx
      int     15h

      /* set APM version */
      mov     ax, 530Eh
      mov     cx, 0102h
      xor     bx, bx
      int     15h

      /* shutdown */
      mov     ax, 5307h
      mov     bx, 0001h
      mov     cx, 0003h
      int     15h
      hlt
    }
  }

  return 0;
}
