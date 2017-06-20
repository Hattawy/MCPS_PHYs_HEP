#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x60d90935, "module_layout" },
	{ 0xf25aaa6e, "usb_deregister" },
	{ 0x52bfbc74, "usb_register_driver" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xe914e41e, "strcpy" },
	{ 0x97b61c1f, "usb_control_msg" },
	{ 0x2b42df66, "mutex_unlock" },
	{ 0x90269879, "mutex_lock" },
	{ 0x86a4889a, "kmalloc_order_trace" },
	{ 0xebb9eced, "usb_register_dev" },
	{ 0xba236513, "kmem_cache_alloc_trace" },
	{ 0xc6177942, "kmalloc_caches" },
	{ 0x50afd589, "usb_deregister_dev" },
	{ 0x97f67b83, "dev_set_drvdata" },
	{ 0x89ae6e69, "dev_get_drvdata" },
	{ 0x37a0cba, "kfree" },
	{ 0x4e16bec, "usb_clear_halt" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0x50eedeb8, "printk" },
	{ 0x30f1f11d, "usb_bulk_msg" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0xb9c656ea, "current_task" },
	{ 0xeb7c47a7, "__mutex_init" },
	{ 0xe174aa7, "__init_waitqueue_head" },
	{ 0x57b09822, "up" },
	{ 0x1a925a66, "down" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0547p1002d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v21E1p0000d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v21E1p0001d*dc*dsc*dp*ic*isc*ip*");
MODULE_ALIAS("usb:v21E1p0005d*dc*dsc*dp*ic*isc*ip*");

MODULE_INFO(srcversion, "8D9E1150BB67F8447FD6216");
