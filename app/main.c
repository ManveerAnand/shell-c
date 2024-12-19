#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>


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
  
  char *path = getenv("PATH");
  char *directory = strtok(path, ":");

  while(1){

  printf("$ ");
  char input[100];
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = '\0'; //remove the trailing newline character
  int command = get_command(input);
  
  //for type command
  char filename[100];
  bool found = false;



//different commands logic
  switch(command){
    case EXIT:
      if(input[5]=='0')
      return 0;
    
    case ECHO:
      printf("%.*s\n",strlen(input)-5,input+5);
      break;
    
    case TYPE:
      snprintf(filename,100,"%.*s",strlen(input)-5,input+5);
      while(directory != NULL) 
      {
        if (access(directory, F_OK) == 0) {
          printf("%s is %s\n", filename, directory);
          found = true;
          break;
        }
        directory = strtok(NULL, ":");
      }
      if(!found)
        printf("%s: not found\n",input);
      break;
      
      default:
      printf("%s: command not found\n",input);  
      }
    }
}


