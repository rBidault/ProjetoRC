//check conta na app de admin
int opt;
char op[5];
printf("\nVerificar novos registos.\n1 - Aplicação Profissional de Saúde\n2 - Aplicação Agente de Segurança.\nEscolha uma opção: ");
scanf("%d", opt);
while(opt > 2 || opt < 1){
	printf("Opção inválida! Introduza outra vez: ");
	scanf("%d", opt);
}
if(opt == 1)
	strcpy(op, "1");
else if(opt == 2);
	strcpy(op, "2");
write(fd, op, BUF_SIZE-1);
memset(opt, 0, strlen(buffer));
printf("\nContas novas:\n");
while(1){
	nread = read(fd, buffer, BUF_SIZE-1);
	buffer[nread] = '\0';
	printf("%s", buffer);
	int o = 0;
	printf("\nConfirma conta?\n1 - Sim\n2 - Não");
	scanf("%d", o);
	while(o > 2 || o < 1){
		printf("Opção inválida! Introduza outra vez: ");
		scanf("%d", o);
	}
	if(o == 1)
		scrcpy(op, "1");
	write(fd, op, BUF_SIZE-1);
	memset(opt, 0, strlen(buffer));
	char
	//if ()
}