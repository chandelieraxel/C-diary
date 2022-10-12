#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

/**   
 Make a program that take an input from an user, save into a file.
 Make command to read from the file and output it fully.
 Must timestamp with date and username then separator, such as a diary
 * @param argc Number of arguments given
 * @param argv Actual arguments
 * @return int 
 */
int main(int argc, char *argv[]) {
    // Is the printf() simply doing this ?
    // char string[12] = "Hello World";
    // write(1, string, sizeof(string));

    if (argv[1] != NULL && strcmp(argv[1], "print") == 0) {
        FILE* diaryPtr;
        int letterBuff;

        diaryPtr = fopen("./diary.txt", "r");

       //! Be mindful, fgetc() return byte by byte. If \n, it may break an UTF-8 encoding 
       while((letterBuff = fgetc(diaryPtr)) != EOF) {
        //* %i Print the decimal representation of the letter, can look back into the decimal ASCII table
        //* So %c automatically convert a given integer into the corresponding ASCII, but not UTF-8 value ?
        printf("%c", letterBuff);
       };
       printf("\n");

        // char letter[5] = "\xE1";
        // Looks like it's break the encoding, print � in stdout. But why ? As it's working properly in file reading
        // printf("%s", letter);

        fclose(diaryPtr);
        return 0;
    } 

    int MAX_INPUT_SIZE = 1024;

    printf("What do you wish to write today ? \n");

    // Can I handle this more properly, allocate dynamically ?
    char input[MAX_INPUT_SIZE];

    fgets(input, MAX_INPUT_SIZE, stdin);

    // Why Bus Error ?
    // time_t* writingTime;
    // time(writingTime);
    time_t writingTime;
    time(&writingTime);

    struct tm* local;
    local = localtime(&writingTime);

    FILE* diaryPtr;
    diaryPtr = fopen("./diary.txt", "a"); 

    fprintf(diaryPtr, "%d/%d/%d %d:%d : %s", 1900 + local->tm_year, 1 + local->tm_mon, local->tm_mday, local->tm_hour, local->tm_min, input);

    fclose(diaryPtr);

    printf("Your entry has been properly registered. \n");
    printf("Goodbye !\n");

    return 0;
}