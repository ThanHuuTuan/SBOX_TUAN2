#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1000
#define MAX_SIZE 1000

int main()
{
    /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    char path[100];
    char buffer[BUFFER_SIZE];
    char oldWord[100], newWord[100];
    char matrix[50][50];
    int chon=0,count=0;
    int wCount;
    int line, col,i;

    printf("Enter file name: ");
    scanf("%s", path);
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w");

if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open.\n");
        printf("Please check your file.\n");
        exit(EXIT_SUCCESS);
    }
else{
   do
    {

        printf("===========>Avaliabe file\n");
        printf("\t\t\t ==MENU==\n");
        printf("\t\t\t |1. Search\n");
        printf("\t\t\t |2. Repalce\n");
        printf("\t\t\t |3. Exit\n");
        printf("\t\t\t >Select: ");
        scanf("%d",&chon);
        switch(chon)
        {
            case 1:
                    {
                    printf("Input a word: ");
                    scanf("%s", newWord);
// COunt occurrences
                     wCount = countOccurrences(fPtr, newWord);
                     printf("'%s' appears %d times in File.\n", newWord, wCount);

/* Display index of substring
                    indexOf(fPtr, newWord, &line, &col);
                    if (line!= -1){
                        printf("line: %d, col: %d\n", line+1, col + 1);
                    }
                     else{
                        printf("------------------NO EXIST-------\n");
                     }
*/
                    fclose(fPtr);

                    break;

                    }

            case 2:{
                printf("Enter word want to replace: ");
                scanf("%s", oldWord);

                printf("Replace '%s' by: ");
                scanf("%s", newWord);

                while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
                    {
                        // Replace all occurrence of word from current line
                        replaceAll(buffer, oldWord, newWord);
                        // After replacing write it to temp file.
                        fputs(buffer, fTemp);
                    }
                    /* Close all files to release resource */
                    fclose(fPtr);
                    fclose(fTemp);
                    /* Delete original source file */
                    remove(path);
                    /* Rename temp file as original file */
                    rename("replace.tmp", path);
                    printf("\nReplace'%s' by '%s' sucessful.", oldWord, newWord);
                    return 0;
                break;
                }
            case 3:
                break;
            default:
                printf("ReSelect MENU!\n");
                break;
        }

    }while(chon!=4);
    return 0;
    }
}
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;
    owlen = strlen(oldWord);

//Repeat till all occurrences are replaced.
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);
        // Index of current found word
        index = pos - str;
        // Terminate str after word found index
        str[index] = '\0';
        // Concatenate str with new word
        strcat(str, newWord);
        // Concatenate str with remaining words after
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}
int match(const char *s, const char *p, int overlap)
{
        int c = 0, l = strlen(p);

        while (*s != '\0') {
                if (strncmp(s++, p, l)) continue;
                if (!overlap) s += l - 1;
                c++;
        }
        return c;
}
int countOccurrences(FILE *fptr, const char *word)
{
    char str[BUFFER_SIZE];
    char *pos;
    int index, count;
    count = 0;
    // Read line from file till end of file.
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        index = 0;
        // Find next occurrence of word in str
        while ((pos = strstr(str + index, word)) != NULL)
        {
            // Index of word in str is
            // Memory address of pos - memory
            // address of str.
            index = (pos - str) + 1;
            count++;

        }
    }
    return count;
}
int indexOf(FILE *fptr, const char *word, int *line, int *col)
{
    char str[BUFFER_SIZE];
    char *pos;
    *line = -1;
    *col  = -1;

    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        *line += 1;
        // Find first occurrence of word in str
        pos = strstr(str, word);
        if (pos != NULL)
        {
            // First index of word in str is
            // Memory address of pos - memory
            // address of str.
                    *col = (pos - str);
                     col++;
            break;
        }
    }
    // If word is not found then set line to -1
    if (*col == -1)
        *line = -1;
    return *col;

}

