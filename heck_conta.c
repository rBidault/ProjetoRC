//check conta
FILE *fp;
int opt;
nread = read(fd, buffer, BUF_SIZE-1);
buffer[nread] = '\0';
opt = strcmp(buffer, "1");
int o = -1;
if(opt == 0){
	fp = fopen("Health_sign_up.txt", "r");
	char *newusers = NULL;
	size_t len = 0;
	while((getline(&newusers, &len, fp)) != -1){
		strcpy(buffer, newusers);
		write(fd, buffer, BUF_SIZE-1);
		nread = read(fd, buffer, BUF_SIZE-1);
		buffer[nread] = '\0';
		o = strcmp(buffer, "1");
		if (o == 0){
			text = fopen("RHealth.txt", "w")
			fprintf(text, "%s\n", newusers);
		}
		else if (o != 0){
			continue;
		}
		fclose(text);
		text = fopen("Health_sign_up.txt", "w");
		fclose(text);
		fclose(fp);
	}
}
else if(opt != 0){
	fp = fopen("Agent_sign_up.txt", "r");
	char *newusers = NULL;
	size_t len = 0;
	while((getline(&newusers, &len, fp)) != -1){
		strcpy(buffer, newusers);
		write(fd, buffer, BUF_SIZE-1);
		nread = read(fd, buffer, BUF_SIZE-1);
		buffer[nread] = '\0';
		o = strcmp(buffer, "1");
		if (o == 0){
			text = fopen("RSecurity.txt", "w")
			fprintf(text, "%s\n", newusers);
		}
		else if (o != 0){
			continue;
		}
		fclose(text);
		text = fopen("Agent_sign_up.txt", "w");
		fclose(text);
		fclose(fp);
	}
}
else
	printf("Opção inválida!");
return 0;