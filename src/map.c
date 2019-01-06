/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdlib.h>
#include <stdio.h>
#include "lemipc.h"

static char *colors[] = { RST, RED, GRN, YEL, BLU, MAG, CYN };

int check_nb_team(soldier_t *soldier)
{
	int nb1 = 0;
	for (int i = 0 ; i < MAP_Y ; i++)
		for (int j = 0 ; j < MAP_X ; j++) {
			if (soldier->field[i][j] != 0 && nb1 == 0)
				nb1 = soldier->field[i][j];
			else if (soldier->field[i][j] != 0 &&
				soldier->field[i][j] != nb1)
				return (1);
		}
	return (0);
}

int nb_player(soldier_t *soldier)
{
	int nb = 0;

	for (int i = 0 ; i < MAP_Y ; i++)
		for (int j = 0 ; j < MAP_X ; j++)
			if (soldier->field[i][j] != 0)
				nb++;
	return (nb);
}

void print_map(soldier_t *soldier)
{
	printf("\nmap: %dx%d\n", MAP_X, MAP_Y);
	for (int i = 0 ; i < MAP_Y ; i++) {
		for (int j = 0 ; j < MAP_X ; j++) {
			if (soldier->field[i][j] != 0)
				printf("%s%d" RST,
					colors[soldier->field[i][j] % 7],
					soldier->field[i][j]);
			else
				printf("%d", soldier->field[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

int fill_map(soldier_t *soldier)
{
	void *data;

	data = shmat(soldier->shmid, NULL, SHM_R | SHM_W);
	if (data == (void *)(-1))
		return (0);
	soldier->field = malloc(MAP_SIZE);
	if (!soldier->field)
		return (0);
	for (int i = 0 ; i < MAP_Y ; i++)
		soldier->field[i] = &((int *)data)[MAP_X * i];
	if (soldier->host) {
		for (int i = 0 ; i < MAP_Y ; i++) {
			for (int j = 0 ; j < MAP_X ; j++)
				soldier->field[i][j] = 0;
		}
	}
	return (1);
}

int get_map(soldier_t *soldier)
{
	soldier->shmid = shmget(soldier->f_key, MAP_SIZE, SHM_R | SHM_W);
	if (soldier->shmid == -1) {
		printf("create\n");
		soldier->shmid = shmget(soldier->f_key, MAP_SIZE,
					IPC_CREAT | SHM_R | SHM_W);
		soldier->host = true;
		if (!fill_map(soldier))
			return (0);
	} else {
		printf("join\n");
		soldier->host = false;
		if (!fill_map(soldier))
			return (0);
	}
	return (1);
}
