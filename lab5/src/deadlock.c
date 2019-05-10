/********************************************************
 * An example source module to accompany...
 *
 * "Using POSIX Threads: Programming with Pthreads"
 *     by Brad nichols, Dick Buttlar, Jackie Farrell
 *     O'Reilly & Associates, Inc.
 *  Modified by A.Kostin
 ********************************************************
 * mutex.c
 *
 * Simple multi-threaded example with a mutex lock.
 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void do_one_thing(int *);
void do_one_thing2(int *);
void do_another_thing(int *);
void do_another_thing2(int *);
void do_wrap_up(int);
int common = 0; /* A shared variable for two threads */
int r1 = 0, r2 = 0, r3 = 0;
pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut4 = PTHREAD_MUTEX_INITIALIZER;
int main() {
  pthread_t thread1, thread2,thread3,thread4;

  if (pthread_create(&thread1, NULL, (void *)do_one_thing,
			  (void *)&common) != 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_create(&thread2, NULL, (void *)do_another_thing,
                     (void *)&common) != 0) {
    perror("pthread_create");
    exit(1);
  }
  if (pthread_create(&thread3, NULL, (void *)do_one_thing2,
			  (void *)&common) != 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_create(&thread4, NULL, (void *)do_another_thing2,
                     (void *)&common) != 0) {
    perror("pthread_create");
    exit(1);
  }

  if (pthread_join(thread1, NULL) != 0) {
    perror("pthread_join");
    exit(1);
  }

  if (pthread_join(thread2, NULL) != 0) {
    perror("pthread_join");
    exit(1);
  }
  
  if (pthread_join(thread3, NULL) != 0) {
    perror("pthread_join");
    exit(1);
  }

if (pthread_join(thread4, NULL) != 0) {
    perror("pthread_join");
    exit(1);
  }


  do_wrap_up(common);

  return 0;
}

void do_one_thing(int *pnum_times) {
  int i, j, x;
  unsigned long k;
  int work;
  pthread_mutex_lock(&mut1);
  for (i = 0; i < 50; i++) {
    pthread_mutex_lock(&mut1);
    printf("doing one thing1\n");
    work = *pnum_times;
    printf("counter = %d\n", work);
    work++; /* increment, but not write */
    for (k = 0; k < 500000; k++)
      ;                 /* long cycle */
    *pnum_times = work; /* write back */
	pthread_mutex_unlock(&mut1);
  }
  pthread_mutex_lock(&mut2);
  work++;
  pthread_mutex_unlock(&mut2);
  pthread_mutex_unlock(&mut1);
  pthread_mutex_unlock(&mut3);
  pthread_mutex_unlock(&mut4);
}

void do_another_thing(int *pnum_times) {
  int i, j, x;
  unsigned long k;
  int work;
  pthread_mutex_lock(&mut2);
  for (i = 0; i < 50; i++) {
    //pthread_mutex_lock(&mut1);
    printf("doing one thing2\n");
    work = *pnum_times;
    printf("counter = %d\n", work);
    work++; /* increment, but not write */
    for (k = 0; k < 500000; k++)
      ;                 /* long cycle */
    *pnum_times = work; /* write back */
    pthread_mutex_unlock(&mut2);
  }
  pthread_mutex_lock(&mut1);
  work++;
  pthread_mutex_unlock(&mut2);
  pthread_mutex_unlock(&mut1);
  pthread_mutex_unlock(&mut3);
  pthread_mutex_unlock(&mut4);
}
void do_one_thing2(int *pnum_times) {
  int i, j, x;
  unsigned long k;
  int work;
  pthread_mutex_lock(&mut3);
  for (i = 0; i < 50; i++) {
    pthread_mutex_lock(&mut1);
    printf("doing one thing3\n");
    work = *pnum_times;
    printf("counter = %d\n", work);
    work++; /* increment, but not write */
    for (k = 0; k < 500000; k++)
      ;                 /* long cycle */
    *pnum_times = work; /* write back */
	pthread_mutex_unlock(&mut3);
  }
  pthread_mutex_lock(&mut3);
  work++;
  pthread_mutex_unlock(&mut2);
  pthread_mutex_unlock(&mut1);
  pthread_mutex_unlock(&mut3);
  pthread_mutex_unlock(&mut4);
}

void do_another_thing2(int *pnum_times) {
  int i, j, x;
  unsigned long k;
  int work;
  pthread_mutex_lock(&mut4);
  for (i = 0; i < 50; i++) {
    //pthread_mutex_lock(&mut1);
    printf("doing one thing4\n");
    work = *pnum_times;
    printf("counter = %d\n", work);
    work++; /* increment, but not write */
    for (k = 0; k < 500000; k++)
      ;                 /* long cycle */
    *pnum_times = work; /* write back */
    pthread_mutex_unlock(&mut4);
  }
  pthread_mutex_lock(&mut4);
  work++;
  pthread_mutex_unlock(&mut2);
  pthread_mutex_unlock(&mut1);
  pthread_mutex_unlock(&mut3);
  pthread_mutex_unlock(&mut4);
}

void do_wrap_up(int counter) {
  int total;
  printf("All done, counter = %d\n", counter);
}