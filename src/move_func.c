/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** move_func.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lemipc.h"

void down_up(soldier_t *soldier)
{
	if (soldier->pos_y < MAP_Y / 2)
		try_move(0, 1, soldier);
	else if (soldier->pos_y > MAP_Y / 2)
		try_move(0, -1, soldier);
}

void right_left(soldier_t *soldier)
{
	if (soldier->pos_x < MAP_X / 2)
		try_move(1, 0, soldier);
	else if (soldier->pos_x > MAP_X / 2)
		try_move(-1, 0, soldier);
}

void rand_mov(soldier_t *soldier)
{
	int x_rdn = rand() % 2;
	int y_rdn = rand() % 2;

	try_move(x_rdn, y_rdn, soldier);
}
