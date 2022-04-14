#ifndef PAGING_H_l5ffSHJMUua09zTAMQKdiU0oTLUXOOr9
#define PAGING_H_l5ffSHJMUua09zTAMQKdiU0oTLUXOOr9

void
init_paging(void);

void
map_page(const void *virt_addr, const void *phys_addr);

void
identity_map_pages(const void *first_page, const void *last_page);

void
load_page_map(void);

#endif
