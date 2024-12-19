#include <stdio.h>
#include <string.h>


int get_command(char* input)
{
  if(strcmp("exit 0",input)==0){
    return 0;
  }

  char c[6] ;
  snprintf(c,100,"%.*s",5,input);
  if(strcmp("echo ",c)==0){
    return 1;
  }
  return -1;
}

int main() {
  
  setbuf(stdout, NULL);

  while(1){
  printf("$ ");
  
  char input[100];
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = '\0'; //remove the trailing newline character
  int command = get_command(input);

  
  switch(command){
    case 0:
      return 0;
    case 1:
      printf("%.*s\n",strlen(input)-5,input+5);
      break;
      default:
      printf("%s: command not found\n",input);  
      }
    }
}


