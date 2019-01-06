/*
** EPITECH PROJECT, 2018
** *
** File description:
** *
*/


#include "lemipc.h"

int get_msg(soldier_t *soldier)
{
	soldier->msgid = msgget(soldier->f_key, SHM_R | SHM_W);
	if (soldier->msgid == -1) {
		soldier->msgid = msgget(soldier->f_key, IPC_CREAT |
					SHM_R | SHM_W);
		if (soldier->msgid == -1)
			return (0);
	}
	return (1);
}

int get_sem(soldier_t *soldier)
{
	soldier->semid = semget(soldier->f_key, 1, SHM_R | SHM_W);
	if (soldier->semid == -1) {
		soldier->semid = semget(soldier->f_key, 1,
					IPC_CREAT | SHM_R | SHM_W);
		if (soldier->semid == -1)
			return (0);
		if (semctl(soldier->semid, 0, SETVAL, 1) == -1)
			return (0);
	}
	else if (soldier->host)
		if (semctl(soldier->semid, 0, SETVAL, 1) == -1)
			return (0);
	return (1);
}
