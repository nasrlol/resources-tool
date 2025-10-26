#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

void get_cpu();
void get_ram();
void get_disk();
void get_device();

void get_c_version()
{

#if __STDC_VERSION__
  printf("C standard version: %ld\n", __STDC_VERSION__);
#else
  printf("C standard not defined\n");
#endif


}

#ifdef __APPLE__

int main(int argc, char** argv) {

  printf("%d", u_cpu->temperature);

  return 0;
}

#endif

#ifdef __gnu_linux

int main(int argc, char** argv) {


  return 0;

}

#endif

