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
#define BUF_SIZE 2048
char buffer[BUF_SIZE];
char app[] = "security";
char login[20] = "", pw[20] ="";
char option[20];
int fd, nread,op, check=1;
struct sockaddr_in addr;
struct hostent *hostPtr;

void erro(char *msg);
void menu(int fd, char login[20]);
void signIN(int fd);
void signUP(int fd);
void frontPAGE(int fd);
void mostradenuncia(int fd);
void helpTXT(int fd,char login[20]);
void edit(int fd);

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
  printf("Bem vindo à aplicação do Segurança de Saúde.\n");
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
  if(check==0){
    printf("Utilizador não existe.Será redirecionado em 5 segundos");
    printf("\n");
    sleep(5);
    frontPAGE(fd);
  }
	memset(buffer,0,strlen(buffer));
  menu(fd,login);
}

void menu(int fd,char login[20]){
  op=-1;
  char msg[]="";
  system("clear");
  printf("Bem vindo %s à aplicação do Segurança de Saude\n", login);
  printf("\n1- Consultar Denuncias \n2- Alterar Conta\n3- Menu Ajuda\n0- Sair\n");
  printf("Escolha uma da opções: ");
	scanf("%d", &op);
  while(op >3 || op<0){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op);
  }
  getchar();
  printf("%d",op);
  switch(op){
    case 1:
      strcat(msg, "mostra");
      printf("%s",msg);
      write(fd,msg,sizeof(msg));
      printf("eu");
      mostradenuncia(fd);
    case 2:
      edit(fd);
    case 3:
      helpTXT(fd,login);
    case 0:
      exit(0);
  }
}

void signUP(int fd){
  char sUP[]="UP";
  write(fd, sUP,sizeof(sUP));
  memset(buffer, 0, BUF_SIZE);
  char newlogin[20];
  char newpw[20];
  printf("\nInsira o Login pretendido: ");
  scanf("%s", newlogin);
  printf("\nInsira a password desejada: ");
  scanf("%s", newpw);
  strcat(buffer, newlogin);
  strcat(buffer, " ");
  strcat(buffer, newpw);
  write(fd, buffer, BUF_SIZE-1);
  memset(buffer, 0, strlen(buffer));
  nread = read(fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0'; 
  exit(0); 
}

void mostradenuncia(int fd){
  char filtro[20];
  system("clear");
  memset(buffer, 0, strlen(buffer));
  printf("Menu de Visualização de Denuncias\n");
  printf("Deseja aplicar filtros na pesquisa?\n");
  printf("\n1- Sim \n2- Não\n");
  printf("Escolha uma da opções: ");
	scanf("%d", &op);
  while(op >2 || op<1){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op);
  }
  getchar();
  if(op==1){
    op=-1;
    memset(option,0,20);
    char options[]="filtro";
    write(fd, options, strlen(options));
    printf("Que tipo de filtro quer aplicar?\n");
    printf("\n1- Data \n2- Tipo de agressão\n");
    printf("Escolha uma da opções: ");
	  scanf("%d", &op);
    while(op >2 || op<1){
      printf("Escolha Inválida. Reintroduza: ");
      scanf("%d", &op);
    }
    getchar();
    if(op==2){
      printf("Que tipo de agressão quer procurar?\n");
      printf("\n1- Verbal \n2- Fisica\n3- Sexual\n4- Outro\n");
      printf("Escolha uma da opções: ");
	    scanf("%d", &op);
      while(op >4 || op<1){
        printf("Escolha Inválida. Reintroduza: ");
        scanf("%d", &op);
      }
      getchar();
      switch (op){
        case 1:
          strcat(filtro, "Verbal");
          break;
        case 2:
          strcat(filtro, "Fisica");
          break;
        case 3:
          strcat(filtro, "Sexual");
          break;
        case 4:
          strcat(filtro, "Outro");
          break;
      }
      write(fd,filtro,strlen(filtro));
    }
    else{
      op=-1;
      printf("Quer pesquisar por?\n");
      printf("\n1- Mês \n2- Ano\n3- Data Especifica\n");
      printf("Escolha uma da opções: ");
	    scanf("%d", &op);
      while(op >3 || op<1){
        printf("Escolha Inválida. Reintroduza: ");
        scanf("%d", &op);
      }
      getchar();
      switch (op){
        case 1:
          op=-1;
          printf("Que mês quer pesquisar?\n");
          printf("\n1- Janeiro \n2- Fevereiro\n3- Março\n4- Abril\n5- Maio\n6- Junho\n7- Julho\n8- Agosto\n9- Setembro\n10- Outubro\n11- Novembro\n12- Dezembro\n");
          printf("Escolha uma da opções: ");
	        scanf("%d", &op);
          while(op >12 || op<1){
            printf("Escolha Inválida. Reintroduza: ");
            scanf("%d", &op);
          }
          getchar();
          switch (op){
            case 1:
              strcat(filtro, "/01/");
              break;
            case 2:
              strcat(filtro, "/02/");
              break;
            case 3:
              strcat(filtro, "/03/");
              break;
            case 4:
              strcat(filtro, "/04/");
              break;
            case 5:
              strcat(filtro, "/05/");
              break;
            case 6:
              strcat(filtro, "/06/");
              break;
            case 7:
              strcat(filtro, "/07/");
              break;
            case 8:
              strcat(filtro, "/08/");
              break;
            case 9:
              strcat(filtro, "/09/");
              break;
            case 10:
              strcat(filtro, "/10/");
              break;
            case 11:
              strcat(filtro, "/11/");
              break;
            case 12:
              strcat(filtro, "/12/");
              break;
          
          }
          break;
        case 2:
          printf("\nIntroduza o ano que deseja visualizar: " );
          fgets(filtro,20,stdin);
          filtro[strcspn(filtro, "\n")] = 0;
          break;
        case 3:
          printf("\nIntroduza a data que deseja visualizar(no formato dd/mm/aaaa): " );
          fgets(filtro,20,stdin);
          filtro[strcspn(filtro, "\n")] = 0;
          break;
      }
      write(fd,filtro,strlen(filtro));
    }
    memset(buffer,0,BUF_SIZE);
    nread = read(fd, buffer, BUF_SIZE-1);	//recebe login
	  buffer[nread] = '\0';
    while((strcmp(buffer,"fim"))!=0){
      printf("%s", buffer);
      memset(buffer,0,BUF_SIZE);
      nread = read(fd, buffer, BUF_SIZE-1);	//recebe login
	    buffer[nread] = '\0';
    }
  }
  else{
    memset(buffer,0,BUF_SIZE);
    nread = read(fd, buffer, BUF_SIZE-1);	//recebe login
	  buffer[nread] = '\0';
    while((strcmp(buffer,"fim"))!=0){
      printf("%s", buffer);
      memset(buffer,0,BUF_SIZE);
      nread = read(fd, buffer, BUF_SIZE-1);	//recebe login
	    buffer[nread] = '\0';
    }
  }


}

void helpTXT(int fd,char login[20]){
  system("clear");
  printf("Menu Apoio\n");
  printf("1- Consultar Denuncias.\n Neste menu poderá consultar as denuncias registadas até ao momento.\n Será acompanhado em cada passo caso queria aplicar filtros à sua pesquisa.\n Pode aplicar filtros de pesquisa como data da ocorência ou tipo de agressão.");
  printf("\n\n2- Alterar Conta.\n Neste menu poderá alterar o seu nome do uiltizador e a sua palavra-passe.\n Será acompanhado em cada passo pelo processo.");
  printf("\n\nPrima Enter para voltar.\n");
  getchar();
  menu(fd, login);
}

void edit(int fd){
  char newlogin[20];
  char newpw[20];
  system("clear");
  memset(buffer, 0, strlen(buffer));
  strcat(buffer, "edit");
  write(fd, buffer, BUF_SIZE-1);
  memset(buffer, 0, strlen(buffer));
  printf("\nIntroduza o seu novo nome de utilizador: ");
  scanf("%s", newlogin);
  printf("\nIntroduza a nova palavra-passe: ");
  scanf("%s", newpw);
  memset(buffer, 0, strlen(buffer));
  newlogin[strcspn(newlogin, "\n")] = '\0';
  newpw[strcspn(newpw, "\n")] = '\0';
  strcat(buffer, newlogin);
  strcat(buffer, " ");
  strcat(buffer, newpw);
  printf("\n%s", buffer);
  write(fd, buffer, BUF_SIZE-1);
  memset(buffer, 0, strlen(buffer));
  nread = read(fd, buffer, BUF_SIZE-1);
	buffer[nread] = '\0';
  printf("%s", buffer);\
  printf("\n\nPrima Enter para voltar.\n");
  getchar();
  menu(fd, login);
  
}

void delete(int fd){
  memset(buffer, 0, strlen(buffer));
  strcat(buffer, "delete");
  write(fd, buffer, BUF_SIZE-1);
  memset(buffer, 0, strlen(buffer));
  nread = read(fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
}

void erro(char *msg){
	printf("Erro: %s\n", msg);
	exit(-1);
}