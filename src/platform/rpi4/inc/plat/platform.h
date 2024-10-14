/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved
 */

#ifndef __PLAT_PLATFORM_H__
#define __PLAT_PLATFORM_H__

#define UART8250_REG_WIDTH   (4)
#define UART8250_PAGE_OFFSET (0x40)

#define UART_CLK 48000000
#define PL011_PAGE_OFFSET (0xa00) /**< UART5 offset for page alignment */

//#ifndef UART_CLK_MSG_SENT
//#define UART_CLK_MSG_SENT
//#define MY_STR(x) #x
//#define MY_STR_VAL(x) MY_STR(x)
//#pragma message "File: " __FILE__ ": UART_CLK (Hz): " MY_STR_VAL(UART_CLK)
//#pragma message "File: " __FILE__ ": PL011_PAGE_OFFSET (Hz): " MY_STR_VAL(PL011_PAGE_OFFSET)
////#pragma message "File: " __FILE__ ": UART_CLK (Hz): "
//#endif
#include <drivers/pl011_uart.h>

#endif
