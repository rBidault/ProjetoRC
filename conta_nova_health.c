//criar conta nova
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
