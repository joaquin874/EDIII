#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

extern int errno;

struct PuertoB{
    unsigned short int MEMDIR;
    unsigned short int TRISB;
    unsigned short int ANSELH;
    unsigned short int PORTB;
};

int main() {
    char curr_time[10];
    char curr_date[12];
    int std_c;

    //strcpy(curr_time, __TIME__);
    //strcpy(curr_date, __DATE__);
    printf("%s %s\n", __TIME__, __DATE__);
    printf("This is line %d\n", __LINE__);    
    std_c = __STDC__;
    printf("STDC is %d", std_c); 
    
    // FILE *file = fopen("archivo_inexistente.txt", "r");
    
    // if (file == NULL) {
    //     perror("Error al abrir el archivo");
    //     printf("Mensaje de error: %s\n", strerror(errno));
    //     return 1;
    // }
    
    // fclose(file);

    
    return 0;
}

