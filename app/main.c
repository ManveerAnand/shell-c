#include <stdio.h>
#include <string.h>

enum commands{
  EXIT,
  ECHO,
  TYPE
};


int get_command(char* input)
{
  char c[6] ;
  snprintf(c,100,"%.*s",5,input);
  
  if(strcmp("exit ",c)==0){
    return EXIT;
  }
  
  if(strcmp("echo ",c) == 0){
    return ECHO;
  }
  
  if(strcmp("type ",c) == 0){
    return TYPE;
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
  char comcheck[100];

//different commands logic

  switch(command){
    case EXIT:
      if(input[5]=='0')
      return 0;
    
    case ECHO:
      printf("%.*s\n",strlen(input)-5,input+5);
      break;
    
    case TYPE:
      snprintf(comcheck,100,"%.*s",strlen(input)-5,input+5);
      comcheck[strlen(input)-5] =  ' ';
      comcheck[strlen(input)-4]=  '\0';
      // printf("%s\n",comcheck);
      if(get_command(comcheck) != -1){
        printf("%s is a shell builtin\n",comcheck);
      }
      else{
        printf("%s: command not found\n",comcheck);
      }
      break;
      
      default:
      printf("%s: command not found\n",input);  
      }
    }
}


