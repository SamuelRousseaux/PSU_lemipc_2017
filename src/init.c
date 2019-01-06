/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "lemipc.h"

int is_num(char *nb)
{
	for (int i = 0 ; nb[i] != '\0' ; i++)
		if (nb[i] < '0' || nb[i] > '9')
			return (0);
	return (1);
}

int set_soldier(char **argv, soldier_t *soldier)
{
	if (is_num(argv[2]) && atoi(argv[2])) {
		soldier->team_number = atoi(argv[2]);
		soldier->path = argv[1];
		soldier->f_key = ftok(soldier->path, 0);
		if (soldier->f_key == -1) {
			fprintf(stderr, "Error while getting key: %s\n",
				strerror(errno));
			return (0);
		}
		return (1);
	} else {
		fprintf(stderr, "Error: team isn't a positive number\n");
		return (0);
	}
}


int init_battle(char **argv, soldier_t *soldier)
{
	if (!set_soldier(argv, soldier))
		return (0);
	if (!get_map(soldier))
		return (0);
	if (!get_sem(soldier))
		return (0);
	if (!get_msg(soldier))
		return (0);
	if (!place_soldier(soldier))
		return (0);
	soldier->is_alive = true;
	return (1);
}
