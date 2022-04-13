#ifndef PAGING_H_l5ffSHJMUua09zTAMQKdiU0oTLUXOOr9
#define PAGING_H_l5ffSHJMUua09zTAMQKdiU0oTLUXOOr9

void
init_paging(void);

void
map_page(const void *virt_ptr, const void *phys_ptr);

void
identity_map_pages(void);

void
load_page_map(void);

#endif
