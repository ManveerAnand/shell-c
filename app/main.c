#include <stdio.h>
#include <string.h>

int main() {
  // Flush after every printf 
  setbuf(stdout, NULL);

  // Uncomment this block to pass the first stage

  // Wait for user input
  while(1){
  printf("$ ");
  char input[100];
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = '\0'; //remove the trailing newline character
  
  if(!strcmp(input,"exit 0")){
    return 0;
  }
  // printf("%d",strcmp(input,"exit 0"));
  printf("%s: command not found\n",input);

}
}
