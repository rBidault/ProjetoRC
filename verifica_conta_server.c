void accountcheck(int client_fd){
  char contas[BUF_SIZE] = "";
  memset(buffer,0,BUF_SIZE);
  int opt;
  nread = read(client_fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
  opt = strcmp(buffer, "1");
  memset(buffer,0,BUF_SIZE);
  int o = -1;
  if(opt == 0){
    text = fopen("Health_sign_up.txt", "r");
    textaux = fopen("RHealth.txt", "a");
    char *newusers = NULL;
    size_t len = 0;
    while((getline(&newusers, &len, text)) != -1){
      strcat(buffer, newusers); 
    }
    strcat(contas, buffer);
    write(client_fd, buffer, BUF_SIZE-1);
    memset(buffer,0,BUF_SIZE);
    nread = read(client_fd, buffer, BUF_SIZE-1);
    buffer[nread] = '\0';
    printf("\n%s", buffer);
    o = strcmp(buffer, "1");
    if(o == 0){
      fprintf(textaux, "%s", contas);
    }
    else{
      printf("\n Cheguei aqui!");
    }
    memset(buffer, 0, strlen(buffer));
    fclose(text);
    fclose(textaux);
    text = fopen("Health_sign_up.txt", "w");
    fclose(text);
    memset(buffer,0,BUF_SIZE);
  }
  if(opt != 0){
    text = fopen("Agent_sign_up.txt", "r");
    textaux = fopen("RSecurity.txt", "a");
    char *newusers = NULL;
    size_t len = 0;
    while((getline(&newusers, &len, text)) != -1){
      strcat(buffer, newusers); 
    }
    strcat(contas, buffer);
    write(client_fd, buffer, BUF_SIZE-1);
    memset(buffer,0,BUF_SIZE);
    nread = read(client_fd, buffer, BUF_SIZE-1);
    buffer[nread] = '\0';
    o = strcmp(buffer, "1");
    if(o == 0){
      fprintf(textaux, "%s", contas);
    }
    else{
      printf("\n Cheguei aqui!");
    }
    memset(buffer, 0, strlen(buffer));
    fclose(text);
    fclose(textaux);
    text = fopen("Agent_sign_up.txt", "w");
    fclose(text);
    memset(buffer,0,BUF_SIZE);
  }
  return;
}
