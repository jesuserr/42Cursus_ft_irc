/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t1.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:57:26 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/31 18:54:38 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char **argv)
{
	int listen_sd = -1;
	int on = 1;
	struct sockaddr_in6  iaddr;
	struct pollfd fds[200];
	int    nfds = 1;
	int current_size;
	int new_sd = 1;
	char   buffer[80];
	int rc;
	bool compressfds = false;
	
	if (argc < 2)
	{
		printf("Falta ewl puerto");
		exit(1);
	}
	listen_sd = socket (AF_INET6, SOCK_STREAM, 0);
	if (listen_sd < 0)
	{
		printf("Error: no se ha podido crear un socket\n");
		exit(1);
	}
	if (setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR,
                  (char *)&on, sizeof(on)) < 0)
	{
		printf("Error: No he podido poner el socket con rehusable\n");
		exit (1);
	}
	if (fcntl(listen_sd, F_SETFL, O_NONBLOCK) < 0)
	{
		printf("Error: no he podido poner el socket en modo no bloqueante\n");
		exit(1);
	}
	memset(&iaddr, 0, sizeof(iaddr));
	iaddr.sin6_family = AF_INET6;
	memcpy(&iaddr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	iaddr.sin6_port = htons(atoi(argv[1]));
	
	if (bind(listen_sd, (struct sockaddr *)&iaddr, sizeof(iaddr)) < 0)
	{
		printf("Error: no se ha podido hacer bind\n");
		exit(1);
	}
	
	if (listen(listen_sd, 64) < 0)
	{
		printf("Error: No se ha podido poner el socket a la espera de aceptar conexiones\n");
		exit(1);
	}
	
	memset(fds, 0 , sizeof(fds));
	fds[0].fd = listen_sd;
	fds[0].events = POLLIN;
	while (1)
	{
		if (poll(fds, nfds, -1) < 0)
		{
			printf("Error: error al hacer poll()\n");
			exit(1);
		}
		current_size = nfds;
		for (int c = 0; c < current_size ; c++)
		{
			if(fds[c].revents == 0)
       			continue;
			/*if(fds[c].revents != POLLIN)
			{
				printf("fd:%dError! revents = %d\n", fds[c].fd, fds[c].revents);
				exit(1);
			}*/
			if (fds[c].fd == listen_sd)
      		{
				new_sd = 1;
				while (new_sd != -1)
				{
					new_sd = accept(listen_sd, NULL, NULL);
					if (new_sd < 0 && errno != EWOULDBLOCK)
					{
						printf("Error: al crear el socket para una conexion entrante nueva\n");
						exit(1);
					}
					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++;
				}
			}
			else 
			{
				while(1)
				{
					rc = recv(fds[c].fd, buffer, sizeof(buffer), 0);
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  recv() failed");
							exit(1);
						}
						break;
					}
					if (rc == 0)
					{
						printf("  Connection closed\n");
						fflush(stdout);
						close(fds[c].fd);
          				fds[c].fd = -1;
						compressfds = true;
						break;
					}
					printf("%d: ", fds[c].fd);
					fflush(stdout);
					write(1, buffer, rc);
				}
			}
		}
		if (compressfds)
		{
			compressfds = false;
			for (int i = 0; i < nfds; i++)
			{
				if (fds[i].fd == -1)
				{
					for(int j = i; j < nfds-1; j++)
					{
						fds[j].fd = fds[j+1].fd;
					}
					i--;
					nfds--;
				}
			}
		}
	}
}
