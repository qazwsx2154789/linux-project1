#include <unistd.h>

#define SYS_GET_PHY 449   // 自訂的 system call 編號

// Python 會透過 ctypes 呼叫這個函式
unsigned long my_get_physical_addresses(void *virtual_addr) {
    return (unsigned long)syscall(SYS_GET_PHY, virtual_addr);
}
