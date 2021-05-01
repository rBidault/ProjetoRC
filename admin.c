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

#define BUF_SIZE 1024
int op;

void erro(char *msg);
void menu(int fd,char login[20]);

int main() {
  char buffer[BUF_SIZE];
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
  write(fd, app, strlen(app));//indica ao servidor qual é a app
  memset(buffer,0,strlen(buffer));
  printf("\n1- Entrar\n0- Sair\n");
  printf("Escolha uma da opções: ");
	scanf("%d", &op);
  while(op >1 || op<0){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op);
  }
  switch(op){
    case 1:
      system("clear");
      printf("Introduza o seu Login: ");//pede login
      fgets(login,20,stdin);
      login[strcspn(login, "\n")] = 0;
      printf("\nIntroduza a sua Password: ");//pede pass
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
        erro("Utilizador não existe!");
      }
  
	    memset(buffer,0,strlen(buffer));
      menu(fd,login);
    case 0:
      return 0;
  }
  fflush(stdout);
  close(fd);
}
void menu(int fd,char login[20]){
  system("clear");
  printf("Bem vindo %s à aplicação do Gestor de Aplicação\n", login);
  printf("\n1-Alterar Contas \n2- Validar Contas\n3-Menu Ajuda\n0- Sair\n");
   printf("Escolha uma da opções: ");
	scanf("%d", &op);
  while(op >3 || op<0){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op);
  }


}
void erro(char *msg)
{
	printf("Erro: %s\n", msg);
	exit(-1);
}

