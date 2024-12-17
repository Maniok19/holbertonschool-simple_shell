# Simple Shell

This project is a simple implementation of a Unix shell. It provides a command-line interface for users to interact with the operating system by executing commands.

## Features

- Execute commands with arguments
- Handle built-in commands
- Environment variable management
- Path resolution for executables

## Files

- `shell.c`: Main file that contains the shell loop and command execution logic.

## Usage

To compile the shell, use the following command:

```sh
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

To start the shell, run:

```sh
./hsh
```

## Example

```sh
$ ./hsh
$ ls -l
$ /bin/ls
$ echo "Hello, world!"
$ exit
```

## Authors

- Mano
- Sebastien

## License

This project is licensed under the MIT License.