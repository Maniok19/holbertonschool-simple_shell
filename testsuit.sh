#!/bin/bash

# Fonction pour exécuter une commande sur les deux shells et comparer les résultats
test_command() {
    command="$1"
    echo "Testing command: $command"
    
    # Exécute la commande sur votre shell personnalisé
    custom_output=$(echo "$command" | ./shell 2>&1)
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
    "lm"
    "ls -poyui"
    "/bin/ls"
    "/hgdsk"
    "echo Hello, World!"
    "pwd"
    "cat /etc/passwd"
    "nonexistent_command"
    "ls -l /tmp"
    "ls | grep .txt"
    "echo $PATH"
    "cd /tmp && pwd"
    "exit 42"
)

# Exécute les tests pour chaque commande
for cmd in "${commands[@]}"; do
    test_command "$cmd"
done