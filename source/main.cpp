/*
 * Author: nasr
 * Year: 2025-2026
 * */

#include <unistd.h>
#include <stdint.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO(nasr): create and start virtual machines using KVM - QEMU - LIBVIRT
// #include <libvirt/libvirt.h>

#define MAXC_CHAR 256


typedef struct {

	uint8_t *base; 
	size_t idx;
	size_t cap;

} Arena;

	Arena 
*ArenaAlloc(void) 
{

	return NULL;

}

	void
*ArenaRelease(Arena *arena) 
{

	return NULL;

}

	Arena
*ArenaPush(Arena *arena, size_t bytes)
{

	return NULL;
}

	void
ArenaPop(Arena *arena)
{

}

	uint64_t
ArenaGetPos(Arena *arena)
{

	return 0;
}

	void
ArenaClear(Arena *arena)
{
	// TODO(nasr): check if there is more needed to do here
	free(arena);
}

typedef struct 
{

	char vendor[MAXC_CHAR]; 
	char model[MAXC_CHAR]; 
	char frequency[MAXC_CHAR]; 
	char cores[MAXC_CHAR]; 

} Cpu;

typedef struct 
{
	char* total;
	char* free;
} Ram;

typedef struct 
{
	long size;
	char *name;
} Disk;

typedef struct 
{ 

	char *hostname;
	char *os_version;
	int uptime;
	uint16_t procs;

} Device;


// math heper functions
// @param takes a base and an exponent
int
pow(int base, int exp) 
{

	uint64_t result = 0;
	for (int i = 0; i < exp; ++i) {

		result *= base;
	}

	return result;

	return 0;
}

int
pow(double base, double exp) 
{

	float result = 0;

	for (int i = 0; i < exp; ++i) {

		result *= base;
	}

	return result;
}


void
cpu_data(Cpu *cpu) 
{
	char basic_cpu_info[]	= "/proc/cpuinfo";

	char vendor_id[]		= { "vendor_id"};
	char model[]			= { "model name"};
	char frequency[]		= { "cpu MHz"};
	char cores[]			= { "cpu cores"};

	FILE *file = fopen(basic_cpu_info, "r");
	if (!file)
	{
		//TODO(nasr): write this to the created agent log system
		return;
	}

	char buffer[MAXC_CHAR] = "";
	while(fgets(buffer, sizeof(buffer), file) != NULL)
	{
		char *colon = strchr(buffer, ':');
		if (!colon)
			continue; 

		char *start = colon + 1;
		 
		while (*start == ' ')
			start++;

		char *end = strchr(start, '\n');

		if (!end)
			end = start + strlen(start);

		size_t length = (size_t)(end - start);

		if ((strncmp(buffer, vendor_id, sizeof(vendor_id) - 1)) == 0) 
		{
			memcpy(cpu->vendor, start, length);
			cpu->vendor[length] = '\0';
		}

		if ((strncmp(buffer, model, sizeof(model) - 1)) == 0) 
		{
			memcpy(cpu->model, start, length);
			cpu->model[length] = '\0';
		}

		if ((strncmp(buffer, frequency , sizeof(frequency) - 1)) == 0) 
		{
			memcpy(cpu->frequency, start, length);
			cpu->frequency[length] = '\0';
		}

		if ((strncmp(buffer, cores, sizeof(cores) - 1)) == 0) 
		{
			memcpy(cpu->cores, start, length);
			cpu->cores[length] = '\0';
		}
	}

	fclose(file);
}

void
memory_data(Ram *ram) 
{

	char mem_info[]	= "/proc/meminfo";

	char total[]		= { "MemTotal"};
	char free[]			= { "MemFree"};

	FILE *file = fopen(mem_info, "r");
	if (!file)
	{
		//TODO(nasr): write this to the created agent log system
		return;
	}

	char buffer[MAXC_CHAR] = "";
	while(fgets(buffer, sizeof(buffer), file) != NULL)
	{
		char *colon = strchr(buffer, ':');
		if (!colon)
			continue; 

		char *start = colon + 1;
		 
		while (*start == ' ')
			start++;

		char *end = strchr(start, '\n');

		if (!end)
			end = start + strlen(start);

		size_t length = (size_t)(end - start);

		if ((strncmp(buffer, total, sizeof(total) - 1)) == 0) 
		{
			memcpy(ram->total, start, length);
			ram->total[length] = '\0';
		}

		if ((strncmp(buffer, total, sizeof(total) - 1)) == 0) 
		{
			memcpy(ram->total, start, length);
			ram->free[length] = '\0';
		}
	}
	fclose(file);

}

void
disk_data(Disk *disk) 
{
	char disk_info[]	= "/proc/diskstats";
	FILE *file = fopen(disk_info, "r");
	if (!file)
	{
		fclose(file);
		return;
	}

	fclose(file);
}


char *uptime(const char *path)
{
	FILE *file = fopen(path, "r");
	if (!file)
		return NULL;

	char *buffer = (char*)malloc(MAXC_CHAR);
	if (!buffer)
		return NULL;


	char *content = fgets(buffer, sizeof(*buffer), file);
	if (!content)
		return NULL;

	fclose(file);
	return content;

}

char* os_version(const char *path)
{
	FILE *file = fopen(path, "r");
	if (!file)
		return NULL;

	char *buffer = (char*)malloc(MAXC_CHAR);

	char *content = fgets(buffer, sizeof(*buffer), file);
	if (!content)
		return NULL;

	fclose(file);
	return content; 

}


void
device_data(Device *device) 
{
	const char *uptime_path = "/proc/uptime";
	const char *os_version_path = "/proc/os_version";

	if (device->uptime == NULL)
	{
		device->uptime = uptime(uptime_path);
		device->os_version = os_version(os_version_path);
	}


}

int 
main() 
{
	// Arena *arena; 
	//
	Cpu *cpu;
	Ram *ram;
	Device *device;
	Disk *disk;
	//
	// ArenaPush(arena, sizeof(Cpu));
	// ArenaPush(arena, sizeof(Ram));
	// ArenaPush(arena, sizeof(Disk));
	// ArenaPush(arena, sizeof(Device));
	//
	// ArenaAlloc();
	//
	// cpu_data(cpu);
	// memory_data(ram);
	// device_data(device);
	//
	// ArenaRelease(arena);

	cpu_data(cpu);
	return 0;
}


// TODO(nasr): find a way to use libvirt to create and start a virtual machine
// TODO(nasr): find a way to pass parameters to libvirt

void
create_vm()
{

	// TODO(nasr): create and start virtual machines using libirt

}

