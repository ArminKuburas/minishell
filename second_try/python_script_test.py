# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    python_script_test.py                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 13:38:22 by akuburas          #+#    #+#              #
#    Updated: 2024/05/15 16:22:31 by akuburas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import subprocess

def run_process(executable, commands):
    if executable == 'bash':
        formatted_output = ""
        for command in commands:
            # Run the command in a subshell and capture its output
            cmd_output = subprocess.Popen(
                f'{command}',
                shell=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                executable='/bin/bash'
            )
            stdout, stderr = cmd_output.communicate()
            exit_status = cmd_output.returncode
            # Format the output
            formatted_output += f"bash: {command}\n"
            if stdout:
                formatted_output += stdout
            if stderr:
                formatted_output += stderr
            formatted_output += f"Exit status: {exit_status}\n"
        return formatted_output, None
    else:
        process = subprocess.Popen(
            [executable], 
            stdin=subprocess.PIPE, 
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,  # Merge stdout and stderr
            text=True
        )
        input_data = '\n'.join(commands) + '\n'
        output, _ = process.communicate(input=input_data)
        return output, None

def compare_outputs(minishell_output, bash_output):
    print("---- minishell output ----")
    print(minishell_output)
    print("--------------------------")
    print("------ bash output -------")
    print(bash_output)
    print("--------------------------")
    input("Press Enter to continue to the next set of commands...")

def run_tests(command_sets):
    for commands in command_sets:
        print(f"Running command set: {commands}")

        # Run the commands in minishell
        minishell_output, _ = run_process('./minishell', commands)

        # Run the commands in bash
        bash_output, _ = run_process('bash', commands)

        # Compare the outputs
        compare_outputs(minishell_output, bash_output)

# List of command sets to test
command_sets = [
    ["< doesnt_exist echo hello", "echo $?"],
    ["echo hello", "echo world", "echo $?"],
    ["ls", "pwd", "echo $?"],
    ["whoami", "date", "echo $?"],
	["commant_doesnt_exist", "echo $?"],
	["cd /", "pwd"],
	["touch test_file", "ls", "rm test_file", "ls"],
	["touch no_permission", "chmod 000 no_permission", "ls", "echo hello > no_permission", "echo $?" ,"cat no_permission", "echo $?", "chmod 777 no_permission", "rm no_permission"],
	["echo hello > test_file", "cat test_file", "rm test_file"],
	["Makefile > grep NAME | cat -e"],
	[" < Makefile echo hello > test_file", "cat test_file", "rm test_file"],
	["cd ..", "pwd", "cd ..", "pwd", "cd ..", "pwd"],
	
]

# Run the tests
run_tests(command_sets)
