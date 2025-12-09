/*
 * 
 * Author: nasr
 * Year: 2025-2026
 *
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/sysinfo.h>

#define MAXC 1024
#define MAXC_CHAR 256
#define CONVERT_BYTES_TO_GIGABYTES 107374182   
#define D 1073741824


void cpu_name();
void cpu_threads();
void cpu_temperature();
void cpu_frequency();

void get_total();
void get_usage();

void av_size();
void ram_info();

void mem_size();
void mem_av_size();

void device_os_version();
void device_model();
void device_up_time();
void device_model();


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


cpu_s *u_cpu;
ram_s *u_ram;
disk_s *u_disk;
device_s *u_device;

void init() {

	u_cpu = (cpu_s*)malloc( sizeof(cpu_s) );
	u_ram = (ram_s*)malloc(sizeof(ram_s));
	u_disk =(disk_s*) malloc(sizeof(disk_s));
	u_device = (device_s*)malloc(sizeof(device_s));

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

	// free program
	end();


	return 0;
}



void
cpu_name() {

	int *buffer_size = (int*)malloc(sizeof(int));
	char *cpu_name = (char*)malloc(sizeof(char));

	FILE *fp = fopen("/proc/cpuinfo", "r");
	if (!fp) perror("can't open /proc/cpuinfo");

	char line[sizeof(cpu_name)];
	while (fgets(line, sizeof(line), fp)) {
		if (strncmp(line, "model name", 10) == 0) {
			char *colon = strchr(line, ':');
			if (colon) {
				int err = fclose(fp);
				if (err != 0)
					perror("error closing /proc/cpuinfo");
			}
		}
	}

	u_cpu->name = cpu_name;

}

void
cpu_frequency() {
	char* buffer = (char*)malloc(MAXC_CHAR);

	FILE *fp = fopen("/proc/cpuinfo", "r");
	if (!fp) {
		printf("can't open /proc/cpuinfo");
		return;
	}

	while (fgets(buffer, MAXC_CHAR, fp)) {
		if (strstr(buffer, "cpu MHz") != NULL) {
			char *colon = strchr(buffer, ':');
			if (colon) {
				buffer[strcspn(buffer, "\n")] = 0;
				snprintf(buffer, MAXC_CHAR, "%s", colon);
			}
		}

		fclose(fp);
		u_cpu->frequency = buffer;
	}
	return;
}

void
mem_size() {

	struct sysinfo info;

	if (sysinfo(&info) != 0) {
		perror("sysinfo");
		return;
	}

	long total_ram = info.totalram * info.mem_unit; 
	u_ram->total = total_ram;

}


void
mem_av_size() {
	struct sysinfo info;

	if (sysinfo(&info) != 0) {
		perror("sysinfo");
	}

	long total_ram = info.totalram * info.mem_unit;
	long free_ram = info.freeram * info.mem_unit;

	u_ram->available = free_ram;
}


void
cpu_temperature() {

	int delay = 0;
	while (1) {
		sleep(delay);
		FILE *pf = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
		if (!pf)
			printf("error reading /proc/cpuinfo");

		char buffer[MAXC];
		while (fgets(buffer, sizeof(buffer), pf)) {
			int a = atoi(buffer);
			a /= 1000;
			printf("cpu temperature: %dC\n", a);
			fflush(stdout);
		}
		fclose(pf);
	}
}


void
device_up_time() {
	struct sysinfo info;
	if (sysinfo(&info) == -1)
		perror("sysinfo");

	u_device->uptime = info.uptime;
}


void
device_model() {

	// TODO(nasr): 

	return;

}

void
cpu_threads() {

	// TODO(nasr): 
	return;
}

void
get_total() {


	// TODO(nasr): 
}

void
get_usage() {


	// TODO(nasr): 
}

void
device_os_version() {

	// TODO(nasr): 

}

