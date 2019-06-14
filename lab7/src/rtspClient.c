#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define BUFSIZE 100
#define SERV_PORT 10050
#define SERV_PORT2 20001
#define SADDR struct sockaddr
#define SIZE sizeof(struct sockaddr_in)
#define SLEN sizeof(struct sockaddr_in)

int main(void) {
    perror("client Start!");
  printf("client stat!  ");
  int fd;
  int nread;
  char buf[BUFSIZE];
  struct sockaddr_in servaddr;
  perror("test1");
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket creating");
    exit(1);
  }
 
  memset(&servaddr, 0, SIZE);
  servaddr.sin_family = AF_INET;
  perror("test2");
 
  if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
    perror("bad address");
    exit(1);
  }

 perror("test3");
  servaddr.sin_port = htons(SERV_PORT);
  
  if (connect(fd, (SADDR *)&servaddr, SIZE) < 0) {
    perror("connect");
    exit(1);
  }
  
   perror("test4");
  int updPort=SERV_PORT;
 if (recv(fd, &updPort, sizeof(int), 0) < 0) {
      fprintf(stderr, "Recieve failed\n");
      exit(1);
    }
    
    char testStr[20];
    sprintf(testStr, "%d", updPort);
    perror(testStr);
    
    perror("test5");
    
    //upd
   // char* input="20001";
   struct sockaddr_in servaddr2;
   memset(&servaddr2, 0, sizeof(servaddr2));
   char* input="127.0.0.1";
   servaddr2.sin_family = AF_INET;
   servaddr2.sin_port = htons(SERV_PORT2);
   if (inet_pton(AF_INET, input, &servaddr2.sin_addr) < 0) {
    perror("inet_pton problem");
    exit(1);
    }
    
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket problem");
    exit(1);
    }
    perror("test6");
    int n=-1;
    char sendline[BUFSIZE], recvline[BUFSIZE + 1];
    *sendline="123TESTMESSAGE!";
  
    perror("upd send");
   
   //
   /*
    if (sendto(sockfd, sendline, n, 0, (SADDR *)&servaddr2, SLEN) == -1) {
      perror("sendto problem");
      exit(1);
    }
    */
    //
    clock_t start, stop;
unsigned long t;
start = clock ();
  perror("upd read");
 char closeStr[BUFSIZE];
 //strcpy(closeStr, sendline);
 strcpy(closeStr, "close");
    while ((n = read(0, sendline, BUFSIZE)) > 0) {
    //  while(1){
    //strcpy(closeStr, sendline);
    //strcpy(sendline, "close");
    sendline[n-1]='\0';
        printf("REPLY FROM SERVER= %s\n", sendline);
    if(!strcmp(sendline, closeStr)){
        perror("close upd");
        //if (recv(fd, &updPort, sizeof(int), 0) < 0) {
        int msg0=4;
        if(send(fd, &msg0, sizeof(int), 0) == -1){
          perror("sendto tcp faile");
          exit(1);
        }
    }
    if(strcmp(sendline, "stop")==0){
        perror("stop upd");
    }
         
    sprintf(testStr, "%d", n);
    perror(testStr);
        
    if (sendto(sockfd, sendline, n, 0, (SADDR *)&servaddr2, SLEN) == -1) {
      perror("sendto problem");
      exit(1);
    }
    
    perror("test7");

    if (recvfrom(sockfd, recvline, BUFSIZE, 0, NULL, NULL) == -1) {
      perror("recvfrom problem");
      exit(1);
    }
    perror("test8");
    printf("REPLY FROM SERVER= %s\n", recvline);
    //if(recvline)
}

//  }

    
 int f=0;

  //write(1, "Enter string\n", 13);
  //write(sockfd, "in", 2);
 // write(1, f, 22);
  //while ((nread = read(0, buf, BUFSIZE)) > 0) {
    //if (write(fd, f, nread) < 0) 
        //  perror("write");
    //  exit(1);
    //}
  //  printf(f++);
  //}
printf("test9");
  close(fd);
}

