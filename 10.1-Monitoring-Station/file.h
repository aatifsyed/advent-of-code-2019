#ifndef FILE_H
#define FILE_H

#include <stdio.h>

// Not including the terminating newline. Seeks to SEEK_SET
int first_line_length(FILE* file)
{
    int characters_in_line = 0;
    char current_char = '\0';

    // go to beginning of file
    fseek(file, 0, SEEK_SET);

    while ( (current_char = fgetc(file)) != '\n' && current_char != EOF)
    {
        characters_in_line++;
    }

    // go to beginning of file
    fseek(file, 0, SEEK_SET);

    return characters_in_line;
}

// Doesn't matter if file is newline terminated. Seeks to SEEK_SET
int lines_in_file(FILE* file)
{
    int lines_in_file = 0;
    char current_char = '\0';

    // go to beginning of file
    fseek(file, 0, SEEK_SET);

    while ( (current_char = fgetc(file)) != EOF)
    {
        if (current_char == '\n')
        {
            lines_in_file++;
        }
    }

    // go to penultimate character, and inspect it
    fseek(file, -1, SEEK_END);
    switch (fgetc(file))
    {
        // if it's a newline, then the final line is already accounted for
        case '\n':
            break;
        // file is not newline terminated, add one to our count
        default:
            lines_in_file++;
            break;
    }

    // go back to beginning of file
    fseek(file, 0, SEEK_SET);

    return lines_in_file;
}

#endif