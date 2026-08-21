# Minishell

## Description

**Minishell** is a lightweight, POSIX-inspired UNIX shell built from scratch in C. Designed to demonstrate a deep understanding of operating system mechanics, this project recreates the core execution behavior of Bash. 

The development of Minishell required robust systems-level programming, with a heavy focus on process lifecycle management, inter-process communication (IPC) via pipes, strict file descriptor manipulation, and safe signal handling in a continuous runtime environment.

---

## Technical Features

### Command Execution & Process Management
* **Interactive Prompt:** Continuous Read-Eval-Print Loop (REPL) with a working command history.
* **Binary Resolution:** Dynamic executable searching using the `PATH` environment variable, alongside absolute and relative path execution.
* **Process Synchronization:** Orchestration of child processes using `fork`, `execve`, and `waitpid`.

### Parsing & Lexical Analysis
* **Stateful Parsing:** Robust handling of single quotes (`'`) for literal strings and double quotes (`"`) for interpolated strings.
* **Dynamic Expansion:** Environment variable expansion (`$VAR`) and accurate exit status reporting (`$?`).
* **Syntax Validation:** Graceful degradation and error handling for unsupported syntax (e.g., unclosed quotes).

### I/O Redirection & IPC
* **Pipelining:** Full support for chained pipelines (`|`), correctly managing file descriptors across multiple child processes.
* **File Redirections:** Input (`<`), Output (`>`), and Append (`>>`) handling.
* **Here-Documents (`<<`):** Streams multi-line inputs directly into command execution, featuring full support for **in-stream environment variable expansion** (`$VAR` resolution inside the heredoc).

### Built-in Utilities
Engineered modular, custom implementations of core shell commands. These execute directly within the parent process to manipulate the shell's environment state:
* `cd`
* `echo`
* `env`
* `exit`
* `export`
* `pwd`
* `unset`

### Developer Tooling: Interactive Token Debugger
To aid in the development and verification of the lexical analyzer, Minishell features a custom debug mode. Launching the shell with the `-D` flag provides a real-time, visual breakdown of how the input string is sliced into tokens, categorized, and indexed before hitting the execution engine.

**Example:** Processing `ls -la | grep "shell"` in debug mode:

```text
 =================================================
                [ INPUT TOKEN DEBUG ]

ls -la | grep "shell"
^^ STRING -> [ Index: 0 | Size: 2 ]

ls -la | grep "shell"
  ^ SPACE -> [ Index: 2 | Size: 1 ]

ls -la | grep "shell"
   ^^^ STRING -> [ Index: 3 | Size: 3 ]

ls -la | grep "shell"
      ^ SPACE -> [ Index: 6 | Size: 1 ]

ls -la | grep "shell"
       ^ PIPE -> [ Index: 7 | Size: 1 ]

ls -la | grep "shell"
        ^ SPACE -> [ Index: 8 | Size: 1 ]

ls -la | grep "shell"
         ^^^^ STRING -> [ Index: 9 | Size: 4 ]

ls -la | grep "shell"
             ^ SPACE -> [ Index: 13 | Size: 1 ]

ls -la | grep "shell"
              ^^^^^^^ DOUBLE_Q -> [ Index: 14 | Size: 7 ]

 =================================================
-rwxr-xr-x  1 deck deck 227312 Aug 21 12:32 minishell
```

### Signal Management
* Custom handlers for interrupt signals to ensure the shell remains stable and responsive:
  * `SIGINT` (`Ctrl-C`) safely halts the current process and displays a fresh prompt.
  * `EOF` (`Ctrl-D`) gracefully exits the shell, freeing all allocated memory.
  * `SIGQUIT` (`Ctrl-\`) is safely ignored in interactive mode.
* Signal states are managed asynchronously to prevent undefined behavior during execution.

---

## Technical Competencies Demonstrated

Building this interpreter required hands-on application of advanced systems programming concepts:
* **System Calls:** Deep integration with UNIX syscalls for I/O and process control.
* **Memory Management:** Preventing memory leaks and segmentation faults during continuous string manipulation and state changes.
* **Data Structures:** Managing environment variables, command tokens, and execution nodes efficiently in C.
* **Concurrency:** Preventing race conditions and deadlocks when managing multiple file descriptors across piped commands.

---

## Build & Run Instructions

### Requirements
* GCC or Clang compiler
* GNU Make
* Readline library

### Compilation
```bash
make
```

### Execution
```bash
# Standard mode
./minishell

# Debug mode (Lexer visualization)
./minishell -D
```

### Clean Utilities
```bash
# Clean object files
make clean

# Remove all generated files and executables
make fclean

# Full recompile
make re
```

---

## References & Documentation

* **Bash Manual:** [GNU Bash](https://www.gnu.org/software/bash/manual/)
* **POSIX Shell Command Language:** [OpenGroup](https://pubs.opengroup.org/onlinepubs/9699919799/)
* **The Linux Programming Interface** (Michael Kerrisk)
* **Advanced Programming in the UNIX Environment** (W. Richard Stevens & Stephen A. Rago)

---

## AI Usage

Artificial Intelligence tools were utilized as workflow accelerators during this project's development lifecycle. Primary use cases included clarifying POSIX standards, retrieving man-page specifications for UNIX system calls, and refining documentation. All architectural decisions, parsing logic, memory management, and debugging were strictly executed by the project authors.

---

## Authors

* **Julian Galizio**
* **Lody Iaremko**
