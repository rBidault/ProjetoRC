/*
	APLICAÇAO GESTOR DO SISTEMA (AAS)
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
#define BUF_SIZE 2048
char buffer[BUF_SIZE];
char app[] = "admin";
char option[20];
char login[20] = "", pw[20] ="";
int fd, nread,op, check=1;
struct sockaddr_in addr;
struct hostent *hostPtr;

void erro(char *msg);
void menu(int fd, char login[20]);
void signIN(int fd);
void signUP(int fd);
void frontPAGE(int fd);
void edit(int fd);
void accountcheck(int fd);
void help();

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
  write(fd, app, strlen(app));//manda ao servidor a identificação da app
  frontPAGE(fd);
  fflush(stdout);
  close(fd);
}

void frontPAGE(int fd){
  system("clear");
  printf("Bem vindo à aplicação do Gestor de Aplicacao.\n");
  memset(buffer,0,strlen(buffer));
  printf("\n1- Entrar\n0- Sair\n");
  printf("Escolha uma da opções: ");
  
	scanf("%d", &op);
  while(op >1 || op<0){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op);
  }
  getchar();
  switch(op){
    case 1:
      signIN(fd);
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
  printf("Bem vindo %s à aplicação do Gestor de Aplicação\n", login);
  printf("\n1- Validar Contas\n2- Alterar Conta\n3- Menu Ajuda\n0- Sair\n");
   printf("Escolha uma da opções: ");
	scanf("%d", &op);
  while(op >3 || op<0){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op);
  }
  getchar();
  switch (op){
  case 1:
    accountcheck(fd);
    break;
  case 2:
    edit(fd);
  case 3:
    help();
    break;
  case 0:
    exit(0);
  }

}

void accountcheck(int fd){
  memset(option,0,20);
  strcat(option,"check");
  write(fd, option, strlen(option));
  //check conta na app de admin
  int opt;
  printf("\nVerificar novos registos.\n1 - Aplicação Profissional de Saúde\n2 - Aplicação Agente de Segurança.\nEscolha uma opção: ");
  scanf("%d", &opt);
  while(opt > 2 || opt < 1){
	printf("Opção inválida! Introduza outra vez: ");
  	scanf("%d", &opt);
  }
  memset(buffer, 0, strlen(buffer));
  if(opt == 1){
	strcat(buffer, "1");
  }
  if(opt == 2){
	  strcat(buffer, "2");
  }
  write(fd, buffer, BUF_SIZE-1);
  memset(buffer, 0, strlen(buffer));
  printf("\nContas novas:\n");
  while(1){
  	  memset(buffer, 0, strlen(buffer));
	  nread = read(fd, buffer, BUF_SIZE-1);
	  buffer[nread] = '\0';
    if(strstr(buffer,"fim")){
      break;
    }
	  printf("%s", buffer);
	  int o = 0;
	  printf("\nConfirma conta?\n1 - Sim\n2 - Não");
	  scanf("%d", &o);
	  while(o > 2 || o < 1){
		  printf("Opção inválida! Introduza outra vez: ");
		  scanf("%d", &o);
	  }
	  memset(buffer, 0, strlen(buffer));
	  if(o == 1){
		  strcpy(buffer, "1");
    }
	write(fd, buffer, BUF_SIZE-1);
	memset(buffer, 0, strlen(buffer));
  }  
}
void edit(int fd){
  printf("ola");
}
void help(){
  printf("ola");
}
void erro(char *msg)
{
	printf("Erro: %s\n", msg);
	exit(-1);
}

