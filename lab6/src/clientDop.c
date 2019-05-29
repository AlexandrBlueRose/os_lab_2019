#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <time.h>

int BUFSIZE = -1;
int PORT = -1;
int STATE = -1;



int main(int argc, char * argv[]) {
  srand(time(NULL));
  char * ADDR;
  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{ "bufsize", required_argument, 0, 0},
                                      { "port", required_argument, 0, 0 },
                                      { "addr", required_argument, 0, 0 },
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
      case 2:
        ADDR = optarg;
        break;
      }

    case '?':
      break;

    default:
      printf("getopt returned character code 0%o?\n", c);
    }

  }
  if (BUFSIZE == -1) {
    printf("Usage: %s --bufsize \"buffer_size\" --port \"port\" --addr \"addr\"\n",
      argv[0]);
    return 1;
  }

  int sockfd, connfd;
  struct sockaddr_in serverIn;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed.\n");
    exit(0);
  } else
    printf("Socket successfully created\n");
  bzero( & serverIn, sizeof(serverIn));

  serverIn.sin_family = AF_INET;
  serverIn.sin_addr.s_addr = inet_addr(ADDR);
  serverIn.sin_port = htons(PORT);

  if (connect(sockfd, (SA * ) & serverIn, sizeof(serverIn)) != 0) {
    printf("connection with the server failed\n");
    exit(0);
  } else
    printf("connected to the server\n"); 
  clientConnect(sockfd);

  close(sockfd);
}

void clientConnect(int sockfd) {
  char buff[BUFSIZE];
  int n, syn, ack, x;
  for (;;) {
    //Функция bzero() устанавливает первые  sizeof(buff) байт области, 
    //начинающейся с buff, в ноль (байты, содержащие '\0')).
    bzero(buff, sizeof(buff));
    if (STATE == -1) {
      // send signal to server (syn)
      x = rand() % 500;
      printf("client:  x = %d\n", x);
      syn = x;
      printf("client: send syn to server x = %d\n", syn);
      //Функция sprintf() идентична printf(), за исключением того, 
      //что вывод производится в массив, указанный аргументом buf.
      snprintf(buff, sizeof(buff), "%d", syn);
      write(sockfd, buff, sizeof(buff));

      // получаем syn 
      bzero(buff, sizeof(buff));
      read(sockfd, buff, sizeof(buff));

      int * recived_data = (int * ) buff;
      ack = recived_data[0];
      syn = recived_data[1];

      printf("client: recive syn-ask from server ( ack = x + 1 = %d, seq = y = %d\n)", ack, syn);

      // переходим в режим ESTEBLISHED 
      if (ack == x + 1) {
        ack = syn + 1;
        syn = x + 1;
        printf("client: send ask to server( ack = y + 1 = %d, seq = x + 1 = %d\n)", ack, syn);
        int data_to_send[2] = {
          ack,
          syn
        };
        write(sockfd, data_to_send, sizeof(data_to_send));

        printf("client: established\n");
        STATE++;
      } else {
        printf("client: error ,sorry\n");
        printf("client exit\n");
        break;
      }
    } 
  }
}