/*
	APLICAÇÃO AGENTE DE SEGURANÇA (AGS)
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SERVER_PORT     9000
#define BUF_SIZE 1024
char buffer[BUF_SIZE];
char app[] = "security";
char login[20] = "", pw[20] ="";
int fd, nread,op, check=1;
struct sockaddr_in addr;
struct hostent *hostPtr;

void erro(char *msg);
void menu(int fd, char login[20]);
void signIN(int fd);
void signUP(int fd);
void frontPAGE(int fd);

int main() {
  bzero((void *) &addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(SERVER_PORT);

  if((fd = socket(AF_INET,SOCK_STREAM,0)) == -1){
	  erro("socket");
  }
  if( connect(fd,(struct sockaddr *)&addr,sizeof (addr)) < 0){
	  erro("Connect");
  }
  write(fd, app, strlen(app));//indica ao servidor qual é a app
  frontPAGE(fd);
  fflush(stdout);
  close(fd);
}
void frontPAGE(int fd){
  system("clear");
  printf("Bem vindo à aplicação do Profissional de Saúde.\n");
  memset(buffer,0,strlen(buffer));
  printf("\n1- Entrar\n2- Criar Conta\n0- Sair\n");
  printf("Escolha uma da opções: ");
	scanf("%d", &op);
  while(op >2 || op<0){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op);
  }
  getchar();
  switch(op){
    case 1:
      signIN(fd);
    case 2:
      signUP(fd);
    case 0:
      return;
  }
}
void signIN(int fd){
  system("clear");
  printf("Introduza o seu Nome de Utilizador: ");//pede login
  fgets(login,20,stdin);
  login[strcspn(login, "\n")] = 0;
  printf("Introduza a sua Password: ");//pede pass
  fgets(pw,20,stdin);
  pw[strcspn(pw, "\n")] = 0;
  strcat(buffer,login);//junta login+pass numa str
  strcat(buffer," ");
  strcat(buffer,pw);
  write(fd, buffer, strlen(buffer));//envia ao servidor
  memset(buffer,0,strlen(buffer));
  nread = read(fd, buffer, BUF_SIZE-1); //recebe verificação do login pelo servidor
  buffer[nread] = '\0';
	check=strcmp(buffer,"0");
  if (check==0){
    printf("Utilizador não existe.Será redirecionado em 5 segundos");
    printf("\n");
    sleep(5);
    frontPAGE(fd); 
  }
	memset(buffer,0,strlen(buffer));
  menu(fd,login);
}

void menu(int fd,char login[20]){
  system("clear");
  printf("Bem vindo %s à aplicação do Segurança de Saude\n", login);
  printf("\n1- Consultar Denuncias \n2- Alterar Conta\n3- Menu Ajuda\n0- Sair\n");
   printf("Escolha uma da opções: ");
	scanf("%d", &op);
  while(op >3 || op<0){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op);
  }
}
void signUP(int fd){
  
}


void erro(char *msg)
{
	printf("Erro: %s\n", msg);
	exit(-1);
}
