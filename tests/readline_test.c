/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:14:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/28 13:26:57 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HISTORY_FILE ".command_history"

int main() {
    char *input;
	char *input2;

    // Load command history from file
    read_history(HISTORY_FILE);

    while (1) {
        // Read input from the user using readline
        input = readline(">> ");

        // If the input is NULL, the user pressed Ctrl+D (EOF)
        if (!input) {
            printf("\nExiting...\n");
            break;
        }

        // If the input is not empty, add it to the history
        if (*input) {
            add_history(input);
            // Save command history to file after each command
            write_history(HISTORY_FILE);
        }

        // Display the entered command
        printf("You entered: %s\n", input);

        // Free the memory allocated by readline
        free(input);
    }

    return 0;
}