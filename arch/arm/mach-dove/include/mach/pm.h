/*
 * arch/arm/mach-dove/include/mach/pm.h
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __MACH_PM_H
#define __MACH_PM_H

#include <asm/errno.h>
#include <mach/irqs.h>

#define CLOCK_GATING_CONTROL	(DOVE_PMU_VIRT_BASE + 0x38)
#define  CLOCK_GATING_USB0_MASK		(1 << 0)
#define  CLOCK_GATING_USB1_MASK		(1 << 1)
#define  CLOCK_GATING_GBE_MASK		(1 << 2)
#define  CLOCK_GATING_SATA_MASK		(1 << 3)
#define  CLOCK_GATING_PCIE0_MASK	(1 << 4)
#define  CLOCK_GATING_PCIE1_MASK	(1 << 5)
#define  CLOCK_GATING_SDIO0_MASK	(1 << 8)
#define  CLOCK_GATING_SDIO1_MASK	(1 << 9)
#define  CLOCK_GATING_NAND_MASK		(1 << 10)
#define  CLOCK_GATING_CAMERA_MASK	(1 << 11)
#define  CLOCK_GATING_I2S0_MASK		(1 << 12)
#define  CLOCK_GATING_I2S1_MASK		(1 << 13)
#define  CLOCK_GATING_CRYPTO_MASK	(1 << 15)
#define  CLOCK_GATING_AC97_MASK		(1 << 21)
#define  CLOCK_GATING_PDMA_MASK		(1 << 22)
#define  CLOCK_GATING_XOR0_MASK		(1 << 23)
#define  CLOCK_GATING_XOR1_MASK		(1 << 24)
#define  CLOCK_GATING_GIGA_PHY_MASK	(1 << 30)

#define PMU_INTERRUPT_CAUSE	(DOVE_PMU_VIRT_BASE + 0x50)
#define PMU_INTERRUPT_MASK	(DOVE_PMU_VIRT_BASE + 0x54)

#define IO_PWR_CTRL		(DOVE_PMU_VIRT_BASE + 0x58)
#define IO_PWR_CTRL_PCIE_PHY0		(1 << 16)
#define IO_PWR_CTRL_PCIE_PHY1		(1 << 17)

static inline int pmu_to_irq(int pin)
{
	if (pin < NR_PMU_IRQS)
		return pin + IRQ_DOVE_PMU_START;

	return -EINVAL;
}

static inline int irq_to_pmu(int irq)
{
	if (IRQ_DOVE_PMU_START < irq && irq < NR_IRQS)
		return irq - IRQ_DOVE_PMU_START;

	return -EINVAL;
}

/* request the pm core to save & restore a list of registes on power management
 * transitions.
 * The registers list is not copied, instead, the pm will use the pointer,
 * so the callee must not free it.
 */
int pm_registers_add(u32 *registers, int count);

/*
 * request the pm core to save & restore single register
 */
int pm_registers_add_single(u32 register_address);

void dove_pm_register (void);

void dove_pm_cpuidle_deepidle (void);

#endif
