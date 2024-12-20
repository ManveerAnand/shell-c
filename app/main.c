#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

enum commands
{
  EXIT,
  ECHO,
  TYPE,
  PWD,
  CD
};

int get_command(char *input)
{
  char *c;
  c = strtok(input, " ");
  if (strcmp("exit", c) == 0)
  {
    return EXIT;
  }

  if (strcmp("echo", c) == 0)
  {
    return ECHO;
  }

  if (strcmp("type", c) == 0)
  {
    return TYPE;
  }

  if (strcmp("pwd", c) == 0)
  {
    return PWD;
  }

  if (strcmp("cd", c) == 0)
  {
    return CD;
  }

  return -1;
}

bool isValid(char *path, char *args)
{
  char filepath[100] = "";
  char *directory = strtok(path, ":");
  int size = 100;
  char fullpath[1024];
  while (directory != NULL)
  {
    snprintf(filepath, 100, "%s/%s", directory, args);
    if (access(filepath, F_OK) == 0)
    {
      return true;
    }
    directory = strtok(NULL, ":");
  }
  return false;
}

int main()
{

  setbuf(stdout, NULL);

  char *path = getenv("PATH");
  char abs[2024];
  strcpy(abs, path);
  while (1)
  {
    strcpy(abs, path);
    printf("$ ");
    char *command;
    char *token;
    char *args;
    char input[100];
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0'; // remove the trailing newline character
    char temp[1024];
    strcpy(temp, input);
    command = strtok(temp, " ");
    args = strtok(NULL, " ");

    int operation = get_command(input);
    // for type command
    char filepath[100] = "";
    bool found = false;
    int size = 100;
    char fullpath[1024];
    char cwd[1024];


    switch (operation)
    {

    case EXIT:
      if (input[5] == '0')
        return 0;

    case ECHO:
      printf("%.*s\n", strlen(input) - 5, input + 5);
      break;

    case TYPE:
      if (get_command(args) != -1)
      {
        printf("%s is a shell builtin\n", args);
      }

      else
      {
        char *directory = strtok(abs, ":");
        while (directory != NULL)
        {
          snprintf(filepath, 100, "%s/%s", directory, args);
          if (access(filepath, F_OK) == 0)
          {
            found = true;
            if (size >= strlen(directory))
            {
              size = strlen(directory);
              snprintf(fullpath, 1024, "%s", filepath);
            }
          }
          directory = strtok(NULL, ":");
        }
        if (!found)
          printf("%s: not found\n", args);
        else
        {
          printf("%s is %s\n", args, fullpath);
        }
      }
      break;

    case PWD:
      getcwd(cwd, sizeof(cwd));
      printf("%s\n", cwd);
      break;

    case CD:
        if(strcmp(args, "~") == 0) {
            chdir(getenv("HOME"));
        } else
        if (chdir(args) != 0) {
        fprintf(stderr, "cd: %s: ", args);
        perror("");
}

      break;
    default:
      if (isValid(path, command))
      {
        if (fork() == 0)
        {
          execvp(command, (char *const[]){command, args, NULL});
        }
        else
        {
          wait(NULL);
        }
      }
      else
      {
        printf("%s: command not found\n", command);
      }
    }
  }
}
