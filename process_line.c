#include "monty.h"

/**
 * process_line - Processes a line from a Monty language bytecode file,
 *		  executing the specified opcode.
 * @line: The line from the Monty bytecode file to be processed.
 * @stack: Pointer to the top of the stack.
 * @line_number: The line number in the Monty bytecode file being processed.
 * @opcodes: An array of structures representing Monty language instructions.
 */

void process_line(char *line, stack_t **stack,
		unsigned long int line_number, instruction_t opcodes[])
{
	char *opcode, *value;
	int numeric_value, j;
	size_t len = strlen(line);

	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	opcode = strtok(line, " \t$");
	if (opcode == NULL || opcode[0] == '#')
		return;
	if (strcmp(opcode, "push") == 0)
	{
		value = strtok(NULL, " \t$\n");
		if (value == NULL)
		{
			print_push_error(line_number, stderr, line);
			return;
		}
		for (int i = 0; value[i] != '\0'; i++)
		{
			if (!isdigit(value[i]) && value[i] != '-')
			{
				print_push_error(line_number, stderr, line);
				return;
			}
		}
		numeric_value = atoi(value);
		push(stack, numeric_value);
		return;
	}
	for (j = 0; opcodes[j].opcode != NULL; j++)
	{
		if (strcmp(opcode, opcodes[j].opcode) == 0)
		{
			opcodes[j].f(stack, line_number);
			return;
		}
	}
	fprintf(stderr, "L%lu: unknown instruction %s\n", line_number, opcode);
	free(line);
	exit(EXIT_FAILURE);
}
