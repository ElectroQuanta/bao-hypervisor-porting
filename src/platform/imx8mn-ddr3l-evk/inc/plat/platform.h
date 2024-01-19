/**
 * SPDX-License-Identifier: Apache-2.0 
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__


// #define UART8250_REG_WIDTH (4)
// #define UART8250_PAGE_OFFSET (0x40)

// GIC_PPI: 16-31
// GIC_SPI: 32-991
#define ADD_NRS(a, b) ((a) + (b))
#define GIC_PPI_VAL(x) ADD_NRS(x, 16)
#define GIC_SPI_VAL(x) ADD_NRS(x, 32)


//#include <drivers/imx_uart.h>
#include <drivers/nxp_uart.h>

#endif
