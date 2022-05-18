/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:58:33 by lchan             #+#    #+#             */
/*   Updated: 2022/04/20 14:22:54 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int id;
	int	id2;
	int	id3;

	id = fork();
	id2 = fork();
	id3 = fork();

	if (id)
	{
		if (id2)
		{
			if (id3)
			{
				printf("PARENT PROCESS : id =%d, id2 = %d and id3 = %d\n", id, id2, id3);
				wait(0);
			}
			else
				printf("PROCESS 3 : id =%d, id2 = %d and id3 = %d\n\n\n", id, id2, id3);
		}
		else 
		{
			if (id3)
			{
				printf("CHILD PROCESS 2 : id =%d, id2 = %d and id3 = %d\n", id, id2, id3);
				wait(0);
			}
			else
				printf("SON OF CPROCESS 2 : id =%d, id2 = %d and id3 = %d\n\n\n", id, id2, id3);
		}
	}
	else
	{
		if (id2)
		{
			if (id3)
			{
				printf("First CHILD PROCESS 1 : id =%d and id2 = %d id3 = %d\n", id, id2, id3);
				wait(0);
			}
			else
				printf("second CHILD PROCESS 1 : id =%d and id2 = %d id3 = %d\n", id, id2, id3);
		}
		else if (id3)
		{
			printf("SON OF CPROCESS 1 : id =%d, id2 = %d and id3 = %d\n", id, id2, id3);
			wait(0);
		}
		else
			printf("GRANDSON of CPROCESS 1 : id =%d,  id2 = %d, id3 = %d\n", id, id2, id3);
	}
}*/
