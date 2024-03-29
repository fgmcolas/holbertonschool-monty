#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */

typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *stack;

void process_line(char *line, stack_t **stack, unsigned long int line_number, instruction_t opcodes[]);

void push(stack_t **stack, int value);
void pall(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
void nop(stack_t **stack, unsigned int line_number);

void free_dlistint(stack_t *stack);
int sum_dlistint(stack_t *stack);
size_t dlistint_len(const stack_t *stack);
int delete_dnodeint_at_index(stack_t **stack, unsigned int index);
void invalid_inst(unsigned long line_number, const char *opcode,
		FILE *file, char *line, stack_t *stack);
void error_usage(void);
void error_file_open(const char *filename);
void push_integer(void);
void print_push_error(unsigned long line_number, FILE *file, char *line);

#endif
