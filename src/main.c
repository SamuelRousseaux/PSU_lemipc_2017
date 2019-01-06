/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** main
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "lemipc.h"

void help(void)
{
	printf("USAGE\n");
	printf("\t./lemipc PATH TEAM_NUMBER\n\n");
	printf("DESCRIPTION\n");
	printf("\tPATH\t\tpath you'll give to ftok\n");
	printf("\tTEAM_NUMBER\tteam number of the current champion");
	printf(" (greater than 0)\n");
}

void kill_soldier(soldier_t *soldier)
{
	lock_sem(soldier);
	soldier->is_alive = false;
	soldier->field[soldier->pos_y][soldier->pos_x] = 0;
	send_msg(soldier, "ARGUE");
	unlock_sem(soldier);
}

int end(soldier_t *soldier)
{
	if (shmget(soldier->f_key, MAP_SIZE, SHM_R | SHM_W) == -1)
		return (1);
	return (0);
}

int game_loop(soldier_t *soldier)
{
	while (!check_nb_team(soldier)) {
		if (soldier->host)
			print_map(soldier);
		move(soldier);
		usleep(100000);
	}
	while ((soldier->is_alive && check_nb_team(soldier) && !end(soldier))
		|| soldier->host) {
		if (soldier->host) {
			print_map(soldier);
			if (!check_nb_team(soldier))
				return (1);
		}
		if (check_if_alive(soldier))
			move(soldier);
		else
			kill_soldier(soldier);
		usleep(100000);
	}
	return (1);
}

int main(int argc, char **argv)
{
	soldier_t soldier;

	srand(getpid());
	if (argc == 1 || !strcmp(argv[1], "--help") || argc != 3) {
		help();
		return (0);
	}
	if (!init_battle(argv, &soldier)) {
		if (soldier.host) {
			shmctl(soldier.shmid, IPC_RMID, 0);
			semctl(soldier.shmid, IPC_RMID, 0);
		}
		return (84);
	}
	game_loop(&soldier);
	if (soldier.host) {
		shmctl(soldier.shmid, IPC_RMID, 0);
		semctl(soldier.shmid, IPC_RMID, 0);
	}
	return (0);
}
