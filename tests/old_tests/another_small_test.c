/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_small_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:08:22 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/27 10:08:24 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    // Initialize Readline
    rl_bind_key('\t', rl_insert);

    while (1) {
        // Prompt user and read input
        input = readline("Enter a command (type 'exit' to quit): ");

        // If the input is NULL, the user pressed Ctrl+D (EOF), so exit
        if (!input) {
            printf("\nExiting...\n");
            break;
        }

        // If the input is not empty, handle the command
        if (*input) {
            // Print the entered command
            printf("You entered: %s\n", input);

            // Replace the line with "New text" and redisplay
            rl_replace_line("New text", 0);
            rl_redisplay();

            // Free memory allocated by readline
            free(input);
        }
    }

    return 0;
}