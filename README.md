# Simple Shell

## Description
This project is a simple UNIX command interpreter that replicates the basic functionalities of the shell. It reads commands from the user, executes them, and displays the output.

## Features
- Execute commands with arguments
- Handle built-in commands like `exit` and `env`
- Search and execute commands from the PATH environment variable
- Error handling for command execution

## Files
- `shell.c`: Main file that contains the entry point and main loop of the shell.
- `_strcmp.c`: Contains string manipulation functions like `_strcmp`, `_strcat`, `_strcpy`, `_strdup`, and `_strlen`.
- `_strchr.c`: Contains functions `_strchr`, `print_env`, and `_getenv`.
- `shell.h`: Header file with function prototypes and necessary includes.

## Usage
1. Clone the repository:
	```sh
	git clone https://github.com/yourusername/holbertonschool-simple_shell.git
	```
2. Compile the source files:
	```sh
	gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
	```
3. Run the shell:
	```sh
	./hsh
	```

## Built-in Commands
- `exit`: Exit the shell.
- `env`: Print the environment variables.

## Example
```sh
$ ./hsh
$ ls -l
total 8
-rwxrwxr-x 1 user user  0 Oct  1 12:34 file1
-rwxrwxr-x 1 user user  0 Oct  1 12:34 file2
$ env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
HOME=/home/user
$ exit
```

## Authors
- Mano
- Holberton School

## License
This project is licensed under the MIT License.