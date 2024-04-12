/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_readline_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:46:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/27 10:54:27 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HISTORY_FILE ".command_history"

int main() {
    char *input;

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

        // Clear history and replace line with a new text
		rl_on_new_line();
        rl_replace_line("New text", 0);
        rl_redisplay();

        // Free the memory allocated by readline
        free(input);
    }
	rl_clear_history();
    return 0;
}
