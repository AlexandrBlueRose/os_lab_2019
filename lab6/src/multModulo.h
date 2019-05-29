#ifndef MULTMODULO_H
#define MULTMODULO_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <getopt.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>


uint64_t MultModulo(uint64_t a, uint64_t b, uint64_t mod);

#endif