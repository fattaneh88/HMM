#include "Comm.h"

int newsockfd, sockfd;

void connection(int idserver)
{
	//client
	if(idserver == 1)
	{
		struct sockaddr_in serv_addr;

		sockfd = socket(AF_INET, SOCK_STREAM, 0);

		if (sockfd < 0)
		{
			perror("ERROR opening socket");
		}

		if (server == NULL)
		{
			fprintf(stderr, "ERORR, no such host\n");
		}

		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;

		bcopy((char *) server-> h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

		serv_addr.sin_port = htons(portno);

		if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0)
		{
			perror("ERROR connecting");
		}
		gettimeofday(&t0, 0);
	} 
	// server
	else
	{
		int clilen;
		struct sockaddr_in serv_addr, cli_addr;

		sockfd = socket(AF_INET, SOCK_STREAM, 0);

		if (sockfd < 0)
		{
			perror("ERROR opening socket");
		}

		bzero((char *) &serv_addr, sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);
		
		if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		{
			perror("ERROR on binding");
		}

		listen(sockfd, 1);
		clilen = sizeof(cli_addr);

		newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
		{
			perror("ERROR on accept");
		}
		gettimeofday(&t0, 0);

	}

	return;
}

int sending(big *data, int num)
{
	char buffer [length*num];
	bzero(buffer, length*num);
	int n, len, i, bytes_read, bytes_write;
	signal(SIGPIPE, SIG_IGN);

	len = big_to_bytes(length, data[0], buffer, TRUE);

	i = 1;
	while (i < num)
	{	
		len = big_to_bytes(length, data[i], buffer + i *length, TRUE);
		i++;
	}

	bytes_read = sizeof(buffer);
	bytes_write = 0;
    	while (bytes_read > 0) {
		if (idserver == 1)
			n = write(sockfd, buffer + bytes_write, sizeof(buffer) - bytes_write);
		else 
			n = write(newsockfd, buffer + bytes_write, sizeof(buffer) - bytes_write);
		if (n < 0)
		{
				perror("ERROR writing to socket");
		}

		bytes_read -= n;
		bytes_write += n;		
        }
   	
	return n;
}

big* receive(int num)
{
	char buffer[length*num];
	bzero(buffer, length*num);
	int n, i, bytes_read, bytes_write;
	signal(SIGPIPE, SIG_IGN);
	big *data = malloc(((K/4)+1)*num);

	bytes_read = length*num;
	bytes_write = 0;
    	while (bytes_read > 0) {
		if (idserver == 1)
			n = read(sockfd, buffer + bytes_write, length*num - bytes_write);
		else 
			n = read(newsockfd, buffer + bytes_write, length*num - bytes_write);
		if (n < 0)
		{
			error("ERROR reading from socket");
		}

		bytes_read -= n;
		bytes_write += n;		
        }

	data[0] = mirvar(0);
	bytes_to_big(length, buffer, data[0]);

	i = 1;
	while (i < num)
	{
		data[i] = mirvar(0);
		bytes_to_big(length, buffer + i * length, data[i]);
		i++;
	}

	return data;
}

void printnum(big n)
{
   	char number[length];
   	int len, i;
   	len = big_to_bytes(length, n, number, FALSE);
   	printf("%d %d ", numdig(n), len);
   	for (i = 0; i < len; i++) 
	{
      		printf("%02x", number[i] & 0xff);
   	}  
   	printf("\n"); 

   	return;  
}

void initializer(void)
{
	miracl *mip;
	mip = mirsys(2*K+1, 2);
    	mip->NTRY=100;
	length = ((2*K+1)/8)+1;

	return;
}
