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
#define BUF_SIZE	2048

//FUNCTIONS
void process_client(int client_fd);
void health_app();
void security_app();
void admin_app();
void erro(char *msg);
void den_reg(int client_fd);
void BTNalarm(int client_fd);
void editarS(int client_fd); 
void editarH(int client_fd);
void editarA(int client_fd); 
void optionH(int client_fd);
void optionS(int client_fd);
void optionA(int client_fd);
void den_vis(int client_fd);
void HsignUP(int client_fd);
void SsignUP(int client_fd);
void accountcheck(int client_fd);

//GLOBAL VARIABLES
FILE *text, *textaux;
int s=1, h=1, a=1, sU=1;
int nread = 0;
char buffer[BUF_SIZE];

int main(){
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
  memset(buffer, 0, BUF_SIZE);
  nread = read(client_fd, buffer, BUF_SIZE-1);	
	buffer[nread] = '\0';
  sU=strcmp(buffer,"UP");
  if(sU==0){
    HsignUP(client_fd);
  }
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
  optionH(client_fd);
}

void HsignUP(int client_fd){
  FILE *fp;
  nread = read(client_fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
  fp = fopen("Health_sign_up.txt", "a");
  if(fp == NULL)
	erro("Abertura do ficheiro");
  char newuser[50];
  strcpy(newuser, buffer);
  fprintf(fp, "%s\n",newuser);
  fclose(fp);
  exit(0);
}

void optionH(int client_fd){
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
   editarH(client_fd); //administrador do sistema
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
  fprintf(text,"%s\n", buffer);
  memset(buffer,0,BUF_SIZE);
  fclose(text);
  return;
}

void BTNalarm(int client_fd){
  printf("ola");
}

void editarH(int client_fd){
  printf("ola");
}

void security_app(int client_fd){
  memset(buffer, 0, BUF_SIZE);
  nread = read(client_fd, buffer, BUF_SIZE-1);	
	buffer[nread] = '\0';
  printf("%s",buffer);
  sU=strcmp(buffer,"UP");
  if(sU==0){
    HsignUP(client_fd);
  }
  text = fopen ("RSecurity.txt","r"); //tenta abrir o ficheiro
  char *userinfo=NULL;
  size_t len=0;
  char user[BUF_SIZE];
  int check=1;
  char msg[BUF_SIZE];
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
  optionS(client_fd);
}

void SsignUP(int client_fd){
  FILE *fp;
  nread = read(client_fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
  fp = fopen("Security_sign_up.txt", "a");
  if(fp == NULL)
	erro("Abertura do ficheiro");
  char newuser[50];
  strcpy(newuser, buffer);
  fprintf(fp,"%s\n", newuser);
  fclose(fp);
  exit(0);
}

void optionS(int client_fd){
  int denuncia=1,edit=1;
  memset(buffer,0,BUF_SIZE); 
  nread = read(client_fd, buffer, BUF_SIZE-1);
  printf("%s", buffer);
  denuncia=strcmp(buffer,"denuncia");
  edit=strcmp(buffer,"edit");
  if (denuncia==0){
    //den_vis(client_fd); //profisional de saude
  }
  if (edit==0){
    //editarS(client_fd); //administrador do sistema
  }

} 

/*void den_vis(int client_fd){
  memset(buffer,0,BUF_SIZE);
  text = fopen ("RegistoDen.txt","r");

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
}*/

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
  memset(msg,0,strlen(msg));
  strcat(msg,"1");  
  write(client_fd, msg, strlen(msg));
  fclose(text);
  optionA(client_fd);
}

void optionA(int client_fd){
  int accheck=1,edit=1;
  memset(buffer,0,BUF_SIZE); 
  nread = read(client_fd, buffer, BUF_SIZE-1);
  printf("%s", buffer);
  accheck=strcmp(buffer,"check");
  edit=strcmp(buffer,"edit");
  if (accheck==0){
    accountcheck(client_fd); //profisional de saude
  }
  if (edit==0){
    //editarS(client_fd); //administrador do sistema
  }
} 
void accountcheck(int client_fd){
  memset(buffer,0,strlen(buffer));
  int opt;
  nread = read(client_fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
  opt = strcmp(buffer, "1");
  memset(buffer,0,strlen(buffer));
  int o = -1;
  if(opt == 0){
    text = fopen("Health_sign_up.txt", "r");
    textaux = fopen("RHealth.txt", "a");
    char *newusers = NULL;
    size_t len = 0;
    while((getline(&newusers, &len, text)) != -1){
      memset(buffer,0,strlen(buffer));
      strcat(buffer, newusers); 
      printf("%s\n", newusers);
      printf("%s\n", buffer);
      write(client_fd, buffer, BUF_SIZE-1);
      memset(buffer,0,strlen(buffer));
      nread = read(client_fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      o = strcmp(buffer, "1");
      if (o == 0){
        fprintf(text, "%s\n", newusers);
      }
      else if (o != 0){
        continue;
      }
      memset(buffer,0,strlen(buffer));
    }
    fclose(text);
    fclose(textaux);
    text = fopen("Health_sign_up.txt", "w");
    fclose(text);
    memset(buffer,0,strlen(buffer));
  }
  if(opt != 0){
    text = fopen("Agent_sign_up.txt", "r");
    textaux = fopen("RSecurity.txt", "a");
    char *newusers = NULL;
    size_t len = 0;
    while((getline(&newusers, &len, text)) != -1){
      memset(buffer,0,strlen(buffer));
      strcat(buffer, newusers);
      printf("%s\n", newusers);
      printf("%s\n", buffer);
      write(client_fd, buffer, BUF_SIZE-1);
      memset(buffer,0,strlen(buffer));
      newusers=NULL;
      nread = read(client_fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      o = strcmp(buffer, "1");
      if (o == 0){
        fprintf(text, "%s\n", newusers);
      }
      else if (o != 0){
        continue;
      }
      memset(buffer,0,strlen(buffer));
    } 
    fclose(text);
    fclose(textaux);
    text = fopen("Agent_sign_up.txt", "w");
    fclose(text);
    memset(buffer,0,strlen(buffer));
  }
  memset(buffer,0,strlen(buffer));
  strcat(buffer, "fim");
  write(client_fd, buffer, BUF_SIZE-1);
  return;
}
void erro(char *msg){
	printf("Erro: %s\n", msg);
	exit(-1);
}
