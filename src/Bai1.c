#include <stdio.h>
#include <stdlib.h> // For exit() function
#include <string.h>
#define MAX 200

struct stack{
  char character[MAX];
  int top;
};
typedef struct stack stack;
void Init(stack *a){
  a->top=0;
}
//PUSH FUNTION
void Push(stack *a,int value){
  if(a->top>=MAX){
    printf("canot push more element to stack.\n");
    exit(1);
  }
  else{
    a->top++;
    a->character[a->top]=value;
  }
}
//POP FUNTION
int Pop(stack *a){
  if(a->top<=0){
    printf("cannot pop more ..\n");
    exit(1);
  }
  else{
    int temp=a->character[a->top];
    a->top--;
    return temp;
  }
}
//CHECK BRACKET
int check(stack *a,char *str){
  int i;
  int count=0;
  for(i=0;i<strlen(str);i++){  //liner
    if((str[i]=='('))
      Push(a,str[i]);
    else if(str[i]==')'){
      if(a->top!=0){
    if(Pop(a)!='(')  //
      return 0;
      }
      else
    Push(a,str[i]);
    }
  else if(str[i]=='"'){
    count++;   //count the number of " character
    if(count%2!=0){    //check odd or even
      Push(a,str[i]);  // if odd
    }
    else{
      if(Pop(a)!='"')
    return 0;
    }
  }
  }
  if(a->top==0)
    return 1;
  else
    return 0;
}
int main()
{

    FILE *fptr,*fptw;
    stack a;
    Init(&a);
    char str1[MAX];
    if ((fptr = fopen("BRACKET.INP", "r")) == NULL)
    {
        printf("ERROR");
        // Program exits if file pointer returns NULL.
        exit(1);
    }
    else{
        // reads text until newline
        fscanf(fptr,"%[^\n]", str1);
        printf("FILE CONTENT:\n%s\n", str1);
        //fgets(str1,20,stdin);
        if(check(&a,str1)){
             printf("=>TRUE BRACKET!\n");
             fptw=fopen("BRACKET.OUT","wt");
             fprintf(fptw,"0");
             fclose(fptw);
             fclose(fptr);
        }
        else
            printf("=>FALSE BRACKET!\n");
            //THUC HIEN CONG VIEC SUA LOI O DOAN NAY

            //IN SO VI TRI CAN SUA

            //DONG
            fptw=fopen("BRACKET.OUT","w");
             fprintf(fptw,"X");
             fclose(fptw);
            fclose(fptr);
        return 0;

    }

}
