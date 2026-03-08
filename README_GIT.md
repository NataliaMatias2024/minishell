# Minishell - @42SP

## 📖 About the Project
Minishell is a project at **42 São Paulo** that consists of recreating the functioning of a terminal. The goal is to develop a shell in C that handles command execution, pipes, redirections, and signals, requiring advanced memory management.

---

## 🛠️ Features
* **Prompt:** Displays a functional prompt waiting for user input. 🟡 Under Development
* **Command Execution:** Search and launch executables based on the `PATH`. 🟡 Under Development
* **Built-ins:** `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`. 🟡 Under Development
* **Redirections:** `<`, `>`, `>>`, and `<<` (heredoc). 🟡 Under Development
* **Pipes:** `|` operator to connect commands. 🟡 Under Development
* **Environment Variables:** Expansion of `$` and `$?`. 🟡 Under Development
* **Signals:** Proper handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`. ⚪ Planned

---

## 🚀 Getting Started

### Installation
1. Clone the repository:
   ```bash
   git clone [https://github.com/NataliaMatias2024/minishell.git](git@github.com:NataliaMatias2024/minishell.git)
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run Minishell:
   ```bash
   ./minishell
   ```

---

## 📂 Project Structure

* **srcs/:** Source files (.c) organized by modules (parsing, execution, built-ins).
* **includes/:** Header files (.h).
* **libft/:** Custom C library with utility functions.
* **.gitignore:** Configuration to keep the repository clean from binaries and system noise.

---

## 👥 Authors

* **Natalia Matias** - Student at 42 São Paulo.
* **Magali Midori** - Student at 42 São Paulo.

---

## 🔄 Development Workflow

To ensure code quality and avoid merge conflicts, we follow a Feature Branch workflow:

1. Sync: Always start by pulling the latest changes **from main**.
	 ```bash
	 git checkout main
	 git pull
	 ```

2. Branch: Create a branch for each feature:
	```bash
	git checkout -b feat/feature-name
	```

3. Add, Commit and Push: Use descriptive messages in English for commits.
	```bash
	git add .
	git commit -m "type: message" (Ex: doc: add initial readme)
	git push origin type/type-name
	```

4. PR: Open a Pull Request on GitHub to merge the feature into main.

5. Review: Review code for memory management and logic before merging.