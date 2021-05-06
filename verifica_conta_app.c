void accountcheck(int fd){
  system("clear");
  char option[]="check";
  write(fd, option, strlen(option));
  //check conta na app de admin
  int opt;
  printf("\nVerificar novos registos.\n1 - Aplicação Profissional de Saúde\n2 - Aplicação Agente de Segurança.\nEscolha uma opção: ");
  scanf("%d", &opt);
  while(opt > 2 || opt < 1){
	  printf("Opção inválida! Introduza outra vez: ");
  	scanf("%d", &opt);
  }
  system("clear");
  memset(buffer, 0, strlen(buffer));
  if(opt == 1){
	  strcpy(buffer, "1");
  }
  if(opt == 2){
	  strcpy(buffer, "2");
  }
  write(fd, buffer, BUF_SIZE-1);
  memset(buffer, 0, strlen(buffer));
  printf("\nContas novas:\n");
  nread = read(fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
  printf("%s", buffer);
  int o = 0;
  printf("\nConfirma conta?\n1 - Sim\n2 - Não\nEscolha uma opção: ");
  scanf("%d", &o);
  while(o > 2 || o < 1){
	  printf("Opção inválida! Introduza outra vez: ");
	  scanf("%d", &o);
  }
  if(o == 1){
	  strcpy(buffer, "1");
  }
  write(fd, buffer, BUF_SIZE-1);
  memset(buffer, 0, BUF_SIZE );
  frontPAGE(fd);
}
