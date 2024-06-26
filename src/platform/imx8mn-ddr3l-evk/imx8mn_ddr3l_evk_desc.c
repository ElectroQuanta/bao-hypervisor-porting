/**
 * @file imx8mn_ddr3l_evk_desc.c
 * @author Jose Pires
 * @date 2024-01-23
 *
 * @brief i.MX 8M Nano UltraLite (DDR3L) EVK (imx8mn_ddr3l_evk) platform
 * description for the Bao hypervisor
 *
 * References:
 * - Technical Reference Manual for the i.MX 8M Nano
 * (https://www.nxp.com/webapp/Download?colCode=IMX8MNRM)
 * - Device trees: https://github.com/nxp-imx/uboot-imx/tree/lf_v2022.04/arch/arm/dts
 *   - imx8mn-dd3rl-evk.dts
 *   - imx8mn.dtsi
 *   - imx8mn-evk.dtsi
 *
 * @license SPDX-License-Identifier: Apache-2.0
 *
 * @copyright Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

/**< RAM: imx8mn-dd3rl-evk.dts */
//	memory@40000000 {
//		device_type = "memory";
//		reg = <0x00 0x40000000 0x00 0x80000000>;
//	};
/// RAM adddresses
#define RAM1_ADDR_DTB       0x40000000UL
#define RAM1_ADDR_UBOOT     0x40200000UL
#define RAM1_ADDR_CUR       0x50000000UL

/// RAM Sizes
#define RAM1_SIZE_2GB       0x80000000UL /**< U-boot device tree */
#define RAM1_SIZE_1GB       0x40000000UL /**< DDR3L Datasheet (1GB) */
#define RAM1_SIZE_750MB     0x30000000UL /**< DDR3L Datasheet (1GB) */

/// RAM address and size calculation
//#define RAM1_ADDR RAM1_ADDR_DTB
#define RAM1_ADDR RAM1_ADDR_UBOOT
//#define RAM1_ADDR RAM1_ADDR_CUR
//#define RAM1_SIZE_ORIG RAM1_SIZE_2GB
#define RAM1_SIZE_ORIG RAM1_SIZE_1GB

#define RAM1_SIZE ( RAM1_SIZE_ORIG - (RAM1_ADDR - RAM1_ADDR_DTB )) 

#define CPU_NUM 4 /**< Quad-core A53 processor */

/**< uboot-imx/arch/arm/dts/imx8mn-evk.dtsi */
// / {
// 	model = "NXP i.MX8MNano EVK board";
// 	compatible = "fsl,imx8mn-evk", "fsl,imx8mn";
// 
//	chosen {
//		bootargs = "console=ttymxc1,115200 earlycon=ec_imx6q,0x30890000,115200";
//		stdout-path = &uart2;
//	};
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
#define UART2_ADDR 0x30890000UL


/**< GIC: imx8mn.dtsi */
// interrupt-controller@38800000 {
//     compatible = "arm,gic-v3";
//     reg = <0x38800000 0x10000 0x38880000 0xc0000>;
//     #interrupt-cells = <0x03>;
//     interrupt-controller;
//     interrupts = <0x01 0x09 0x04>;
// 0x01 (SPI); 0x00 (PPI)
// 0x09 (INT_ID)
// 0x04 (flags)
#define GICD_ADDR 0x38800000UL
#define GICR_ADDR 0x38880000UL
#define GIC_GIC_PPI 9 /**< Interrupt for the GIC500 controller (in PPI) */
#define GIC_INTERRUPT (GIC_PPI_VAL(GIC_GIC_PPI))


struct platform platform = {
    .cpu_num = CPU_NUM,
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
        .base = UART2_ADDR 
    },

    .arch = {
        //.clusters =  {
        //    .num = 1,
        //    .core_num = (size_t[]) {CPU_NUM}
        //},
        .gic = {
            .gicd_addr = GICD_ADDR,
            .gicr_addr = GICR_ADDR,
            // .gicc_addr = 0x6f000000, /**< Dont care (v3) */
            // .gich_addr = 0x6f010000, /**< Dont care (v3) */
            // .gicv_addr = 0x6f020000, /**< Dont care (v3) */
            .maintenance_id = GIC_INTERRUPT
            //.maintenance_id = ( 0x09UL + 16UL )
        },
    }
};
