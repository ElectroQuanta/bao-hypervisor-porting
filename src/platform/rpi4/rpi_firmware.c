#include <bao.h>
#include <platform.h>

#include <cpu.h>
#include <hypercall.h>
#include <spinlock.h>
#include <interrupts.h>
#include <stdbool.h>
#include <vm.h>

#define RPI_MAILBOX_IRQ_ID 65

#define RPI_HYP_ARG_START  1
#define RPI_HYP_ARG_END    2

spinlock_t rpi_firmware_lock = SPINLOCK_INITVAL;


static void rpi_mailbox_irq_handler(irqid_t irq_id) {
  /* INFO("func %s, irq_id: %d", __func__, (int)irq_id); */
  vcpu_inject_irq(cpu()->vcpu, irq_id);
  interrupts_cpu_enable(irq_id, false);
}

void plat_rpi_init(void) {
  /* INFO("func %s", __func__); */
  interrupts_reserve(RPI_MAILBOX_IRQ_ID, rpi_mailbox_irq_handler);
}

long rpi_mailbox_hypercall(unsigned long arg0, unsigned long arg1, unsigned long arg2)
{
  switch (arg0) {
  case RPI_HYP_ARG_START:
	/* INFO("func %s, arg0 = %lu", __func__, arg0); */
	spin_lock(&rpi_firmware_lock);
	interrupts_cpu_enable(RPI_MAILBOX_IRQ_ID, true);
	break;

  case RPI_HYP_ARG_END:
	/* INFO("func %s, arg0 = %lu", __func__, arg0); */
	interrupts_cpu_enable(RPI_MAILBOX_IRQ_ID, false);
	spin_unlock(&rpi_firmware_lock);
	break;

  default:
    ERROR("func %s, unknown arg0 = %lu", __func__, arg0);
  }

  return 0;
}
