#ifndef PRTSCN_H_
#define PRTSCN_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <X11/Xutil.h>

/* structure to store PNG image bytes */

void getScreen(const int, const int, const int, const int, const char*);

#ifdef __cplusplus
}
#endif

#endif
