#include <linux/kernel.h>
#include <linux/kmain.h>

asmlinkage long sys_ukl(void)
{
        printk("In UKL syscall\n");
        kmain();
        return 0;
}