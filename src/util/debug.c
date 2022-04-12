#include "util/debug.h"

#include "io/text.h"

void
log_info(const char *msg)
{
        put_str("[tcf-kernel] info: ");
        put_str(msg);
        put_char('\n');
}

void
log_warning(const char *msg)
{
        put_str("[tcf-kernel] warning: ");
        put_str(msg);
        put_char('\n');
}
