# Shell-C

A simple UNIX shell implementation written in C, built as part of the [CodeCrafters Shell Challenge](https://codecrafters.io/challenges/shell).

## Overview

This project implements a basic command-line shell that can execute both built-in commands and external programs. The shell provides an interactive interface for running commands, navigating the filesystem, and executing programs found in the system PATH.

## Features

### Built-in Commands

- **`exit [code]`** - Exit the shell with an optional exit code
- **`echo <text>`** - Print text to standard output (supports quoted strings)
- **`type <command>`** - Display information about a command (whether it's a builtin or external program)
- **`pwd`** - Print the current working directory
- **`cd <directory>`** - Change the current directory (supports `~` for home directory)

### Additional Capabilities

- Execute external programs from PATH
- Command argument parsing with support for quoted strings
- Process forking and execution using `execvp`
- PATH resolution for external commands
- Error handling for invalid commands and failed operations

## Installation

### Prerequisites

- GCC (GNU Compiler Collection) 9.2 or later
- A UNIX-like operating system (Linux, macOS, WSL)

### Building

Clone the repository and compile the shell:

```bash
git clone https://github.com/ManveerAnand/shell-c.git
cd shell-c
gcc app/*.c -o shell
```

Or use the provided script:

```bash
./your_program.sh
```

This will compile the code and run the shell.

## Usage

### Running the Shell

After building, run the shell:

```bash
./shell
```

You'll see the shell prompt:

```
$ 
```

### Example Commands

```bash
$ pwd
/home/user/shell-c

$ echo Hello, World!
Hello, World!

$ type echo
echo is a shell builtin

$ type ls
ls is /usr/bin/ls

$ cd /tmp

$ pwd
/tmp

$ cd ~

$ ls -la
# Lists files in home directory

$ exit 0
```

## Project Structure

```
shell-c/
├── app/
│   └── main.c          # Main shell implementation
├── .codecrafters/      # CodeCrafters configuration
│   ├── compile.sh      # Remote compilation script
│   └── run.sh          # Remote execution script
├── codecrafters.yml    # CodeCrafters configuration file
├── your_program.sh     # Local build and run script
└── README.md           # This file
```

## Technical Details

### Implementation Highlights

- **Command Parsing**: Uses `strtok()` for tokenizing input and separating commands from arguments
- **PATH Resolution**: Searches through PATH environment variable to locate external executables
- **Process Management**: Creates child processes with `fork()` and executes programs with `execvp()`
- **Quote Handling**: Supports both single (`'`) and double (`"`) quoted strings for arguments
- **Directory Navigation**: Implements `cd` with support for home directory (`~`) expansion

### Code Structure

The shell uses an enum-based command dispatcher:
- Commands are identified and mapped to enum values
- A switch statement handles execution of built-in commands
- Default case handles external program execution

## Development

This project was created as part of the CodeCrafters "Build Your Own Shell" challenge. The implementation progressively adds features:

1. Basic REPL (Read-Eval-Print Loop)
2. Built-in commands (exit, echo, type)
3. External program execution
4. Directory navigation (pwd, cd)
5. Argument and quote handling

## Contributing

Feel free to fork this repository and submit pull requests for improvements or bug fixes.

## License

This project is available as open source for educational purposes.

## Acknowledgments

- Built as part of the [CodeCrafters](https://codecrafters.io/) "Build Your Own Shell" challenge
- Inspired by common UNIX shells like bash and sh
