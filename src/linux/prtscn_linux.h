#ifndef PRTSCN_LINUX_H_
#define PRTSCN_LINUX_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <X11/Xutil.h>

/* structure to store PNG image bytes */

void getScreen(const int, const int, int, int, const char*);

#ifdef __cplusplus
}
#endif

#endif
