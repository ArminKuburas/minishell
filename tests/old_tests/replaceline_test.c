/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replaceline_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:06:04 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/27 10:06:06 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    // Prompt user and read input
    input = readline("Enter a command: ");

    // If the input is not empty, replace the line with "New text"
    if (input) {
        rl_replace_line("New text", 0);
        rl_redisplay();
    }

    // Free memory allocated by readline
    free(input);

    return 0;
}