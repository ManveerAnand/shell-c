#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


enum commands{
  EXIT,
  ECHO,
  TYPE,
  EXEC
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

bool isValid(char* path,char* args)
{
  char filepath[100] = "";
  char *directory = strtok(path, ":");
  int size = 100;
  char fullpath[1024];
  while(directory != NULL) 
      {
        snprintf(filepath,100,"%s/%s",directory,args);  
        if (access(filepath, F_OK) == 0) {
          return true;
        }
        directory = strtok(NULL, ":");
      }
  return false;
}

int main() {
  
  setbuf(stdout, NULL);
  
  char *path = getenv("PATH");
  char *abs = malloc(strlen(path) + 1);
  strcpy(abs, path);
  // printf("path: %s\n", abs);

  while(1){
  strcpy(path, abs);
  char *directory = strtok(path, ":");
  printf("$ ");
  char input[100];
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = '\0'; //remove the trailing newline character
  int operation = get_command(input);
  char *command;
  
  //for type command
  char args[100] = "";
  char filepath[100] = "";
  bool found = false;
  int size = 100;
  char fullpath[1024];


//different commands logic
  switch(operation){
    case EXIT:
      if(input[5]=='0')
      return 0;
    
    case ECHO:
      printf("%.*s\n",strlen(input)-5,input+5);
      break;
    
    case TYPE:
      snprintf(args,100,"%.*s",strlen(input)-5,input+5); 
      args[strlen(args)] = ' ';
      
      if(get_command(args)!=-1)
      {
        printf("%sis a shell builtin\n",args);
      }
      
      else{
      args[strlen(args)-1] = '\0'; 

      while(directory != NULL) 
      {
        snprintf(filepath,100,"%s/%s",directory,args);  
        if (access(filepath, F_OK) == 0) {
          found = true;
          if(size>=strlen(directory))
          {
            size = strlen(directory);
            snprintf(fullpath,1024,"%s",filepath);
            
          }
        }
        directory = strtok(NULL, ":");
      }
      if(!found)
        printf("%s: not found\n",args);
      else{
          printf("%s is %s\n", args, fullpath);
          }
      }
      break;
      
      default:
      command = strtok(input, " ");
      char* args = strtok(NULL, " ");
      if(isValid(abs,command))
      {
      if(fork()==0){
      execvp(command, (char *const[]){command, args, NULL});
      }
      else{
        wait(NULL);
    }
  }
  else{
    printf("%s: command not found\n",command);
  }
}
}
}



