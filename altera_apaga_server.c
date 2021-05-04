int a = -1;
int b = -1;
memset(buffer, 0, strlen(buffer));
nread = read(client_fd, buffer, BUF_SIZE);
buffer[nread] = '\0';
a = strcmp(buffer, "edit");
b = strcmp(buffer, "delete");
if(a == 0){
	edita_conta();
}
if(b == 0){
	apaga_conta();
}


//funções para editar e apagar conta
void edita_conta(){
	memset(buffer, 0, strlen(buffer));
	nread = read(client_fd, buffer, BUF_SIZE);
	buffer[nread] = '\0';
	text = fopen("RHealth.txt","r");
	if(text == NULL){
		erro("Abertura do ficheiro");
	}
	textaux = fopen("aux.txt", "w+");
	if(textaux == NULL){
		erro("Abertura do ficheiro");
	}
	size_t len = 0;
	size_t len2 = 0;
	char *userinfo = NULL;
	char newuser[BUF_SIZE];
	strcat(newuser, buffer);
	memset(buffer, 0, strlen(buffer));
	while((getline(&userinfo, &len, text)) != -1){
		if(strstr(userinfo, user)){
			fprintf(textaux, "%s", newuser);
		}
		else{
			fprintf(textaux, "%s", userinfo);
		}
		userinfo = NULL;
	}
	close(text);
	close(textaux);
	text = fopen("RHealth.txt","w+");
	if(text == NULL){
		erro("Abertura do ficheiro");
	}
	textaux = fopen("aux.txt", "r");
	if(textaux == NULL){
		erro("Abertura do ficheiro");
	}
	while((getline(&userinfo, &len2, textaux)) != -1){
		fprintf(text, "%s", userinfo);
		userinfo = NULL;
	}
	close(text);
	close(textaux);
	textaux = fopen("aux.txt", "w+");
	if(textaux == NULL){
		erro("Abertura do ficheiro");
	}
	close(textaux);
	memset(buffer, 0, strlen(buffer));
	strcpy(buffer, "Dados alterados com sucesso!");
	write(client_fd, buffer, strlen(buffer));
}
void apaga_conta(){
	memset(buffer, 0, strlen(buffer));
	nread = read(client_fd, buffer, BUF_SIZE);
	buffer[nread] = '\0';
	text = fopen("RHealth.txt","r");
	if(text == NULL){
		erro("Abertura do ficheiro");
	}
	textaux = fopen("aux.txt", "w+");
	if(textaux == NULL){
		erro("Abertura do ficheiro");
	}
	size_t len = 0;
	size_t len2 = 0;
	char *userinfo = NULL;
	char user[BUF_SIZE];
	strcat(user, buffer);
	memset(buffer, 0, strlen(buffer));
	while((getline(&userinfo, &len, text)) != -1){
		if(!strstr(userinfo, user)){
			fprintf(textaux, "%s", userinfo);
		}
		userinfo = NULL;
	}
	close(text);
	close(textaux);
	text = fopen("RHealth.txt","w+");
	if(text == NULL){
		erro("Abertura do ficheiro");
	}
	textaux = fopen("aux.txt", "r");
	if(textaux == NULL){
		erro("Abertura do ficheiro");
	}
	while((getline(&userinfo, &len2, textaux)) != -1){
		fprintf(text, "%s", userinfo);
		userinfo = NULL;
	}
	close(text);
	close(textaux);
	textaux = fopen("aux.txt", "w+");
	if(textaux == NULL){
		erro("Abertura do ficheiro");
	}
	close(textaux);
	memset(buffer, 0, strlen(buffer));
	strcpy(buffer, "Conta apgada com sucesso!");
	write(client_fd, buffer, strlen(buffer));
}
