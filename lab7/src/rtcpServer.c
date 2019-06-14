#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include<signal.h>

#define SERV_PORT 10050
#define SERV_P 20001
#define BUFSIZE 1024
#define SADDR struct sockaddr
#define SADDR struct sockaddr2

#define SLEN sizeof(struct sockaddr)

void closeUPD(int sig){
    exit(0);
}

pid_t pid;
int main() {
    
  const size_t kSize = sizeof(struct sockaddr_in);

  int lfd, cfd;
  int nread;
  char buf[BUFSIZE];
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;
  printf("test1");
  if ((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }
  printf("test2");
  memset(&servaddr, 0, kSize);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  if (bind(lfd, (SADDR *)&servaddr, kSize) < 0) {
    perror("bind");
    exit(1);
  }
  printf("test3");

  if (listen(lfd, 5) < 0) {
    perror("listen");
    exit(1);
  }
 
  while (1) {
       printf("test4");
    unsigned int clilen = kSize;
      printf("Start serv\n");
    if ((cfd = accept(lfd, (SADDR *)&cliaddr, &clilen)) < 0) {
      perror("accept");
      exit(1);
    }
    printf("test5");
    int updPort0=SERV_P;
    //
    
    if (send(cfd, &updPort0, sizeof(int), 0) == -1) {
      perror("send problem!1");
      exit(1);
    }
    
    //write(cfd, updPort0, sizeof(int));
    printf("connection established\n");
    pid=fork();
    if(pid==0){
    signal(SIGUSR1, closeUPD);
    int updPort1=20001;
    //if(pid==0){
        //upd
        //
        printf("test6");
  int gfd, n;
  char mesg[BUFSIZE], ipadr[16];
  struct sockaddr_in servaddr2;
  struct sockaddr_in cliaddr2;

  if ((gfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
  }
  printf("test7");

  memset(&servaddr2, 0, SLEN);
  servaddr2.sin_family = AF_INET;
  //servaddr2.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr2.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr2.sin_port = htons(SERV_P);

  if (bind(gfd, (SADDR *)&servaddr2, SLEN) < 0) {
    perror("bind problem");
    exit(1);
  }
  printf("test8");
  printf("SERVER starts...\n");
  perror("read?0");
  int upd_stop_flag=1;
  perror("read?1");
  while (upd_stop_flag==1) {
      perror("read?2");
    unsigned int len = sizeof(struct sockaddr);
    perror("read?3");
    if ((n = recvfrom(gfd, mesg, BUFSIZE, 0, (SADDR *)&cliaddr2, &len)) < 0) {
      perror("recvfrom");
      exit(1);
    }
    perror("test9");
    mesg[n] = 0;
    /*
    printf("REQUEST %s      FROM %s : %d\n", mesg,
           inet_ntop(AF_INET, (void *)&cliaddr2.sin_addr.s_addr, ipadr, 16),
           ntohs(cliaddr.sin_port));
           */
perror("test9!");
    if (sendto(gfd, mesg, n, 0, (SADDR *)&cliaddr2, len) < 0) {
      perror("sendto");
      exit(1);
      }
      perror("test10");
    }
        
    exit(0);
}

    //}
//tcp
    //else {
       else {
          int n, syn;
          //printf("Error serv...\n");
        sleep(1);
    for (;;) {
        int buff;
        read(cfd, &buff, sizeof(int));
       if(buff == 5)
            {
                printf("test stop");
                //как прийдет 5 - сигнал по pid (kill)
                break;
            }
        if(buff == 4)
            {
                printf("test close");
                //как прийдет 5 - сигнал по pid (kill)
                kill(pid, SIGUSR1);
                break;
            }
        }
        //отправляем клиенту данные udp
        //читаем клиента бесконечно пока не прийдет код 5
        //как прийдет 5 - сигнал по pid (kill)
    }
    close(cfd);
    printf("test12");
  }
  printf("test13");
  close(lfd);
  
  }


