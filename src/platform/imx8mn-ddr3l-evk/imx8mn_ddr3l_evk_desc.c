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


#define RAM1_ADDR 0x40000000U
#define RAM1_SIZE 0x80000000U

#define CPU_NUM 4 /**< Quad-core A52 processor */

#define UART1_ADDR 0x30890000 /**< serial1 (uart2): serial@30860000 (main.dtsi) */


struct platform platform = {
    .cpu_num = CPU_NUM, /**< Dual-core A72 processor */
    .region_num = 1,

/**
 * src: imx8mn-dd3rl-evk.dts
 * RAM memory
 *
 *	memory@40000000 {
 *		device_type = "memory";
 *		reg = <0x00 0x40000000 0x00 0x80000000>;
 *	};
 */
    .regions =  (struct mem_region[]) {
        // 3GB RAM
        {
            .base = RAM1_ADDR,
            .size = RAM1_SIZE
        }
        // Reserved memory
    },

    .console = {
        .base = UART1_ADDR /**< serial1: (main.dtsi) */
    },

    .arch = {
        .clusters =  {
            .num = 1,
            .core_num = (size_t[]) {4}
        },
//    gic: interrupt-controller@38800000 {
//            compatible = "arm,gic-v3";
//            reg = <0x38800000 0x10000>,
//            <0x38880000 0xc0000>;
//#interrupt-cells = <3>;
//            interrupt-controller;
//            interrupts = <GIC_PPI 9 IRQ_TYPE_LEVEL_HIGH>;
//        };
// 	
// }
        .gic = { /**< gic500: interrupt-controller@1800000 (main.dtsi) */
            .gicd_addr = 0x38800000,
            .gicr_addr = 0x38800000,
            .gicc_addr = 0x6f000000, /**< Dont care */
            .gich_addr = 0x6f010000, /**< Dont care */
            .gicv_addr = 0x6f020000, /**< Dont care */
            .maintenance_id = GIC_INTERRUPT
        },
    }
};
