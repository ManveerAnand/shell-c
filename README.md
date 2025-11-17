# Shell in C

A simple Unix shell implementation written in C, built as part of the [CodeCrafters Shell Challenge](https://codecrafters.io/challenges/shell).

## Features

This shell implementation supports the following features:

### Built-in Commands
- `exit [code]` - Exit the shell with optional exit code
- `echo <text>` - Print text to standard output
- `type <command>` - Display information about command type (builtin or external)
- `pwd` - Print current working directory
- `cd <directory>` - Change current directory (supports `~` for home directory)

### External Commands
- Execute external programs available in the system PATH
- Support for command arguments
- Process management using fork/exec

## Building

To compile the shell locally:

```bash
gcc app/*.c -o /tmp/shell-target
```

Or use the provided script:

```bash
./your_program.sh
```

## Usage

Run the compiled shell:

```bash
/tmp/shell-target
```

Once the shell is running, you'll see a `$ ` prompt where you can enter commands:

```bash
$ pwd
/home/user/shell-c
$ echo Hello, World!
Hello, World!
$ type echo
echo is a shell builtin
$ type cat
cat is /usr/bin/cat
$ cd ~
$ pwd
/home/user
$ exit 0
```

## Project Structure

```
.
├── app/
│   └── main.c          # Main shell implementation
├── your_program.sh     # Build and run script
├── codecrafters.yml    # CodeCrafters configuration
└── README.md          # This file
```

## Implementation Details

The shell is implemented in C and includes:
- Command parsing and tokenization
- PATH resolution for external commands
- Process creation and management using `fork()` and `exec()`
- Support for both built-in and external commands
- Basic error handling

## Requirements

- GCC compiler
- Unix-like operating system (Linux, macOS, etc.)
- Standard C library

## License

This project is part of the CodeCrafters learning platform.
