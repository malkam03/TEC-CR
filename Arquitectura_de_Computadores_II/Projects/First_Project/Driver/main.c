#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/mman.h> 
#include "hwlib.h" 
#include "socal/socal.h"
#include "socal/hps.h" 
#include "socal/alt_gpio.h"
#include "hps_0.h"


#define REG_BASE 0xFF200000
#define REG_SPAN 0x00200000

void* virtual_base;
void* mem_addr;
int fd;
int switches;

int main (){
fd=open("/dev/mem",(O_RDWR|O_SYNC));
virtual_base=mmap(NULL,REG_SPAN,(PROT_READ|PROT_WRITE),MAP_SHARED,fd,REG_BASE);
mem_addr=virtual_base+VECTORIAL_MEM_0_BASE;
for(int i =0; i < chunk_size; i++){
	*(uint32_t *)mem_addr=switches;
}


return 0;




}