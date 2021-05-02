/*
	APLICAÇÃO CENTRAL (AC)
*/
//LIBRARIES
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>

//STATIC VARIABLES
#define SERVER_PORT     9000
#define BUF_SIZE	1024

//FUNCTIONS
void process_client(int client_fd);
void health_app();
void security_app();
void admin_app();
void erro(char *msg);
void den_reg(int client_fd);
void BTNalarm(int client_fd);
void editar(int client_fd); 
void option(int client_fd);


//GLOBAL VARIABLES
FILE *text;
int s=1, h=1, a=1;
int nread = 0;
char buffer[BUF_SIZE];

int main() {
  int fd, client;
  struct sockaddr_in addr, client_addr;
  int client_addr_size;
  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port        = htons(SERVER_PORT);

  if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	erro("na funcao socket");
  if ( bind(fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
	erro("na funcao bind");
  if( listen(fd, 5) < 0) 
	erro("na funcao listen");
  
  int nclients=0;
  system("clear");
  while (1) {
    client_addr_size = sizeof(client_addr);
    client = accept(fd,(struct sockaddr *)&client_addr,&client_addr_size);
      nclients++;
    if (client > 0) {
      if (fork() == 0) {
        close(fd);
        process_client(client);
        exit(0);
      }
    close(client);
    
    }
  }
  return 0;
}


void process_client(int client_fd){ 
  memset(buffer,0,BUF_SIZE); 
  nread = read(client_fd, buffer, BUF_SIZE-1);	
	buffer[nread] = '\0';
  printf("%s",buffer);
  h=strcmp(buffer,"health");
  s=strcmp(buffer,"security");
  a=strcmp(buffer,"admin");
  memset(buffer,0,BUF_SIZE); 
	// aqui o servidor vai identificar a aplicação que fez a ligação
  if (h==0){
    health_app(client_fd); //profisional de saude
  }
  if (s==0){
    security_app(client_fd); //agente de segurança 
  }
  if (a==0){
    admin_app(client_fd); //administrador do sistema
  }
	fflush(stdout);
	close(client_fd);
    
}

void health_app(int client_fd){
  memset(buffer,0,BUF_SIZE);
  text = fopen ("RHealth.txt","r");//tenta abrir ficheiro
  char *userinfo=NULL;
  size_t len=0;
  char user[BUF_SIZE];
  int check=1;
  char msg[BUF_SIZE];
	if(text == NULL) {
    erro("Abertura do ficheiro");//verifica se o ficheiro foi aberto
  }
  memset(user,0,BUF_SIZE); 
  nread = read(client_fd, buffer, BUF_SIZE-1);	//recebe login
	buffer[nread] = '\0';
  strcat(user,buffer);
  memset(buffer,0,BUF_SIZE); 
  while ((getline(&userinfo, &len, text))!= -1){
    if(strstr(userinfo,user)){
      break;
    }
    userinfo=NULL;
  }
  userinfo[strcspn(userinfo, "\n")] = 0; //verifica login
  check=strcmp(userinfo,user); 
  printf("%d", check);   
  if(check!=0){ // só está a verificar uma vez, se falhar 2 entra na mesma
    memset(msg,0,strlen(msg));
    strcat(msg,"0");
    write(client_fd, msg, strlen(msg));
    exit(-1);
  }
  memset(msg,0,strlen(msg));
  strcat(msg,"1");  
  write(client_fd, msg, strlen(msg));
  fclose(text);
  option(client_fd);
}
void option(int client_fd){
  int denuncia=1,alarme=1,edit=1;
  memset(buffer,0,BUF_SIZE); 
  nread = read(client_fd, buffer, BUF_SIZE-1);
  printf("%s", buffer);
  denuncia=strcmp(buffer,"denuncia");
  alarme=strcmp(buffer,"alarme");
  edit=strcmp(buffer,"edit");
  if (denuncia==0){
    den_reg(client_fd); //profisional de saude
  }
  if (alarme==0){
    BTNalarm(client_fd); //agente de segurança 
  }
  if (edit==0){
   editar(client_fd); //administrador do sistema
  }
}
void den_reg(int client_fd){
  memset(buffer,0,BUF_SIZE);
  text = fopen ("RegistoDen.txt","a+");
  if(text == NULL) {//verifica se o ficheiro foi aberto
    erro("Abertura do ficheiro");
  }
  nread = read(client_fd, buffer, BUF_SIZE-1);	//recebe denuncia
	buffer[nread] = '\0';
  printf("%s, ",buffer);
  fprintf(text,"%s", buffer);
  memset(buffer,0,BUF_SIZE);
  fclose(text);
  return;
}
void BTNalarm(int client_fd){
  printf("ola");
}
void editar(int client_fd){
  printf("ola");
}
void security_app(int client_fd){
  memset(buffer,0,BUF_SIZE);
  text = fopen ("RSecurity.txt","r"); //tenta abrir o ficheiro
  char *userinfo=NULL;
  size_t len=0;
  char user[BUF_SIZE];
  int check=1;
  char msg[BUF_SIZE];
	
  memset(user,0,BUF_SIZE); 
  nread = read(client_fd, buffer, BUF_SIZE-1);	//recebe login
	buffer[nread] = '\0';
  strcat(user,buffer);
  memset(buffer,0,BUF_SIZE); 
  while ((getline(&userinfo, &len, text))!= -1){
    if(strstr(userinfo,user)){
      break;
    }
    userinfo=NULL;
  }
  userinfo[strcspn(userinfo, "\n")] = 0; //verifica login
  check=strcmp(userinfo,user);     
  if(check!=0){
    memset(msg,0,strlen(msg));
    strcat(msg,"0");
    write(client_fd, msg, strlen(msg));
    exit(-1);
  }  
  fclose(text);
}
void admin_app(int client_fd){
  memset(buffer,0,BUF_SIZE);
  text = fopen ("RAdmin.txt","r"); //tenta abrir ficheiro
  char *userinfo=NULL;
  size_t len=0;
  char user[BUF_SIZE];
  int check=1;
  char msg[BUF_SIZE];
	if(text == NULL) {//verifica se o ficheiro foi aberto
    erro("Abertura do ficheiro"); 
  }
  memset(user,0,BUF_SIZE); 
  nread = read(client_fd, buffer, BUF_SIZE-1);	//recebe login
	buffer[nread] = '\0';
  //printf("%s", buffer);
  strcat(user,buffer);
  memset(buffer,0,BUF_SIZE); 
  while ((getline(&userinfo, &len, text))!= -1){
    if(strstr(userinfo,user)){
      break;
    }
    userinfo=NULL;
  }
  userinfo[strcspn(userinfo, "\n")] = 0; //confirma login
  check=strcmp(userinfo,user);     
  if(check!=0){
    memset(msg,0,strlen(msg));
    strcat(msg,"0");
    write(client_fd, msg, strlen(msg));
    exit(-1);
  }
  fclose(text);
}
void erro(char *msg){
	printf("Erro: %s\n", msg);
	exit(-1);
}
