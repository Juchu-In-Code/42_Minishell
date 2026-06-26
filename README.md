*This project has been created as part of the 42 curriculum by viaremko, jgalizio.*

# Minishell

## Description

**Minishell** is a simplified UNIX shell developed as part of the 42 curriculum. The goal of the project is to understand how command-line interpreters work by recreating the core behavior of Bash, including command execution, process management, pipes, redirections, environment handling, and signal management.

The project focuses on low-level system programming using C and UNIX system calls, providing practical experience with processes, file descriptors, parsing, and memory management.

---

## Features

### Command Execution

* Interactive shell prompt
* Working command history
* Search executables using the `PATH` environment variable
* Execute commands using relative or absolute paths

### Parsing

* Single quotes (`'`) handling
* Double quotes (`"`) handling
* Environment variable expansion (`$VAR`)
* Exit status expansion (`$?`)
* Ignores unsupported syntax such as unclosed quotes, `\`, and `;`

### Redirections

* Input redirection (`<`)
* Output redirection (`>`)
* Append redirection (`>>`)
* Here-document (`<<`)

### Pipes

* Support for pipelines using the `|` operator

### Environment

* Environment variable expansion
* Environment variable management

### Built-in Commands

* `echo -n`
* `cd`
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

### Signal Handling

* `Ctrl-C` displays a new prompt
* `Ctrl-D` exits the shell
* `Ctrl-\` is ignored in interactive mode
* Uses a single global variable exclusively for received signal numbers, in accordance with the project subject

---

## Instructions

### Requirements

* GCC or Clang
* GNU Make
* Readline library

### Compilation

```bash
make
```

### Clean object files

```bash
make clean
```

### Remove all generated files

```bash
make fclean
```

### Recompile

```bash
make re
```

### Run

```bash
./minishell
```

Example:

```bash
minishell$ echo Hello, World!
Hello, World!

minishell$ ls -la | grep minishell > output.txt
```

---

## Learning Objectives

This project explores:

* UNIX processes (`fork`, `execve`, `wait`)
* Pipes and inter-process communication
* File descriptor management
* Parsing command-line input
* Signal handling
* Environment variables
* Memory management
* Building an interactive shell

---

## Resources

### Documentation

* Bash Manual

  * https://www.gnu.org/software/bash/manual/

* POSIX Shell Command Language

  * https://pubs.opengroup.org/onlinepubs/9699919799/

* Linux Programmer's Manual

  * https://man7.org/linux/man-pages/

* Readline Library Documentation

  * https://tiswww.case.edu/php/chet/readline/rltop.html

* The Linux Programming Interface

  * Michael Kerrisk

* Advanced Programming in the UNIX Environment

  * W. Richard Stevens & Stephen A. Rago

---

## AI Usage

Artificial Intelligence tools were used as development assistants throughout this project.

They were primarily used for:

* Clarifying the behavior of Bash and POSIX shell features
* Explaining system calls and UNIX concepts
* Reviewing algorithms and implementation ideas
* Debugging specific issues
* Improving code readability and documentation
* Writing and polishing this README

All design decisions, implementation, testing, and debugging were carried out by the project authors.

---

## Authors

* **viaremko**
* **jgalizio**
