// Scrieti un program C ls-more.c care emuleaza urmatoarea comanda shell:
//$ ls -l | less
//Programul creeaza in procesul parinte un pipe si doua procese copil, primul responsabil de executia
//comenzii ls -l, iar cel de-al doilea pentru comanda less. Dupa ce a creat procesele copil, procesul
//parinte se blocheaza asteptand terminarea lor si recupereaza starea lor de terminare.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

