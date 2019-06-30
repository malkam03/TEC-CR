/* Necessary includes for device drivers */
#include <linux/init.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/uaccess.h> /* copy_from/to_user */
#include <linux/ioport.h>
#include <asm/io.h>
/*Local defined macros*/
#define BUF_LEN 80
#define DEVICE_NAME "timer"
#define SUCCESS 0
static unsigned RANGE =  0x404;
static unsigned TIMER_BASE =  0x3f00B000;
static char msg[BUF_LEN]; /* The msg the device will give when asked */
static char *msg_Ptr;
static int Device_Open = 0; /* Is device open?  */
u8 *addr;
MODULE_LICENSE("GPL v2");
/* Declaration of timer.c functions */
int timer_open(struct inode *inode, struct file *filp);
int timer_release(struct inode *inode, struct file *file);
ssize_t timer_read(struct file *filp, char *buffer,
size_t length, loff_t * offset);
ssize_t timer_write(struct file *filp, const char *buffer,
size_t length, loff_t * offset));
void timer_exit(void);
int timer_init(void);
/* Structure that declares the usual file */
/* access functions */
struct file_operations timer_fops = {
    read: timer_read,
    write: timer_write,
    open: timer_open,
    release: timer_release
};
/* Declaration of the init and exit functions */
module_init(timer_init);
module_exit(timer_exit);
/* Global variables of the driver */
/* Major number */
int timer_major = 60;
/*********Functions*********/
/* Device init*/
int timer_init(void) {
    int result;
    /* Registering device */
    result = register_chrdev(timer_major, DEVICE_NAME, &timer_fops);
    if (result < 0) {
        printk("<1>timer: cannot obtain major number %d\n", timer_major);
        return result;
    }
    /*Reserve timer memory region */
    if(request_mem_region(TIMER_BASE, RANGE, DEVICE_NAME) == NULL) {
        printk("<1>timer: cannot reserve memory \n");
        unregister_chrdev(timer_major, DEVICE_NAME);
        return -ENODEV;
    }
    printk("<1>Inserting timer module... :)\n");
    /*Generate new address required for iowrite and ioread methods*/
    addr = ioremap(TIMER_BASE, RANGE);
    /* Set free running frequency to half of sys_freq*/
    u32 cmd = 0x00010020;
    /*Write to Timer Control Register*/
    iowrite32(cmd, (addr+ 0x408));
    /*Check it has been configured*/
    printk("timer: Timer control set to 0x%08x\n", ioread32(addr+ 0x408));
    return SUCCESS;
}

void timer_exit(void) {
    /* Freeing the major number and memory space */
    unregister_chrdev(timer_major, DEVICE_NAME);
    release_mem_region(TIMER_BASE, RANGE);
    printk("<1>Removing timer module\n");
}

int timer_open(struct inode *inode, struct file *filp) {
    printk("<1>Opening timer module\n");
    /*Avoid reading conflicts*/
    if (Device_Open)
        return -EBUSY;
    Device_Open++;
    return SUCCESS;
}

int timer_release(struct inode *inode, struct file *file){
    printk("<1>Releasing  timer module...\n");
    Device_Open--;      //make ready for the next caller*/
    return SUCCESS;
}

ssize_t timer_write(struct file *filp, char *buffer,
                    size_t length, loff_t * offset){
    printk("<1>Writing to timer module...\n");
    u32 cmd;
    if (buffer) {
        /* if ascii 0*/
        if (buffer[0] == 48) {
            /*Stop timer - bit 9 OFF*/
            cmd = 0x003E0020;
            iowrite32(cmd, (addr+ 0x408));
            printk("timer: OFF \n");
        }
        else {
            /*if ascii 1*/
            if (buffer[0] == 49){
                /*Start timer - bit 9 ON*/
                cmd = cmd = 0x00010220;
                iowrite32(cmd, (addr+ 0x408));
                printk("timer: ON \n");
            }
        }
    }
    /*Buffer contains only 1 char (0-1)
    returns "1 byte written"*/
    return 1;
}

ssize_t timer_read(struct file *filp, char *buffer,
                    size_t length, loff_t * offset){
    int index;
    u32 res;
    msg_Ptr = msg;
    int nbytes = 8;
    if (*offset == 0) {
        /* Reading FRCR*/
        res = ioread32(addr+0x420);
        /*Mask to get bytes of message*/
        msg[3] = res & 0xFF;
        msg[2] = (res >> 8) & 0xFF;
        msg[1] = (res >> 16) & 0xFF;
        msg[0] = (res >> 24) & 0xFF;
        /*Convert to Hex ASCII */
        sprintf(msg, "%02hhx%02hhx%02hhx%02hhx",
        msg[3],msg[2],msg[1], msg[0]);
        /*Copy to user buffer*/
        copy_to_user(buffer,msg,nbytes);
        *offset+=1;
        printk("timer: timer count = %d \n", res);
        return nbytes;
    } else
        return SUCCESS;
}