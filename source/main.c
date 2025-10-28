#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "lib.h"

cpu_s *u_cpu;
ram_s *u_ram;
disk_s *u_disk;
device_s *u_device;

void init() {

  u_cpu = malloc( sizeof(cpu_s) );
  u_ram = malloc(sizeof(ram_s));
  u_disk = malloc(sizeof(disk_s));
  u_device = malloc(sizeof(device_s));

  cpu_name();
  cpu_frequency();
  cpu_threads();
  cpu_temperature();

  mem_size();
  mem_av_size();

  get_total();
  get_usage();

  device_os_version();
  device_model();
  device_up_time();
  device_model();

}

void end() {

  free(u_cpu);
  free(u_ram);
  free(u_disk);
  free(u_device);

}

int main() {

  init();

  printf("temperature: %d\nfrequency: %s\nname: %s\nthreads: %d\n", u_cpu->temperature, u_cpu->frequency, u_cpu->name, u_cpu->threads);
  printf("total: %ld\navailable: %ld\n", u_ram->total, u_ram->available);
  printf("device name:%s\ndevice hostname:%s\nos version: %s\nuptime: %d\n", u_device->name, u_device->hostname, u_device->os_version, u_device->uptime);

  while(1) {

    char *input = malloc(sizeof(char *));

    if(scanf("%s\n", input)) {


    }
  }

  end();
  return 0;
}


