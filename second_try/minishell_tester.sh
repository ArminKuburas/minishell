# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    minishell_tester.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 12:36:22 by akuburas          #+#    #+#              #
#    Updated: 2024/05/15 13:13:13 by akuburas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
NC='\033[0m'

echo -e "${YELLOW}Compiling minishell...${NC}"
make -C ../
echo -e "${YELLOW}Compiling tester...${NC}"

echo -e "${YELLOW}Running tests...${NC}"

function user_chose_no ()
{
	while true; do
		printf "${YELLOW}Do you want to clean up? (y/n)${NC}"
	read answer
	case $answer in
		[Yy]* ) echo -e "${RED}Exiting...${NC}"; exit;;
		[Nn]* ) echo -e "${RED}Exiting...${NC}"; rm -rf test_files; exit 1;;
		* ) echo "Please answer y or n.";;
	esac
	done
	exit
}


function run_test ()
{
	local test_name=$1
	local test_explanation=$2
	local test_file=$4

	echo -e "${YELLOW}Running test: ${test_name}${NC}"
	echo -e "${CYAN}${test_explanation}${NC}"
	echo -e "${CYAN}running minishell with file: ${test_file}${NC}"
	eval "./minishell < ${test_file}"
	echo -e "${GREEN}Test done!${NC}"
	echo -e "${CYAN}Now lets run the same test file in bash${NC}"
	eval ${test_file}
	echo -e "${GREEN}Test done!${NC}"
	while true; do
		printf "${YELLOW}Do you want to continue to the next test? (y/n)${NC}"
	read answer
	case $answer in
		[Yy]* ) break;;
		[Nn]* ) 
		* ) echo "Please answer y or n.";;
	esac
	done
}

mkdir test_files
touch test_files/simple_commands.sh
echo "ls" > test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo "echo hello" >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo "echo hello world" >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'echo $PWD' >> test_files/simple_commands.sh
echo 'ps' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'ls -l' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'ls -l -a' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'pwd' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'env' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'export TEST=hello' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'echo $TEST' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'unset TEST' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'echo $TEST' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'mkdir test' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'cd test' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'cd ..' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh
echo 'rmdir test' >> test_files/simple_commands.sh
echo 'echo $?' >> test_files/simple_commands.sh

run_test "Simple commands" "This test will be running a few basic commands as well as some of the builtins." test_files/simple_commands.sh
echo -e "${YELLOW}Cleaning up...${NC}"
echo -e "${GREEN}All tests done!${NC}"