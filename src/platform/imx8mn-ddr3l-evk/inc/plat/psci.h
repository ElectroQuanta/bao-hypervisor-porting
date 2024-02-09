/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */


#ifndef __PLAT_PSCI_H__
#define __PLAT_PSCI_H__

// src: imx-atf/include/arch/aarch64/arch.h
//#define MPIDR_AFFLVL0		ULL(0x0)
//#define MPIDR_AFFLVL1		ULL(0x1)
//#define MPIDR_AFFLVL2		ULL(0x2)
// src: imx-atf/include/arch/aarch64/arch.h
//#define IMX_PWR_LVL0			MPIDR_AFFLVL0
//#define IMX_PWR_LVL1			MPIDR_AFFLVL1
//#define IMX_PWR_LVL2			MPIDR_AFFLVL2
#define PSCI_POWER_STATE_LVL_0 		0x0
#define PSCI_POWER_STATE_LVL_1 		0x1
#define PSCI_POWER_STATE_LVL_2 		0x2

//linux/psci.h:#define PSCI_POWER_STATE_TYPE_STANDBY      0
//linux/psci.h:#define PSCI_POWER_STATE_TYPE_POWER_DOWN   1
#define PSCI_STATE_TYPE_STANDBY		0x00000
#define PSCI_STATE_TYPE_BIT			(1UL << 16)
#define PSCI_STATE_TYPE_POWERDOWN		PSCI_STATE_TYPE_BIT

#endif // __PLAT_PSCI_H__
