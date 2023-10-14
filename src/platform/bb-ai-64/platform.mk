## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a72

GIC_VERSION:=GICV3
BBAI64_MEM_GB:=4

drivers = 8250_uart

platform_description:=bb_ai64_desc.c

#platform-cppflags =
platform-cppflags = -DBBAI64_MEM_GB=$(BBAI64_MEM_GB)
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =
