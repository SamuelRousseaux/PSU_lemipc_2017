/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include <stdlib.h>
#include <stdio.h>
#include "lemipc.h"

void try_move(int x, int y, soldier_t *soldier)
{
	int nx = soldier->pos_x + x;
	int ny = soldier->pos_y + y;

	lock_sem(soldier);
	if (nx < MAP_X && nx >= 0 && ny < MAP_Y && ny >= 0
	&& soldier->field[ny][nx] == 0) {
		soldier->field[soldier->pos_y][soldier->pos_x] = 0;
		soldier->field[ny][nx] = soldier->team_number;
		soldier->pos_y = ny;
		soldier->pos_x = nx;
	}
	unlock_sem(soldier);
}

void move(soldier_t *soldier)
{
	int rdm = rand() % 3;

	send_msg(soldier, "ALIVE");
	rcv_msg(soldier);
	if (rdm == 0)
		down_up(soldier);
	else if (rdm == 1)
		right_left(soldier);
	else
		rand_mov(soldier);
}

int check_array_enemies(int *enemies)
{
	int save1 = 0;
	int save2;

	for (int j = 0 ; j < 8 ; j++) {
		save2 = 0;
		if (enemies[j] == 0)
			continue;
		for (int z = 0 ; z < 8 ; z++)
			if (enemies[z] == enemies[j])
				save2++;
		save1 = (save2 > save1) ? save2 : save1;
	}
	if (save1 >= 2)
		return (1);
	return (0);
}

int check_if_alive(soldier_t *soldier)
{
	int xpos = soldier->pos_x;
	int ypos = soldier->pos_y;
	int enemies[8] = { 0 };
	int i = -1;

	lock_sem(soldier);
	for (int x = xpos - 1 ; x <= xpos + 1 ; x++)
		for (int y = ypos - 1 ; y <= ypos + 1 ; y++) {
			if (y == ypos && x == xpos)
				continue;
			if (x >= 0 && x < MAP_X && y >= 0 && y < MAP_Y &&
				soldier->field[y][x] != soldier->team_number)
				enemies[++i] = soldier->field[y][x];
		}
	if (check_array_enemies(enemies)) {
		unlock_sem(soldier);
		return (0);
	}
	unlock_sem(soldier);
	return (1);
}

int place_soldier(soldier_t *soldier)
{
	int x = 0;
	int y = 0;

	lock_sem(soldier);
	if (nb_player(soldier) != (MAP_X * MAP_Y)) {
		while (soldier->field[y][x] != 0) {
			x = rand() % MAP_X;
			y = rand() % MAP_Y;
		}
		soldier->pos_x = x;
		soldier->pos_y = y;
		soldier->field[y][x] = soldier->team_number;
	} else {
		printf("There's no room left on this battlefield!\n");
		unlock_sem(soldier);
		return (0);
	}
	unlock_sem(soldier);
	return (1);
}
