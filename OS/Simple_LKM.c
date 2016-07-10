#include<linux/kernel.h>
#include<linux/module.h>

char khello_msg[] __initdata = "greetings from kernel space !";
//char khello_msg[] = "greetings from kernel space !";

void __init greet(void)
//void greet(void)
{
	pr_notice("greet(): %s\n",khello_msg);	
}


int __init khello_init(void)
//int khello_init(void)
{
	pr_notice("loaded!\n");"
	//pr_notice("khello_init: %s\n",khello_msg);
	return 0;
}

void khello_exit(void)
{
	pr_notice("khello_exit: called !\n");
}

module_init(khello_init);
module_exit(khello_exit);

//Module-section : Module Headers in LKM binary	
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SACHIN BHAVARI");
MODULE_DESCRIPTION("A simple hello world module");
