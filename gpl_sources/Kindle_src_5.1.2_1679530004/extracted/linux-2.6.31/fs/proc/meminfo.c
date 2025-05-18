#include <linux/fs.h>
#include <linux/hugetlb.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/proc_fs.h>
#include <linux/quicklist.h>
#include <linux/seq_file.h>
#include <linux/swap.h>
#include <linux/vmstat.h>
#include <asm/atomic.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/setup.h>
#include "internal.h"

void __attribute__((weak)) arch_report_meminfo(struct seq_file *m)
{
}

extern struct meminfo *get_meminfo(void);
extern unsigned int dma_reserved_count;

unsigned int rss_sum_by_tasks()
{
	unsigned int rss_sum = 0;
	struct task_struct *g, *p;
	do_each_thread(g, p) {
		struct mm_struct *mm;

		if (!thread_group_leader(p))
			continue;

		task_lock(p);
		mm = p->mm;
		if (!mm) {
			/*
			 * total_vm and rss sizes do not exist for tasks with no
			 * mm so there's no need to report them; they can't be
			 * oom killed anyway.
			 */
			task_unlock(p);
			continue;
		}
		rss_sum += get_mm_rss(mm);
		task_unlock(p);
	} while_each_thread(g, p);

	return rss_sum;
}

static int meminfo_proc_show(struct seq_file *m, void *v)
{
	struct sysinfo i;
	unsigned long committed;
	unsigned long allowed;
	struct vmalloc_info vmi;
	long cached;
	unsigned long pages[NR_LRU_LISTS];
	int lru;
	
	int free = 0, total = 0, reserved = 0, sharedp = 0, sharedp_mapped = 0;
	int shared = 0, pcached = 0, slab = 0, shared_mapped = 0, user_pages = 0;
	int user_cache = 0, kernel_cache = 0;
	{
		int node, i;
		struct meminfo * mi = get_meminfo();
	for_each_online_node(node) {
		pg_data_t *n = NODE_DATA(node);
		struct page *map = pgdat_page_nr(n, 0) - n->node_start_pfn;

		for_each_nodebank (i,mi,node) {
			struct membank *bank = &mi->bank[i];
			unsigned int pfn1, pfn2;
			struct page *page, *end;

			pfn1 = bank_pfn_start(bank);
			pfn2 = bank_pfn_end(bank);

			page = map + pfn1;
			end  = map + pfn2;

			do {
				total++;
				if (PageReserved(page))
					reserved++;
				else if (PageSwapCache(page))
					pcached++;
				else if (PageSlab(page))
					slab++;
				else if (!page_count(page))
					free++;
				else {
					shared += page_count(page) - 1;
					if (page_count(page) > 1)
						sharedp++;
					if (page_mapped(page)) {
	                                        if (page_mapcount(page) > 1)
        	                                        sharedp_mapped++;
                                        	shared_mapped += page_mapcount(page) - 1;
						user_pages++;
						if (page_mapping(page))
							user_cache++;
                                	} else if (page_mapping(page))
							kernel_cache++;
				}
				page++;
			} while (page < end);
		}
	}


	}
/*
 * display in kilobytes.
 */
#define K(x) ((x) << (PAGE_SHIFT - 10))
	si_meminfo(&i);
	si_swapinfo(&i);
	committed = percpu_counter_read_positive(&vm_committed_as);
	allowed = ((totalram_pages - hugetlb_total_pages())
		* sysctl_overcommit_ratio / 100) + total_swap_pages;

	cached = global_page_state(NR_FILE_PAGES) -
			total_swapcache_pages - i.bufferram;
	if (cached < 0)
		cached = 0;

	get_vmalloc_info(&vmi);

	for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
		pages[lru] = global_page_state(NR_LRU_BASE + lru);

	/*
	 * Tagged format, for easy grepping and expansion.
	 */
	seq_printf(m,
		"MemTotal:       %8lu kB\n"
		"MemFree:        %8lu kB\n"
		"Buffers:        %8lu kB\n"
		"Cached:         %8lu kB\n"
		"SwapCached:     %8lu kB\n"
		"Active:         %8lu kB\n"
		"Inactive:       %8lu kB\n"
		"Active(anon):   %8lu kB\n"
		"Inactive(anon): %8lu kB\n"
		"Active(file):   %8lu kB\n"
		"Inactive(file): %8lu kB\n"
		"Unevictable:    %8lu kB\n"
		"Mlocked:        %8lu kB\n"
#ifdef CONFIG_HIGHMEM
		"HighTotal:      %8lu kB\n"
		"HighFree:       %8lu kB\n"
		"LowTotal:       %8lu kB\n"
		"LowFree:        %8lu kB\n"
#endif
#ifndef CONFIG_MMU
		"MmapCopy:       %8lu kB\n"
#endif
		"SwapTotal:      %8lu kB\n"
		"SwapFree:       %8lu kB\n"
		"Dirty:          %8lu kB\n"
		"Writeback:      %8lu kB\n"
		"AnonPages:      %8lu kB\n"
		"Mapped:         %8lu kB\n"
		"Slab:           %8lu kB\n"
		"SReclaimable:   %8lu kB\n"
		"SUnreclaim:     %8lu kB\n"
		"PageTables:     %8lu kB\n"
#ifdef CONFIG_QUICKLIST
		"Quicklists:     %8lu kB\n"
#endif
		"NFS_Unstable:   %8lu kB\n"
		"Bounce:         %8lu kB\n"
		"WritebackTmp:   %8lu kB\n"
		"CommitLimit:    %8lu kB\n"
		"Committed_AS:   %8lu kB\n"
		"VmallocTotal:   %8lu kB\n"
		"VmallocUsed:    %8lu kB\n"
		"VmallocChunk:   %8lu kB\n"
		"========\n"
		"%d pages of RAM\n" //, total
		"%d free pages\n" //, free
		"%d reserved pages\n" //, reserved
		"%d slab pages\n" //, slab
		"%d shared page count\n" //, shared
		"%d shared pages\n"
		"%d pages swap cached\n" //, cached
		"%d dma reserved pages\n"
		"%d mapped shared count\n"
		"%d mapped shared pages\n"
		"%d total user pages\n"
		"%d RSS sum by tasks\n"
		"%d RSS sum by page stats\n"
		"%d user cache pages\n"
		"%d kernel cache pages\n",
		K(i.totalram),
		K(i.freeram),
		K(i.bufferram),
		K(cached),
		K(total_swapcache_pages),
		K(pages[LRU_ACTIVE_ANON]   + pages[LRU_ACTIVE_FILE]),
		K(pages[LRU_INACTIVE_ANON] + pages[LRU_INACTIVE_FILE]),
		K(pages[LRU_ACTIVE_ANON]),
		K(pages[LRU_INACTIVE_ANON]),
		K(pages[LRU_ACTIVE_FILE]),
		K(pages[LRU_INACTIVE_FILE]),
		K(pages[LRU_UNEVICTABLE]),
		K(global_page_state(NR_MLOCK)),
#ifdef CONFIG_HIGHMEM
		K(i.totalhigh),
		K(i.freehigh),
		K(i.totalram-i.totalhigh),
		K(i.freeram-i.freehigh),
#endif
#ifndef CONFIG_MMU
		K((unsigned long) atomic_long_read(&mmap_pages_allocated)),
#endif
		K(i.totalswap),
		K(i.freeswap),
		K(global_page_state(NR_FILE_DIRTY)),
		K(global_page_state(NR_WRITEBACK)),
		K(global_page_state(NR_ANON_PAGES)),
		K(global_page_state(NR_FILE_MAPPED)),
		K(global_page_state(NR_SLAB_RECLAIMABLE) +
				global_page_state(NR_SLAB_UNRECLAIMABLE)),
		K(global_page_state(NR_SLAB_RECLAIMABLE)),
		K(global_page_state(NR_SLAB_UNRECLAIMABLE)),
		K(global_page_state(NR_PAGETABLE)),
#ifdef CONFIG_QUICKLIST
		K(quicklist_total_size()),
#endif
		K(global_page_state(NR_UNSTABLE_NFS)),
		K(global_page_state(NR_BOUNCE)),
		K(global_page_state(NR_WRITEBACK_TEMP)),
		K(allowed),
		K(committed),
		(unsigned long)VMALLOC_TOTAL >> 10,
		vmi.used >> 10,
		vmi.largest_chunk >> 10,
		total,
		free,
		reserved,
		slab,
		shared,
		sharedp,
		pcached,
		dma_reserved_count,
		shared_mapped,
		sharedp_mapped,
		user_pages,
		rss_sum_by_tasks(),
		user_pages + shared_mapped,
		user_cache,
		kernel_cache
		);

	hugetlb_report_meminfo(m);

	arch_report_meminfo(m);

	return 0;
#undef K
}

static int meminfo_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, meminfo_proc_show, NULL);
}

static const struct file_operations meminfo_proc_fops = {
	.open		= meminfo_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_meminfo_init(void)
{
	proc_create("meminfo", 0, NULL, &meminfo_proc_fops);
	return 0;
}
module_init(proc_meminfo_init);
