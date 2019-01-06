/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** msg_func.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lemipc.h"

void rcv_msg(soldier_t *soldier)
{
	t_my_msg buff;

	msgrcv(soldier->msgid, &buff, sizeof(buff),
		soldier->team_number, IPC_NOWAIT);
}
void send_msg(soldier_t *soldier, char *str)
{
	t_my_msg buff;

	bzero(&buff, sizeof(buff));
	buff.mtype = soldier->team_number;
	sprintf(buff.str, "%s", str);
	msgsnd(soldier->msgid, &buff, sizeof(buff), 0);
}
