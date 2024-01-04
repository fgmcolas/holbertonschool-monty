#include "monty.h"

/**
 * main - Monty interpreter main function
 * @argc: Argument count
 * @argv: Argument values
 * Return: 0 on success, 1 on failure
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t line_number = 0, len = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		error_usage();
	}

	instruction_t opcodes[] = {
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{NULL, NULL},
	};

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		error_file_open(argv[1]);
	}
	while (getline(&line, &len, file) != -1)
	{
		process_line(line, &stack, ++line_number, opcodes);
		free(line);
		line = NULL;
	}

	free_dlistint(stack);
	fclose(file);
	free(line);

	return (EXIT_SUCCESS);
}

/**
 * push - Pushes an element onto the stack
 * @stack: Pointer to the stack
 * @value: Value to be pushed onto the stack
 */

void push(stack_t **stack, int value)
{
	stack_t *new_node;

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * free_dlistint - function that frees a list
 * @stack: pointer to free tmp
 * Return: void
 */

void free_dlistint(stack_t *stack)
{
	stack_t *tmp;

	while (stack != NULL)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}

/**
 * dlistint_len - function that returns the number of elements in a linked list
 * @stack: pointer to the counter nodes
 * Return: the numbers of nodes
 */

size_t dlistint_len(const stack_t *stack)
{
	size_t i = 0;
	const stack_t *actual = stack;

	while (actual != NULL)
	{
		actual = actual->next;
		i++;
	}
	return (i);
}

/**
 * sum_dlistint - function that adds the top two elements of the stack
 * @stack : pointer to list
 * Return: sum of top two elements or the stack
 */

int sum_dlistint(stack_t *stack)

{
	int sum = 0, i = 0;

	stack_t *current = stack;

	while (i < 2)
	{
		sum += current->n;
		current = current->next;
		i++;
	}
	return (sum);
}
