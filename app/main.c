#include <stdio.h>
#include <string.h>

int main() {
  // Flush after every printf 
  setbuf(stdout, NULL);

  // Uncomment this block to pass the first stage
  printf("$ ");

  // Wait for user input
  char input[100];
  fgets(input, 100, stdin);
  input[strcspn(input, "\n")] = '\0'; //remove the trailing newline character
  printf("%s: command not found",input);
  return 0;
}
