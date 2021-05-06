void delete(int fd){
  memset(buffer, 0, strlen(buffer));
  strcat(buffer, "delete");
  write(fd, buffer, BUF_SIZE-1);
  memset(buffer, 0, strlen(buffer));
  nread = read(fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
}
