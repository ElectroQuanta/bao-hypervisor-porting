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

/**< RAM: imx8mn-dd3rl-evk.dts */
//
//	memory@40000000 {
//		device_type = "memory";
//		reg = <0x00 0x40000000 0x00 0x80000000>;
//	};
#define RAM1_ADDR 0x40000000
#define RAM1_SIZE 0x80000000

#define CPU_NUM 4 /**< Quad-core A52 processor */

/**< imx-uboot/arch/arm/dts/imx8mn-evk.dts */
// / {
// 	model = "NXP i.MX8MNano EVK board";
// 	compatible = "fsl,imx8mn-evk", "fsl,imx8mn";
// 
// 	chosen {
// 		bootargs = "console=ttymxc1,115200 earlycon=ec_imx6q,0x30890000,115200";
// 	};
// 
// };
/**< imx8mn.dtsi */
// uart2: serial@30890000 {
//     compatible = "fsl,imx8mn-uart", "fsl,imx6q-uart";
//     reg = <0x30890000 0x10000>;
//     interrupts = <GIC_SPI 27 IRQ_TYPE_LEVEL_HIGH>;
//     clocks = <&clk IMX8MN_CLK_UART2_ROOT>,
//         <&clk IMX8MN_CLK_UART2_ROOT>;
//     clock-names = "ipg", "per";
//     status = "disabled";
// };
/**< imx8mn-evk.dtsi */
//chosen {
//	stdout-path = &uart2;
//};
#define UART2_ADDR 0x30890000


/**< GIC: imx8mn.dtsi */
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
#define GICD_ADDR 0x38800000
#define GICR_ADDR 0x38880000
#define GIC_GIC_PPI 9 /**< Interrupt for the GIC500 controller (in PPI) */
#define GIC_INTERRUPT (GIC_PPI_VAL(GIC_GIC_PPI))


struct platform platform = {
    .cpu_num = CPU_NUM, /**< Dual-core A72 processor */
    .region_num = 1,

    .regions =  (struct mem_region[]) {
        // 3GB RAM
        {
            .base = RAM1_ADDR,
            .size = RAM1_SIZE
        }
        // Reserved memory
    },

    .console = {
        .base = UART2_ADDR /**< serial1: (main.dtsi) */
    },

    .arch = {
        .clusters =  {
            .num = 1,
            .core_num = (size_t[]) {CPU_NUM}
        },

// @imx8mn.dtsi        
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
        .gic = {
            .gicd_addr = GICD_ADDR,
            .gicr_addr = GICR_ADDR,
            .gicc_addr = 0x6f000000, /**< Dont care (v3) */
            .gich_addr = 0x6f010000, /**< Dont care (v3) */
            .gicv_addr = 0x6f020000, /**< Dont care (v3) */
            .maintenance_id = GIC_INTERRUPT
        },
    }
};
