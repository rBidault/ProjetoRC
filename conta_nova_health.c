// criar conta nova na app
char newlogin[20];
char newpw[20];
printf("\nInsira o Login pretendido: ");
scanf("%s", newlogin);
printf("\nInsira a password desejada: ");
scanf("%s", newpw);
strcat(buffer, newlogin);
strcat(buffer, " ");
strcat(buffer, newpw);
write(fd, buffer, BUFF_SIZE-1);
memset(buffer, 0, strlen(Biffer));
nread = read(fd, buffer, BUFF_SIZE-1);
buffer[nread] = '\0';



//criar conta nova no server
FILE *fp;
nread = read(client_fd, buffer, BUF_SIZE-1);
buffer[nread] = '\0';
fp = fopen("Health_sign_up.txt", "w");
if(fp == NULL)
	erro("Abertura do ficheiro");
char newuser[50];
strcpy(newuser, buffer);
fprintf(fp, newuser);
fclose(fp)
