#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/mm.h>
#include <linux/uaccess.h>
#include <asm/pgtable.h>

SYSCALL_DEFINE1(my_get_physical_addresses, void *, vaddr)
{
    struct page *page;
    unsigned long va = (unsigned long)vaddr;
    unsigned long pa;

    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    struct mm_struct *mm = current->mm;

    pgd = pgd_offset(mm, va);
    if (pgd_none(*pgd) || pgd_bad(*pgd))
        return 0;

    p4d = p4d_offset(pgd, va);
    if (p4d_none(*p4d) || p4d_bad(*p4d))
        return 0;

    pud = pud_offset(p4d, va);
    if (pud_none(*pud) || pud_bad(*pud))
        return 0;

    pmd = pmd_offset(pud, va);
    if (pmd_none(*pmd) || pmd_bad(*pmd))
        return 0;

    pte = pte_offset_map(pmd, va);
    if (!pte)
        return 0;
    if (!pte_present(*pte))
        return 0;

    pa = (pte_pfn(*pte) << PAGE_SHIFT) | (va & ~PAGE_MASK);
    return pa;
}
