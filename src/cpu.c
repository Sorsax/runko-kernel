#include "cpu.h"


#ifdef _MSC_VER
unsigned int cpu_get_vendor(char *buf) {
    for (int i = 0; i < 12; i++) buf[i] = 'X';
    buf[12] = 0;
    return 0;
}
#else
unsigned int cpu_get_vendor(char *buf) {
    unsigned int ebx, edx, ecx;
    __asm__ __volatile__ (
        "cpuid"
        : "=b" (ebx), "=d" (edx), "=c" (ecx)
        : "a" (0)
    );
    ((unsigned int*)buf)[0] = ebx;
    ((unsigned int*)buf)[1] = edx;
    ((unsigned int*)buf)[2] = ecx;
    buf[12] = 0;
    return 0;
}
#endif

#ifdef _MSC_VER
unsigned int cpu_get_features(char *buf) {
    *((unsigned int*)buf) = 0;
    return 0;
}
#else
unsigned int cpu_get_features(char *buf) {
    unsigned int edx;
    __asm__ __volatile__ (
        "cpuid"
        : "=d" (edx)
        : "a" (1)
    );
    *((unsigned int*)buf) = edx;
    return edx;
}
#endif
