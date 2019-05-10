#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <getopt.h>

#include <stdint.h>

#include <pthread.h>

struct FactorialArgs {
  pthread_mutex_t* mut;
  int mod;
  int *value;
  int start;
  int end;
};

void factorial(void* args);

int main(int argc, char **argv)
{
  pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
  int k=-1;
  int pnum=-1;
  int mod = -1;
  
  //
  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"pnum", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {"k", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            pnum = atoi(optarg);
            if(pnum<0){
                printf("error pnum must be > 0 !\n");
                return 1;
            }
            break;
          case 1:
            mod = atoi(optarg);
            if(mod<0){
                printf("error mod must be > 0 !\n");
                return 1;
            }
            break;
            case 2:
            k = atoi(optarg);
            if(k<0){
                printf("error k must be > 0 !\n");
                return 1;
            }
            break;
          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (mod == -1 || pnum == -1 || k == -1) {
    printf("Usage: %s --pnum \"num\" --mod \"num\" \n",
           argv[0]);
    return 1;
  }
if(pnum>k){
    printf("error k must be >= pnum !\n");
    return 1;
}
//
struct FactorialArgs *fArgs = malloc(sizeof(struct FactorialArgs) * pnum);
pthread_t *threads = malloc(sizeof(pthread_t) * pnum);
int delta = (k+1)/pnum;
int value = 1;
 /*
  pthread_mutex_t* mut;
  int mod;
  int *value;
  int start;
  int end;
 */
for(int i = 0; i<pnum; i++){
    fArgs[i].mod=mod;
    fArgs[i].mut=&mut;
    fArgs[i].value=&value;
    fArgs[i].start=i*delta;
    if(i==0)
        fArgs[i].start=1;
    if(i<(pnum-1)){
        fArgs[i].end=(i+1)*delta;
    }
    else{
        fArgs[i].end=k+1;
    }
    //
    if (pthread_create(&(threads[i]), NULL, (void *)factorial, (void *)&(fArgs[i])) != 0) {
        perror("pthread_create");
        exit(1);
    }
}
//
for(int i = 0; i<pnum; i++){
    if (pthread_join(threads[i], NULL) != 0) {
        perror("pthread_join");
        exit(1);
    } 
}
//
free(fArgs);
free(threads);
printf("All done, value = %d\n", value);
return 0;
}
//
void factorial(void* args){
    struct FactorialArgs arg = *((struct FactorialArgs*)args);
    int value = 1;
    for(int i = arg.start; i<arg.end; i++){
        value = value*(i%(arg.mod));
    }
    pthread_mutex_lock(arg.mut);
    //mut
    *(arg.value) = (*(arg.value))*value;
    //
    pthread_mutex_unlock(arg.mut);
}