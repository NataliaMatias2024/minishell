*This project has been created as part of the 42 curriculum by nmatias, mkitano.*

# Minishell

Minishell is a project from the 42 curriculum that consists of recreating a simplified version of a Unix shell.
The objective is to understand how command interpreters work internally by implementing parsing, process management, pipes, redirections, and environment variable handling.

The project is written entirely in **C** and follows the strict coding standards required by the 42 school.

---

# Description

Minishell replicates the fundamental behavior of **bash** in an interactive environment.

The program displays a prompt, reads user input, parses the command line, and executes commands using system calls. The objective of the project is to understand how a shell interprets and executes commands internally.

Through this project we explore concepts such as:

* process creation (`fork`)
* program execution (`execve`)
* file descriptors
* pipes and redirections
* environment variables
* signal handling
* memory management

The internal flow of the program follows this general pipeline:

```
input → lexer → parser → AST → executor
```

---

## Lexer (Tokenization)

The lexer reads the raw input string and splits it into **tokens**, which represent meaningful elements of the command line.

Tokens may include:

* commands
* arguments
* pipes (`|`)
* redirections (`<`, `>`, `>>`, `<<`)
* environment variables
* quoted strings

Example input:

```
echo hello | grep h > file.txt
```

Tokenized representation:

```
[echo] [hello] [|] [grep] [h] [>] [file.txt]
```

This step transforms the raw string into a structured sequence that can be interpreted by the parser.

---

## Parser

After tokenization, the parser analyzes the token sequence and builds a structured representation of the command line.

In many minishell implementations, this structure can be represented as a **binary tree** or command nodes, where operators define the relationship between commands.

Example command:

```
echo hello | grep h
```

Conceptual representation:

```
       PIPE
      /    \
   echo    grep
```

The parser also associates **redirections** with their corresponding commands and prepares the data structures that will later be used during execution.

---

## Execution

Once the command structure is built, the executor runs the commands according to their relationships.

Execution typically involves system calls such as:

* `fork` to create child processes
* `pipe` to connect commands
* `dup2` to handle file descriptor redirections
* `execve` to exec

---

# Project Structure

```
minishell/
│
├── includes/        # Header files
├── srcs/            # Source code
│   ├── lexer/
│   ├── parser/
│   ├── executor/
│   ├── builtins/
│   └── signals/
│
├── libft/           # Custom C utility library
├── Makefile
└── README.md
```

---

# Instructions

## Clone the repository

```bash
git clone https://github.com/mkitano/minishell.git
cd minishell
```

## Compile the project

```bash
make
```

## Run minishell

```bash
./minishell
```

---

# Example Usage

```
minishell$ echo Hello
Hello

minishell$ export NAME=42
minishell$ echo $NAME
42

minishell$ ls -l | grep minishell
```

---

# Resources

References used during the development of this project:

* GNU Bash documentation
* Linux manual pages (`man execve`, `man fork`, `man pipe`, `man dup2`)
* The Linux Programming Interface — Michael Kerrisk
* Playlist https://github.com/lbento/minishell.git
* Shell Program https://www.youtube.com/watch?v=ubt-UjcQUYg&t=498s
* Playlist Data Structures https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P

### AI Usage

AI tools were used to:

* clarify system call behavior
* review conceptual explanations

