#!/bin/bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -o hsh *.c
if [ $? -ne 0 ]; then
	echo "Compilation failed"
	exit 1
fi
# Fonction pour exécuter une commande sur les deux shells
# et comparer les résultats
test_command() {
	command="$1"
	echo "Testing command: $command"

	# Exécute la commande sur votre shell personnalisé
	custom_output=$(echo "$command" | ./hsh 2>&1)
	custom_exit_code=$?

	# Exécute la commande sur sh
	sh_output=$(echo "$command" | sh 2>&1)
	sh_exit_code=$?

	# Compare les sorties
	if [ "$custom_output" = "$sh_output" ]; then
		echo "Output: MATCH"
	else
		echo "Output: MISMATCH"
		echo "Custom shell output:"
		echo "$custom_output"
		echo "Standard sh output:"
		echo "$sh_output"
	fi

	# Compare les codes de sortie
	if [ $custom_exit_code -eq $sh_exit_code ]; then
		echo "Exit code: MATCH ($custom_exit_code)"
	else
		echo "Exit code: MISMATCH (Custom: $custom_exit_code, sh: $sh_exit_code)"
	fi

	echo "----------------------------------------"
}

# Liste des commandes à tester
commands=(
	"ls"
	"pwd"
	"date"
	"lm"
	"ls non_existent_directory"
	"./non_existent_command"
	"ls -poykjghfui"
	"ls -l"
	"/bin/ls"
	"cat /etc/passwd"
	"grep root /etc/passwd"
	"/hgdsk"
	"echo Hello, World!"
	"pwd"
	"cat /etc/passwd"
	"nonexistent_command"
	"ls -l /tmp"
	"echo $PATH"
	"exit 42"
	"cd /tmp"
	"cd -"
	"cd"
	"cd .."
	"cd ~"
	"echo mano # comment"
	"ls ; ls"
	"env"
	"exit"
	"ls -l ; pwd ; echo Hello"

)

# Exécute les tests pour chaque commande
for cmd in "${commands[@]}"; do
	test_command "$cmd"
done
