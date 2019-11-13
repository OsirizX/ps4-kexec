#ifndef ACPI_IO_H
#define ACPI_IO_H

#include "types.h"
#include "x86.h"
#include "kernel.h"
#include "acpi.h"

extern struct ksym_t kern;

static inline void outb(u32 port, u8 data)
{
    asm volatile("out %w1, %0" : : "a" (data), "d" (port));
}
static inline u8 inb(u32 port)
{
	u8 data;
	asm volatile("in %0, %w1" : "=a" (data) : "d" (port));
	return data;
}

static inline void outw(u32 port, u16 data)
{
    asm volatile("out %w1, %0" : : "a" (data), "d" (port));
}
static inline u16 inw(u32 port)
{
	u16 data;
	asm volatile("in %0, %w1" : "=a" (data) : "d" (port));
	return data;
}

static inline u16 inl(u32 port)
{
	u32 data;
	kern.printf("\ninl(0x%x)", port);
	asm volatile("in %0, %w1" : "=a" (data) : "d" (port));
	return data;
}

static void bad_io_access(unsigned long port, const char *access)
{
	static int count = 10000000;
	if (count) {
		count--;
		kern.printf("Bad IO access at port %#lx (%s)\n", port, access);
	}
}
 /*
 * Ugly macros are a way of life.
 */
#define PIO_OFFSET	0x10000UL
#define PIO_MASK	0x0ffffUL
#define PIO_RESERVED	0x40000UL
#define IO_COND(addr, is_pio, is_mmio) do {			\
	unsigned long port = (unsigned long)addr;	\
	if (port >= PIO_RESERVED) {				\
		is_mmio;					\
	} else if (port > PIO_OFFSET) {				\
		port &= PIO_MASK;				\
		is_pio;						\
	} else							\
		bad_io_access(port, #is_pio );			\
} while (0)

//#define __iomem        __attribute__((noderef, address_space(2)))
#define __iomem
#define __force
#define __u32 u32
#define __u64 u64
static inline void __raw_writel(u32 value, volatile void __iomem *addr)
{
	//void __iomem *addr64 = (void __iomem *)PA_TO_DM(addr);
	*(volatile u32 *)addr = value;
	kern.printf("\n__raw_writel(0x%x, 0x%llx)", value, addr);
}

static inline void __raw_writeq(u64 value, volatile void __iomem *addr)
{
	//void __iomem *addr64 = (void __iomem *)PA_TO_DM(addr);
	*(volatile u64 *)addr = value;
}

static inline u32 __raw_readl(const volatile void __iomem *addr)
{
	//void __iomem *addr64 = (void __iomem *)PA_TO_DM(addr);
	kern.printf("\n__raw_readl(0x%llx)", addr);
	return *(const volatile u32 __force *)addr;
}

static inline u64 __raw_readq(const volatile void __iomem *addr)
{
	//void __iomem *addr64 = (void __iomem*)PA_TO_DM(addr);
	return *(const volatile u64 __force *)addr;
} 

//#define __bitwise__ __attribute__((bitwise))
#define __bitwise__
#define __bitwise __bitwise__
typedef u32 __bitwise __le32;
#define __cpu_to_le32(x) ((__le32)(u32)(x))
#define __le32_to_cpu(x) ((__force __u32)(__le32)(x)) 
static inline void writel(u32 value, volatile void __iomem *addr)
{
	__raw_writel(__cpu_to_le32(value), addr);
}

static inline u32 readl(const volatile void __iomem *addr)
{
	return __le32_to_cpu(__raw_readl(addr));
} 

static inline void writew(u16 value, volatile void __iomem *addr)
{
	*(volatile u16 *)addr = value;
}

static inline u32 readw(const volatile void __iomem *addr)
{
	return *(const volatile u16 __force *)addr;
}

typedef u64 __bitwise __le64;
#define __cpu_to_le64(x) ((__le64)(u64)(x))
static inline void writeq(u64 value, volatile void __iomem *addr)
{
	__raw_writeq(__cpu_to_le64(value), addr);
}

#define __le64_to_cpu(x) ((__force __u64)(__le64)(x)) 
static inline u64 readq(const volatile void __iomem *addr)
{
	return __le64_to_cpu(__raw_readq(addr));
} 

#define PCI_IOBASE ((void __iomem *)0)
static inline void outlmem(u32 value, unsigned long addr)
{
	writel(value, PCI_IOBASE + addr);
}

static inline void iowrite16(u16 val, void __iomem *addr)
{
	IO_COND(addr, outw(((u32*)addr)[0], val)/*outwmem(val,addr)*/, writew(val, addr));
}

static inline void iowrite32(u32 val, void __iomem *addr)
{
	IO_COND(addr, outl(((u32*)addr)[0], val)/*outlmem(val,addr)*/, writel(val, addr));
}

static inline void iowrite64(u64 value, volatile void __iomem *addr)
{
	writeq(value, addr);
}

static inline unsigned int ioread32(void __iomem *addr)
{
	IO_COND(addr, return inl(((u32*)addr)[0]), return readl(addr));
	return 0xffffffff;
}

static inline u16 ioread16(void __iomem *addr)
{
	IO_COND(addr, return inw(((u32*)addr)[0]), return readw(addr));
	return 0xffff;
}

#define IORESOURCE_MEM		0x00000200
typedef u64 phys_addr_t;
typedef phys_addr_t resource_size_t;
struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	unsigned long flags;
	struct resource *parent, *sibling, *child;
};

//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-variable"
static struct resource iomem_resource = {
	.name	= "PCI mem",
	.start	= 0,
	.end	= -1,
	.flags	= IORESOURCE_MEM,
};
//#pragma GCC diagnostic pop

typedef unsigned __bitwise__ gfp_t;
#define ___GFP_DIRECT_RECLAIM	0x400000u
#define ___GFP_KSWAPD_RECLAIM	0x2000000u
#define ___GFP_IO		0x40u
#define ___GFP_FS		0x80u
#define __GFP_IO	((__force gfp_t)___GFP_IO)
#define __GFP_FS	((__force gfp_t)___GFP_FS)

#define __GFP_RECLAIM ((__force gfp_t)(___GFP_DIRECT_RECLAIM|___GFP_KSWAPD_RECLAIM))
#define GFP_KERNEL	(__GFP_RECLAIM | __GFP_IO | __GFP_FS)


static inline struct resource *alloc_resource(gfp_t flags)
{
	struct resource *res = NULL;
	//res = kzalloc(sizeof(struct resource), flags);
	res = kernel_alloc_contig(sizeof(struct resource));
	return res;
}

#define request_mem_region(start,n,name) __request_region(&iomem_resource, (start), (n), (name), 0)
#define release_mem_region(start,n)	__release_region(&iomem_resource, (start), (n))

static inline struct resource * __request_region(struct resource *parent,
				   resource_size_t start, resource_size_t n,
				   const char *name, int flags)
{
	if (parent == NULL) parent = &iomem_resource;

	struct resource *res = alloc_resource(GFP_KERNEL);

	if (!res)
		return NULL;

	res->name = name;
	res->start = start;
	res->end = start + n - 1;
	//TODO: Check no other resource requested (start, n) region. 
	return res;
}

static inline void __release_region(struct resource *parent, resource_size_t start,
			resource_size_t n)
{
	//TODO: find and free resource memory allocated by __request_region
}

#endif