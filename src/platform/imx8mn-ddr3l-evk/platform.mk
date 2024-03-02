## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a53

GIC_VERSION:=GICV3
#BBAI64_MEM_GB:=4

#drivers = imx_uart
drivers = pl011_uart
#drivers = nxp_uart

platform_description:=imx8mn_ddr3l_evk_desc.c

platform-cppflags =
#platform-cppflags = -DBBAI64_MEM_GB=$(BBAI64_MEM_GB)
platform-cflags = -mcpu=$(CPU)
platform-asflags =
platform-ldflags =
