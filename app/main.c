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
  char *abs = malloc(strlen(path) + 1);
  strcpy(abs, path);


  while(1){
  strcpy(path, abs);
  char *directory = strtok(path, ":");
  printf("$ ");
  char input[100];
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = '\0'; //remove the trailing newline character
  int command = get_command(input);
  
  //for type command
  char filename[100] = "";
  char filepath[100] = "";
  bool found = false;
  int size = 100;
  char fullpath[1024];


//different commands logic
  switch(command){
    case EXIT:
      if(input[5]=='0')
      return 0;
    
    case ECHO:
      printf("%.*s\n",strlen(input)-5,input+5);
      break;
    
    case TYPE:
      snprintf(filename,100,"%.*s",strlen(input)-5,input+5); // extract filename
      // printf("filenamesize:%d\n",strlen(filename));
      filename[strlen(filename)] = ' ';
      if(get_command(filename)!=-1)
      {
        printf("%sis a shell builtin\n",filename);
      }
      else{
      filename[strlen(filename)-1] = '\0'; 
      // printf("filenamesize:%d\n",strlen(filename));

      while(directory != NULL) 
      {
        snprintf(filepath,100,"%s/%s",directory,filename);  
        // printf("%s\n",filepath);
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
        printf("%s: not found\n",filename);
      else{
          printf("%s is %s\n", filename, fullpath);
          }
      }

      break;
      
      default:
      printf("%s: command not found\n",input);  
      }
    }
}


