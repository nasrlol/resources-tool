#ifndef TYPES_H
#define TYPES_H

typedef struct {

  char* name;
  char* frequency;
  int temperature;
  int threads;

} cpu_s;

typedef struct {
  long int total;
  long int available;
} ram_s;

typedef struct {
  long size;
  char *name;
} disk_s;

typedef struct { 

  char *name;
  char *hostname;
  char *os_version;
  int uptime;

} device_s;


extern cpu_s *u_cpu ;
extern ram_s *u_ram ;
extern disk_s *u_disk ;
extern device_s *u_device ;



#endif
