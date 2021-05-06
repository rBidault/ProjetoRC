void editarH(int client_fd, char data[40]){
  FILE *text1, *textaux1;
  char *userinfo;
  char newuser[BUF_SIZE] = "";
  size_t len = 0;
  size_t len2 = 0;
  memset(buffer,0,strlen(buffer));
  printf("\n%s", newuser);
  nread = read(client_fd, buffer, BUF_SIZE-1);
	buffer[nread] = '\0';
  strcat(newuser, buffer);
  printf("\n%s\n%s",newuser, data);
  text1 = fopen("RHealth.txt", "r");
  if(text1 == NULL){
    erro("Abertura de ficheiro");
  }
  textaux1 = fopen("aux.txt", "w+");
  if(textaux1 == NULL){
    erro("Abertura de ficheiro");
  }
  while((getline(&userinfo, &len, text1)) != -1){
    if(strstr(userinfo, data)){
      //strcat(data[0], "");
      fprintf(textaux1, "%s\n", newuser);
      printf("\nEstou aqui");
    }
    else{
      fprintf(textaux1, "%s", userinfo);
    }
    userinfo = NULL;
  }
  fclose(text1);
  fclose(textaux1);
  textaux1 = fopen("aux.txt", "r");
  if(textaux1 == NULL){
    erro("Abertura de ficheiro");
  }
  text1 = fopen("RHealth.txt", "w+");
  if(text1 == NULL){
    erro("Abertura de ficheiro");
  }
  while ((getline(&userinfo, &len, textaux1)) != -1){
    fprintf(text1, "%s", userinfo);
    userinfo = NULL;
  }
  fclose(textaux1);
  fclose(text1);
  textaux1 = fopen("aux.txt", "w+");
  if(textaux1 == NULL){
    erro("Abertura de ficheiro");
  }
  fclose(textaux1);
  memset(buffer,0,strlen(buffer));
  strcat(buffer, "\nDados alterados com sucesso!");
  write(client_fd, buffer, BUF_SIZE-1);
}
