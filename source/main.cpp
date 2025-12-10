/*
 * Author: nasr
 * Year: 2025-2026
 *
 */

#include <cstdint>
#include <cstdlib>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>

#define MAXC 1024
#define MAXC_CHAR 256
#define CONVERT_BYTES_TO_GIGABYTES 107374182   
#define D 1073741824

#define forever for(;;)

typedef struct {

	// TODO: create the arena struct

} Arena;

typedef struct {

	char* name;
	char* frequency;
	int temperature;
	int threads;

} Cpu;

typedef struct {
	double total;
	double available;
} Ram;

typedef struct {
	long size;
	char *name;
} Disk;

typedef struct { 

	char *hostname;
	char *os_version;
	int uptime;
	uint16_t procs;

} Device;


Arena *ArenaAlloc(void);
Arena *ArenaRelease(void);

template <typename T>
Arena *ArenaPush(Arena *arena, T);

template <typename T>
Arena *ArenaPushZero(Arena *arena, T);

template <typename T> 
void ArenaPop(Arena *arena, T);
uint64_t ArenaGetPos(Arena *arena); 

void ArenaClear(Arena *arena);

void cpu_data(Cpu *cpu);
void memory_data(Ram *ram);
void device_data(Device *device);

int 
main() {

	// TODO: get disk information

	Cpu		*cpu		= (Cpu*)malloc( sizeof(Cpu) );
	Ram		*ram		= (Ram*)malloc(sizeof(Ram));
	Device	*device		= (Device*)malloc(sizeof(Device));

	// disk	= (Disk*)malloc(sizeof(Disk));

	cpu_data(cpu);
	memory_data(ram);
	device_data(device);

	printf("gathering system resources...");
	printf("\ntemperature: %d\nfrequency: %s\nname: %s\nthreads: %d\n", cpu->temperature, cpu->frequency, cpu->name, cpu->threads);
	printf("total: %f\navailable: %f\n", ram->total, ram->available);
	printf("hostname:%s\nos version: %s\nuptime: %d\nprocs: %d\n", device->hostname, device->os_version, device->uptime, device->procs);

	free(cpu);
	free(ram);
	// free(disk);
	free(device);

	return 0;
}





void
cpu_data(Cpu *cpu) {

	cpu->name	= (char*)malloc(sizeof(char) * MAXC_CHAR);
	char *buffer = (char*)malloc(sizeof(char) * MAXC_CHAR);

	FILE *fp = fopen("/proc/cpuinfo", "r");
	if (!fp) perror("can't open /proc/cpuinfo");

	char line[MAXC_CHAR];
	while (fgets(line, MAXC_CHAR, fp)) {
		if (strncmp(line, "model name",  sizeof(cpu->name)) == 0) {
			char *colon = strchr(line, ':');
			if (colon) {
					cpu->name[strcspn(cpu->name, "\n")] = 0;
					snprintf(cpu->name, MAXC_CHAR, "%s", colon);
			}

			if (strstr(line, "cpu MHz") != NULL) {
				colon = NULL;
				colon = strchr(buffer, ':');
				if (colon) {
					snprintf(buffer, MAXC_CHAR, "%s", colon);
					cpu->frequency = buffer;
				}
			}
		}
	}

	fclose(fp);
	fp = NULL;

#define delay 1

	fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
	if (!fp)
		printf("error reading /proc/cpuinfo");

	while (fgets(buffer, sizeof(buffer), fp)) {
		int a = atoi(buffer);
		a /= 1000;
		cpu->temperature = a;
		fflush(stdout);
	}
	fclose(fp);
}


void
memory_data(Ram *ram) {

	struct sysinfo info;

	if (sysinfo(&info) != 0) {
		perror("sysinfo");
		return;
	}

	long total_ram = info.totalram * info.mem_unit; 

	if (sysinfo(&info) != 0) {
		perror("sysinfo");
	}

	long free_ram = info.freeram * info.mem_unit;

	ram->available	= free_ram / pow(10, 8);
	ram->total		= total_ram /  pow(10, 8);

}

void
disk_data(Disk *disk) 
{

	// TODO: return disk data

}


void
device_data(Device *device) {
	struct sysinfo info;
	if (sysinfo(&info) == -1)
		perror("sysinfo");

	device->uptime = info.uptime;
	device->procs = info.procs;	

	FILE *fp = fopen("/etc/hostname", "r");
	char* buffer = (char*)malloc(sizeof(char) * MAXC_CHAR);

	device->hostname = fgets(buffer, MAXC_CHAR, fp);

	fclose(fp);

	free(buffer);
		
	fp = fopen("/etc/os-release", "r");
	void *err = realloc(buffer,  MAXC_CHAR);

	device->os_version = fgets(buffer, MAXC_CHAR, fp);

	free(fp);
}

