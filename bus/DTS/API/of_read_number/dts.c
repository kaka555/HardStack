/*
 * DTS: of_read_number
 *
 * static inline u64 of_read_number(const __be32 *cell, int size)
 *
 * (C) 2019.01.11 BuddyZhang1 <buddy.zhang@aliyun.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/*
 * Private DTS file: DTS_demo.dtsi
 *
 * / {
 *        DTS_demo {
 *                compatible = "DTS_demo, BiscuitOS";
 *                status = "okay";
 *                BiscuitOS-data = <0x10203040 0x50607080
 *                                  0x90a0b0c0 0xd0e0f000>;
 *        };
 * };
 *
 * On Core dtsi:
 *
 * include "DTS_demo.dtsi"
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/of_platform.h>
#include <linux/module.h>

/* define name for device and driver */
#define DEV_NAME "DTS_demo"

/* probe platform driver */
static int DTS_demo_probe(struct platform_device *pdev)
{
    struct device_node *np = pdev->dev.of_node;
    const __be32 *prop;
    int cells;
    u64 data64;
    u32 data32;

    printk("DTS probe entence...\n");

    /* Get #size-cells number */
    cells = of_n_size_cells(np);
    /* get proerpty */
    prop = of_get_property(np, "BiscuitOS-data", NULL);

    if (cells == 1) {
        data32 = of_read_number(prop, cells);
        printk("BiscuitOs-data u32 value: %#x\n", data32);
    } else if (cells == 2) {
        data64 = of_read_number(prop, cells);
        printk("BiscuitOS-data u64 value: %#llx\n", data64);
    }

    return 0;
}

/* remove platform driver */
static int DTS_demo_remove(struct platform_device *pdev)
{
    return 0;
}

static const struct of_device_id DTS_demo_of_match[] = {
    { .compatible = "DTS_demo, BiscuitOS",  },
    { },
};
MODULE_DEVICE_TABLE(of, DTS_demo_of_match);

/* platform driver information */
static struct platform_driver DTS_demo_driver = {
    .probe  = DTS_demo_probe,
    .remove = DTS_demo_remove,
    .driver = {
        .owner = THIS_MODULE,
        .name = DEV_NAME, /* Same as device name */
        .of_match_table = DTS_demo_of_match,
    },
};
module_platform_driver(DTS_demo_driver);
