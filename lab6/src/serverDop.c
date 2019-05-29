#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <getopt.h>
#include <netdb.h>
#include <time.h>

#define SA struct serverIn
int BUFSIZE = -1;
int PORT = -1;
int STATE = -1;



// Driver function 
int main(int argc, char * argv[]) {
  srand(time(NULL));
  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{ "bufsize", required_argument, 0, 0 },
                                      { "port", required_argument, 0, 0 },
                                      { 0, 0, 0, 0 }};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, & option_index);

    if (c == -1) break;

    switch (c) {
    case 0:
      switch (option_index) {
      case 0:
        BUFSIZE = atoi(optarg);
        if (BUFSIZE <= 0) {
          printf("BUFSIZE must be a positive number\n");
          return 1;
        }
        break;

      case 1:
        PORT = atoi(optarg);
        if (PORT <= 0) {
          printf("PORT must be a positive number\n");
          return 1;
        }
        break;
      }

    case '?':
      break;
      default:
      printf("getopt returned character code 0%o?\n", c);
  
    }

  }
  if (BUFSIZE == -1 || PORT == -1) {
    printf("Usage: %s --bufsize \"buffer_size\" --port \"port\"\n",
      argv[0]);
    return 1;
  }

  int sockfd, connfd, len;
  struct sockaddr_in serverIn, cli;

  // socket create and verification 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed.\n");
    exit(0);
  } else
    printf("socket successfully created\n");

  //Функция bzero() устанавливает первые sizeof(servaddr) байт области, 
  //начинающейся с servaddr, в ноль (байты, содержащие '\0')).
  bzero( & serverIn, sizeof(serverIn));

  serverIn.sin_family = AF_INET;
  serverIn.sin_addr.s_addr = htonl(INADDR_ANY);
  serverIn.sin_port = htons(PORT);
  
  //Эта функция используется сервером для присваивания сокету имени.
  //До выполнения функции bind (т.е. присваивания какого-либо имени, вид которого 
  //зависит от адресного домена ) сокет недоступен программам-клиентам.
  if ((bind(sockfd, (SA * ) & serverIn, sizeof(serverIn))) != 0) {
    printf("socket bind failed\n");
    exit(0);
  } else
    printf("Socket successfully binded\n");

  // Функция listen используется сервером, чтобы информировать ОС, что он ожидает ("слушает") запросы связи на данном сокете.
  if ((listen(sockfd, 5)) != 0) {
    printf("Listen failed\n");
    exit(0);
  } else
    printf("Server listening\n");
  len = sizeof(cli);
  
  //Эта функция используется сервером для принятия связи на сокет. 
  //Сокет должен быть уже слушающим в момент вызова функции. 
  connfd = accept(sockfd, (SA * ) & cli, & len);
  if (connfd < 0) {
    printf("server acccept failed\n");
    exit(0);
  } else
    printf("server acccept the client.\n");

  
  serverConnect(connfd);
  close(sockfd);
}


void serverConnect(int sockfd) {
  char buff[BUFSIZE];
  int n, syn, ack, y;
  for (;;) {
    bzero(buff, BUFSIZE);
    read(sockfd, buff, sizeof(buff));
    if (STATE == -1) {
      // принимаем syn
      sscanf(buff, "%d", & ack);
      printf("server: recived syn from client( ask=x = %d\n)", ack);
      
      ack++;
      y = rand() % 500;
      printf("server:  seq = %d\n", y);

      // отправляем ответ  в виде syn-asc
      bzero(buff, BUFSIZE);
      syn = y;
      int data_to_send[2] = {
        ack,
        syn
      };
      printf("server: send syn-ask to client( ack = x + 1 = %d, seq = y = %d\n)", ack, syn);
      write(sockfd, data_to_send, sizeof(data_to_send));

      // принимаем ask 
      bzero(buff, sizeof(buff));
      read(sockfd, buff, sizeof(buff));
      int old_seq = syn;

      int * recived_data = (int * ) buff;
      ack = recived_data[0];
      syn = recived_data[1];

      printf("server: recivrd ask from client (ack = y + 1 = %d, seq = x + 1 = %d\n)", ack, syn);

      // переходим в режим подключения
      if (ack == y + 1) {
        printf("server: established\n");
        STATE++;
      } else {
        printf("server: error\n");
        printf("server exit\n");
        break;
      }
    } 
  }
}