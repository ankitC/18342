/* extern_helper.h : Helper file for book-keeping global functions.
 *
 * Authors: Group Member 1: Arjun Ankleshwaria <aanklesh>
 *          Group Member 2: Jiten Mehta <jitenm>
 *		    Group Member 3: Ankit Chheda <achheda>
 * Date:    Nov 24, 2013 9:00 AM
 */
#define _EXTERN_H_
#ifdef _EXTERN_H_

extern void init(uint32_t*);
extern void SWI_dispatcher();
extern void IRQ_dispatcher();
extern void	init_kern_timer();
extern void prepare_irq_stack();
extern void irq_wrapper();
extern int hijack(uint32_t, uint32_t, uint32_t*, uint32_t*, uint32_t*);

#endif
