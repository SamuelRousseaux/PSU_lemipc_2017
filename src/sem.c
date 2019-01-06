/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/

#include "lemipc.h"

void lock_sem(soldier_t *soldier)
{
	struct sembuf buff;

	buff.sem_num = 0;
	buff.sem_flg = 0;
	buff.sem_op = -1;
	semop(soldier->semid, &buff, 1);
}

void unlock_sem(soldier_t *soldier)
{
	struct sembuf buff;

	buff.sem_num = 0;
	buff.sem_flg = 0;
	buff.sem_op = 1;
	semop(soldier->semid, &buff, 1);
}
