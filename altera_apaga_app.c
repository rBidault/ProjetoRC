//alterar e apagar conta na app
int opt = -1;
char  newlogin[20], newpw[20];
printf("1 - Alterar Conta\n2 - Apagar Conta");
scanf("%d", opt)
while(opt > 2 || opt < 1){
	printf("Opção inválida! Introduza outra vez: ");
	scanf("%d", opt);
}
if(opt == 1){
	memset(buffer, 0, strlen(buffer));
	strcpy(buffer, "edit");
	write(fd, buffer, BUF_SIZE-1);
	printf("\nIntroduza o seu novo nome de utilizador: ");
	scanf("%s", newlogin);
	printf("\nIntroduza a sua nova palavra-passe: ");
	scanf("%s", newpw);
	memset(buffer, 0, strlen(buffer));
	newlogin[strcspn(newlogin, "\n")] = 0;
	strcat(buffer, newlogin);
	strcat(buffer, " ");
	newpw[strcspn(newpw, "\n")] = 0;
	strcat(buffer, newpw);
	 write(fd, buffer, strlen(buffer));
}
if(opt == 2){
	memset(buffer, 0, strlen(buffer));
	stcpy(buffer, "delete");
	write(fd, buffer, BUF_SIZE-1);
	memset(buffer, 0, strlen(buffer));
	strcat(buffer,login);
  	strcat(buffer," ");
  	strcat(buffer,pw);
  	write(fd, buffer, BUF_SIZE-1);
  	return;
}