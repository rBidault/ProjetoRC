#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

void erro(char *msg);

int main() {
  char endServer[100], buffer[BUF_SIZE];
  int fd, client, nread;
  struct sockaddr_in addr, client_addr;
  int client_addr_size;
  struct hostent *hostPtr;
  char login[20], pw[20];
  char app[] = "admin";
  int check=1;
  

  bzero((void *) &addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(9000);


  if((fd = socket(AF_INET,SOCK_STREAM,0)) == -1){
	  erro("socket");
  }
  if( connect(fd,(struct sockaddr *)&addr,sizeof (addr)) < 0){
	  erro("Connect");
  }
  printf("Bem vindo à aplicação do Gestor de Aplicacao.\n");
  write(fd, app, strlen(app));
  memset(buffer,0,strlen(buffer));
	printf("Introduza o seu Login: ");
  fgets(login,20,stdin);
  login[strcspn(login, "\n")] = 0;
  printf("Introduza a sua Password: ");
  fgets(pw,20,stdin);
  pw[strcspn(pw, "\n")] = 0;
  strcat(buffer,login);
	strcat(buffer," ");
	strcat(buffer,pw);
	write(fd, buffer, strlen(buffer));
  memset(buffer,0,strlen(buffer));
  nread = read(fd, buffer, BUF_SIZE-1);		
	buffer[nread] = '\0';

	check=strcmp(buffer,"0");
  if (check==0){
    erro("Utilizador não existe!");
  }
  
	memset(buffer,0,strlen(buffer)); 
	
	printf("\nSeguranca na Saude: Gestor de Aplicacao\n");


  fflush(stdout);
  close(fd);
}

void erro(char *msg)
{
	printf("Erro: %s\n", msg);
	exit(-1);
}

