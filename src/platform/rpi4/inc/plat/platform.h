/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#define UART8250_REG_WIDTH   (4)
#define UART8250_PAGE_OFFSET (0x40)

#define UART_CLK 48000000
#define PL011_PAGE_OFFSET (0xa00)  /**< UART5 offset for page alignment */

#include <drivers/pl011_uart.h>

#endif
