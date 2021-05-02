/*
	APLICAÇÃO PROFISSIONAL DE SAUDE (APS)
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
#include <time.h>

#define SERVER_PORT     9000
#define BUF_SIZE 1024
char buffer[BUF_SIZE];
char app[20] = "health";
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
void denuncia(int fd,char login[20]);
void alarme(int fd);
void edit(int fd);
void helpTXT();

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
  memset(buffer,0,strlen(buffer));
  frontPAGE(fd);

}

void frontPAGE(int fd){
  op=-1;
  write(fd, app, strlen(app));//manda ao servidor a identificação da app
  system("clear");
  printf("Bem vindo à aplicação do Profissional de Saúde.\n");
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
      exit(0);
  }
}

void signIN(int fd){
  system("clear");
  printf("Introduza o seu Nome de Utilizador\n->");//pede login
  fgets(login,20,stdin);
  login[strcspn(login, "\n")] = 0;
  printf("Introduza a sua Password\n->");//pede pass
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
  system("clear");
  printf("Bem vindo %s à aplicação do Profissional de Saude\n", login);
  printf("\n1- Fazer Denuncia \n2- Alertar Segurança(Alarme)\n3- Alterar Conta\n4- Menu Ajuda\n0- Sair\n");
  printf("Escolha uma da opções: ");
	scanf("%d", &op);
  while(op >4 || op<0){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op);
  }
  getchar();
  switch(op){
    case 1:
      denuncia(fd,login);
    case 2:
      alarme(fd);
    case 3:
      edit(fd);
    case 4:
      helpTXT();
    case 0:
      exit(0);
  }
}
void denuncia(int fd,char login[20]){
  char victim[40],agr[40],local[40],data[20],horario[20];
  char ano[10],mes[10],dia[10],hora[10], min[10];
  time_t tempo =time(NULL);
  struct tm *tmp=localtime(&tempo);

  memset(option,0,20);
  strcat(option,"denuncia");
  write(fd, option, strlen(option));
  op=-1;
  system("clear");
  printf("Menu Denuncia\nDeverá responder às seguintes perguntas:");
  printf("\nÉ a vítima da agressão que quer denunciar?");
  printf("\n1- Sim\n2- Não");
  printf("\nEscolha uma da opções: ");
	scanf("%d", &op);
  while(op >2 || op<1){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op); 
  }
  getchar();
  if(op==1){
    memset(victim,0,40);  
    strcat(victim,login);
  }
  else{
    memset(victim,0,40);
    printf("Introduza o nome da vítima: ");
    fgets(victim,40,stdin);
    victim[strcspn(victim, "\n")] = 0;
  }
  op=-1;
  printf("Qual foi o tipo de agressão sofrido?");
  printf("\n1- Verbal\n2- Fisica\n3- Sexual\n4- Outro");
  printf("\nEscolha uma da opções: ");
	scanf("%d", &op);
  while(op >4 || op<1){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op); 
  }
  getchar();
  memset(agr,0,40);
  switch(op){
    case 1:
      strcat(agr,"Verbal");
      break;
    case 2:
      strcat(agr,"Fisica");
      break;
    case 3:
      strcat(agr,"Sexual");
      break;
    case 4:
      fgets(agr,40,stdin);
      agr[strcspn(agr, "\n")] = 0;
      break;
  }
  op=-1;
  printf("Em que local aconteceu a agressão?\n->");
  fgets(local,40,stdin);
  local[strcspn(local, "\n")] = 0;
  printf("A agressão aconteceu agora?");
  printf("\n1- Sim\n2- Não");
  printf("\nEscolha uma da opções: ");
	scanf("%d", &op);
  while(op >2 || op<1){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op); 
  }
  getchar();
  if(op==1){
      snprintf(ano,10,"%04d",tmp->tm_year+1900);
      snprintf(mes,10,"%02d",tmp->tm_mon);
      snprintf(dia,10,"%02d",tmp->tm_mday);
      snprintf(hora,10,"%02d",tmp->tm_hour);
      snprintf(min,10,"%02d",tmp->tm_min);
      memset(data,0,10);
      memset(horario,0,10);
      strcat(data,dia);
      strcat(data,"/");
      strcat(data,mes);
      strcat(data,"/");
      strcat(data,ano);
      strcat(horario,hora);
      strcat(horario,":"); 
      strcat(horario,min);
  }
  else{
      printf("Introduza a data em que aconteceu a agressão(formato dd/mm/aaaa)\n->");
      fgets(data,20,stdin);
      data[strcspn(data, "\n")] = 0;
      printf("Introduza a hora em que aconteceu a agressão(formato hh:mm)\n->");
      fgets(horario,20,stdin);
      horario[strcspn(horario, "\n")] = 0;
  }
  op=-1;
  printf("Quer que a sua denuncia seja anónima?");
  printf("\n1- Sim\n2- Não");
  printf("\nEscolha uma da opções: ");
	scanf("%d", &op);
  while(op >2 || op<1){
    printf("Escolha Inválida. Reintroduza: ");
    scanf("%d", &op); 
  }
  getchar();
  if(op==1){
    memset(victim,0,40);
    strcat(victim,"Anonimo");
  }
  printf("%s",victim);
  memset(buffer,0,BUF_SIZE);
  strcat(buffer,victim);
  strcat(buffer," ");
  strcat(buffer,agr);
  strcat(buffer," ");
  strcat(buffer,local);
  strcat(buffer," ");
  strcat(buffer,data);
  strcat(buffer," ");
  strcat(buffer,horario);
  write(fd,buffer, BUF_SIZE);
  printf("A sua denuncia foi registada. Será redirecionado em 5 segundos.");
  printf("\n");
  sleep(5);
  menu(fd,login); 
}
void alarme(int fd){printf("ola");}
void edit(int fd){printf("ola");}
void helpTXT(){printf("ola");}
void signUP(int fd){
  printf("ola)");
  
}
void erro(char *msg){
	printf("Erro: %s\n", msg);
	exit(-1);
}
