#include "include.h"

int main()
{
    FILE* file;
    char str[10];
    char first_tag[] = "XV5"; 
    char* fgets_out;

    file = fopen("input", "r");

    fgets_out = fgets(str, sizeof(str), file);

    printf("%c\n", (fgets_out == str) ? 'T' : 'F');

    printf("%s", str); // str includes the final newline

    printf("strlen: %ld\n", strlen(str));
    

    fclose(file);
}






// #define NAME_LENGTH 3
// #define NAME_BUFFER (NAME_LENGTH + 1)
// #define LINE_LENGTH 8
// #define LINE_BUFFER (LINE_LENGTH + 1)

// #define READLINE_OK 0
// #define READLINE_EOF 1
// #define READLINE_BUFF_TOO_SHORT -1

// int readline(FILE* file, char* line_buffer, int buffer_length)
// {
//     char c = '\0';

//     while( ((c = fgetc(file)) != '\n') && (c != EOF))
//     {

//     }
// }

// int main()
// {
//     char orbiter[NAME_BUFFER] = {'_','_','_','\0'};
//     char orbitee[NAME_BUFFER] = {'_','_','_','\0'};
//     char line_buffer[LINE_BUFFER] = {'_','_','_','_','_','_','_','_','\0'};

//     char c;
//     FILE* input = fopen("input", "r");
    
//     // readline(input, line_buffer);

//     printf("%s", line_buffer);

//     fclose(input);
// }