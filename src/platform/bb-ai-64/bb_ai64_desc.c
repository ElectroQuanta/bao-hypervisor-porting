/**
 * @file bb_ai64_desc.c
 * @author Jose Pires
 * @date 2023-10-14
 *
 * @brief Beaglebone AI-64 Platform description for the Bao hypervisor
 *
 * See as references:
 * - Technical Reference Manual for the J721E DRA829/TDA4VM
 * Processors (available at
 * https://git.beagleboard.org/beagleboard/beaglebone-ai-64/-/tree/main/doc)
 * - Main device tree for the TI K3-J721E processor (available at
 * https://raw.githubusercontent.com/torvalds/linux/master/arch/arm64/boot/dts/ti/k3-j721e-main.dtsi)
 * - Device tree for the Beaglebone AI-64 (available at
 * https://raw.githubusercontent.com/torvalds/linux/master/arch/arm64/boot/dts/ti/k3-j721e-beagleboneai64.dts)
 *
 * @license SPDX-License-Identifier: Apache-2.0
 *
 * @copyright Bao Project and Contributors. All rights reserved.
 */


#include <platform.h>

#define GIC_GIC_PPI 9 /**< Interrupt for the GIC500 controller (in PPI) */
#define GIC_INTERRUPT (GIC_PPI_VAL(GIC_GIC_PPI))


#define RAM1_ADDR 0x80000000U
#define RAM1_SIZE 0x80000000U
#define RAM2_ADDR 0x880000000ULL
#define RAM2_SIZE 0x80000000U

#define CPU_NUM 2 /**< Dual-core A72 processor */

#define UART0_ADDR 0x2800000 /**< main_uart0: serial@2800000 (main.dtsi) */


struct platform platform = {
    .cpu_num = CPU_NUM, /**< Dual-core A72 processor */
    .region_num = 2,
    .regions =  (struct mem_region[]) {
        // // SRAM
        // {   /**< msmc_ram: sram@70000000 */
        //     .base = 0x70000000,
        //     .size = 0x800000
        // },
        // { /**< atf-sram@0 */
        //     .base = 0x0,
        //     .size = 0x20000
        //     //.size = ((BBAI64_MEM_GB-1) * 0x40000000ULL) - 0x4000000
        // },
        
        // 4GB RAM
        {
            .base = RAM1_ADDR,
            .size = RAM1_SIZE
        },
        {
            .base = RAM2_ADDR,
            .size = RAM2_SIZE
        }
        // Reserved memory
    },

    .console = {
        .base = UART0_ADDR /**< main_uart0: serial@2800000 (main.dtsi) */
    },

    .arch = {
// gic500: interrupt-controller@1800000 {
// 	compatible = "arm,gic-v3";
// 	#address-cells = <2>;
// 	#size-cells = <2>;
// 	ranges;
// 	#interrupt-cells = <3>;
// 	interrupt-controller;
// 	reg = <0x00 0x01800000 0x00 0x10000>,	/* GICD */
// 	      <0x00 0x01900000 0x00 0x100000>,	/* GICR */
// 	      <0x00 0x6f000000 0x00 0x2000>,	/* GICC */
// 	      <0x00 0x6f010000 0x00 0x1000>,	/* GICH */
// 	      <0x00 0x6f020000 0x00 0x2000>;	/* GICV */
// 	
// 	/* vcpumntirq: virtual CPU interface maintenance interrupt */
// 	interrupts = <GIC_PPI 9 IRQ_TYPE_LEVEL_HIGH>;
// }
        .gic = { /**< gic500: interrupt-controller@1800000 (main.dtsi) */
            .gicd_addr = 0x01800000,
            .gicr_addr = 0x01900000,
            .gicc_addr = 0x6f000000,
            .gich_addr = 0x6f010000,
            .gicv_addr = 0x6f020000,
            .maintenance_id = GIC_INTERRUPT
        },
    }
};
