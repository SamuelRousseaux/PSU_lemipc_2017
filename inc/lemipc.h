/*
** EPITECH PROJECT, 2018
** lemipc
** File description:
** lemipc.h
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

# define SUCCESS 0
# define FAIL 84
# define MAP_X 10
# define MAP_Y 10
# define MAP_SIZE (MAP_X * MAP_Y * sizeof(int *))

# define RED	"\e[41m\e[97m"
# define GRN	"\e[42m\e[97m"
# define YEL	"\e[43m\e[97m"
# define BLU	"\e[44m\e[97m"
# define MAG	"\e[45m\e[97m"
# define CYN	"\e[46m\e[97m"
# define RST	"\e[0m"
# define LEADER_DEAD -1

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

typedef enum { false, true } bool;

typedef struct s_my_msg
{
	long mtype;
	char str[32];
} t_my_msg;

typedef struct	s_soldier
{
	int	team_number;
	char	*path;
	key_t	f_key;
	int	pos_x;
	int	pos_y;
	bool	is_alive;
	int	semid;
	int	shmid;
	int	msgid;
	bool	host;
	int	**field;
	int	leader;
}		soldier_t;

int check_if_alive(soldier_t *);
int check_nb_team(soldier_t *);
int fill_map(soldier_t *);
int get_map(soldier_t *);
int get_msg(soldier_t *);
int get_sem(soldier_t *);
int init_battle(char **, soldier_t *);
void lock_sem(soldier_t *);
void move(soldier_t *);
int nb_player(soldier_t *);
int place_soldier(soldier_t *);
void print_map(soldier_t *);
void unlock_sem(soldier_t *);
void send_msg(soldier_t *, char *);
void rcv_msg(soldier_t *);
void rand_mov(soldier_t *);
void right_left(soldier_t *);
void down_up(soldier_t *);
void try_move(int, int, soldier_t *);

#endif /*!LEMIPC_H_*/
