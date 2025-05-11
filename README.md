# 🐚 Minishell
### A feature-complete POSIX shell implemented in C

---

## 📝 Overview

A fully functional shell built in C for the 42 curriculum, replicating key behaviors of `bash`.  
Supports job control, command parsing, environment management, expansions, and built-in commands.  
All logic written from scratch with a custom lexer, parser, and executor architecture.

---

## DISCLAIMER 
This is a Show Repository. The original we worked on is [here]. (https://https://github.com/42mgr/42minishell)

---

## ✨ Features

- 🧠 **Custom Lexer & Parser**  
  Built from scratch to tokenize, parse, and construct abstract syntax trees.

- ⚙️ **Execution Engine**  
  Executes commands with pipelines, logical ops (`&&`, `||`), redirections, and subshells.

- 🧩 **Built-in Commands**  
  Fully re-implemented: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`.

- 🔄 **Environment Variable Handling**  
  Robust `getenv`, `setenv`, and `unsetenv` functionality.

- 🔍 **Word & Parameter Expansion**  
  Handles variables (`$VAR`), wildcards (`*`) and quotes.

- 🗃️ **Redirection & Pipes**  
  Supports `<`, `>`, `>>`, heredocs (`<<`), and multi-command pipelines.

- 📡 **Signal Handling**  
  Handling of `SIGINT`, `SIGQUIT`.

- 🧪 **Robust Error Handling**  
  Error messages, status codes, and edge case coverage.

- 🧠 **Bonus Features**  
  Includes subshells, command chaining, multi-line prompts, and more.

---

## 🚀 How to Run

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
make
./minishell
```

---

## ⚙ Command Syntax Overview
<details> <summary>🛠 Click to expand</summary>

```bash
echo "Hello, $USER"
ls -al | grep minishell
cat << EOF
This is a heredoc
EOF

export PATH=$PATH:./bin
(cd srcs && ls)
```
| Built-Ins   | Explanation                            |
|-------------|----------------------------------------|
| `cd`        | Change the current directory           |
| `export`    | Set an environment variable            |
| `echo`      | Print text to the terminal             |
| `exit`      | Exit the shell                         |
| `pwd`       | Print working Dir                      |
| `unset`     | Unset Env Variable                     |
| `env`       | Prints Enviorment                      |

</details>

---

## 📁 Project Structure

```plaintext
minishell/
├── include/              → Header files
│   ├── minishell.h       → Main includes
│   ├── lexer.h           → Lexer logic
│   ├── parser.h          → Parser logic
│   ├── ms_executer.h     → Command execution
│   ├── ms_env.h          → Environment handling
│   ├── ms_build_ins.h    → Built-in commands
│   ├── ms_expander.h     → Variable and wildcard expansion
│   └── ms_signal.h       → Signal handling
├── libft-42/             → Custom standard library functions
│   └── libft.h, *.c
├── srcs/
│   ├── lexer/            → Tokenization logic
│   ├── parser/           → Command tree builder
│   ├── executer/         → Execution engine
│   ├── env/              → Environment logic
│   ├── build_ins/        → Built-in implementations
│   ├── expander/         → Variable/wildcard expansion
│   ├── signal/           → Signal handlers
│   ├── readline/         → Prompt handling
│   ├── error/            → Error messages
│   └── main.c            
├── Makefile              
└── README.md             
```

## 👨‍💻 Authors
- [@42mgr](https://github.com/42mgr)
- [@bartsch-tech](https://github.com/bartsch-tech)
