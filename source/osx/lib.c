
#ifdef __APPLE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include "cpu.h"

void* cpu_name();
void* cpu_thread_count();

cpu_s cpu;

void* cpu_name(){

    char *name;
    size_t len = 0;

    if (sysctlbyname("machdep.cpu.brand_string", NULL, &len, NULL, 0) < 0)
        perror("errorn in assigning the size for the cpu name variable\n");

    name = malloc(len);

    if(sysctlbyname("machdep.cpu.brand_string", name, &len, NULL, 0) < 0){
        perror("error in assigning the value to the cpu name variable\n");

        free(name);
        return NULL;
    }

    cpu.name = name;
    return NULL;
}

void* cpu_threads(){

    int count;
    size_t len = sizeof(count);
    if (sysctlbyname("machdep.cpu.thread_count", &count, &len, NULL, 0) < 0)
        perror("error in retrieving the cpu threads count\n");

    cpu.threads = count;
    return NULL;
}

void* cpu_info(){
    cpu_threads();
    cpu_name();

    printf("cpu name: %s\ncpu threads: %d\n", cpu.name, cpu.threads);
    return NULL;
}

#endif

#ifdef __APPLE__

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <device.h>

device_s device_info;

void* device_name(){

    char *name;
    size_t size = 0;

    if (sysctlbyname("kern.hostname", NULL, &size, NULL, 0) < 0)
        perror("failed retrieving the hostname: \n"); 

    name = malloc(size);

    if(sysctlbyname("kern.hostname", name, &size, NULL, 0) < 0){
        perror("failed retrieving the hostname: \n");
        free(name);
        return NULL;
    }

    device_info.name = name;
    return NULL;
}


void* device_model(){

    char *model_name;
    size_t size = 0;

    if (sysctlbyname("hw.model", NULL, &size, NULL, 0) < 0)
        perror("failed retrieving the hostname: \n"); 

    model_name = malloc(size);

    if(sysctlbyname("hw.model", model_name, &size, NULL, 0) < 0){
        perror("failed retrieving the hostname: \n");
        free(model_name);
        return NULL;
    }

    device_info.model = model_name;
    return NULL;

}

void* device_up_time(){


    
    return NULL;
}

void* device_os_version(){

    char *os_version;
    size_t size = 0;

    if (sysctlbyname("kern.ostype", NULL, &size, NULL, 0) < 0)
        perror("failed retrieving the hostname: \n"); 

    os_version = malloc(size);

    if(sysctlbyname("kern.ostype", os_version, &size, NULL, 0) < 0){
        perror("failed retrieving the os version: \n");
        free(os_version);
        return NULL;
    }

    device_info.model = os_version;
    return NULL;


}

void* get_device_info(){
    device_name();
    device_model();
    printf("device name: %s\ndevice model: %s\n", device_info.name, device_info.model);
    return NULL;
}

#endif


#include <stdlib.h>
#include "modules/cpu.h"
#include "modules/ram.h"
#include "modules/disk.h"
#include "modules/device.h"
#include <cjson/cJSON.h>

typedef struct {

   cpu_s* cpu;
   ram_s* ram;
   disk_s* disk;
   device_s* device;

} info;


cJSON convert_to_json(info info){

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "cpu", info.cpu->name);
    cJSON_AddNumberToObject(root, "ram", info.ram->total);
    cJSON_AddStringToObject(root, "disk", info.disk->name);
    cJSON_AddStringToObject(root, "device", info.device->name);

    return *root;
}


#ifdef __APPLE__

#include <stdlib.h>
#include <stddef.h>
#include "ram.h"
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/sysctl.h>

void size();
void av_size();
void* ram_i();


ram_s data;

#define D 1073741824


void size() {
    int64_t size;
    size_t len = sizeof(size);
    if (sysctlbyname("hw.memsize", &size, &len, NULL, 0) < 0)
        perror("error in retrieving the memory size");

    data.total = size / D;
    return NULL;
}

void av_size() {
    int64_t size;
    size_t len = sizeof(size);
    if (sysctlbyname("hw.memsize_usable", &size, &len, NULL, 0) < 0)
        perror("error in retrieving the available memory size");

    data.available = size / D;
    return NULL;
}

void ram_info() {
    size();
    av_size();

    printf("available ram: %LF\n", data.available);
    printf("total ram: %LF\n", data.total);

    return NULL;
}

void* ram_i(){

    printf("thread is working");
    return NULL;
}

#endif
