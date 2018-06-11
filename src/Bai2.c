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

    printf("Enter file name: ");
    scanf("%s", path);
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w");

if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open.\n");
        printf("Please check your file.\n");
        exit(EXIT_FAILURE);
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
                    printf("Substring to search:");
                    scanf("%s",newWord);
                    Postion(fPtr,newWord);
// Count occurrences
                    countOccurrences(fPtr, newWord);
                    fclose(fPtr);
                    break;

                    }

            case 2:{
                printf("Enter substring want to replace: ");
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

void countOccurrences(FILE *fptr, const char *word)
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
    printf("-->'%s' appears %d times in File.\n", word, count);
   //return count;
}

void Postion(FILE *fp, const char *subStr)
{
    char line[MAX_SIZE];
    int line_number=0,l=0,i,j,flag;
    char c;
    do
    {
        //read by line
        l=0;
        memset(line,'\0',sizeof(line));
        while((c = fgetc(fp)) != EOF)
        {
            if(c=='\n')
                break;
            line[l++]=(char)c;
        }
        line[l]='\0';
        for(i=0;i<strlen(line)-strlen(subStr);i++)
        {
            flag=1;
            for(j=0;j<strlen(subStr);j++)
            {
                if(line[i+j]!=subStr[j])
                {
                    flag=0;
                    break;
                }
            }
            if(flag==1)
                printf("=>line: %d, column: %d \n",line_number,i);
        }
        line_number++;
    }while(c!=EOF);


}
