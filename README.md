# Linux Project 1 – Virtual to Physical Address Translation

## Team Members
| Name | Student ID |
|:-----|:-----------|
| 呂紀緯 | 114522134 |
| 李宗仁 | 114522018 |
| 鄧暋翰 | 113522153 |
| 黃懷鈺 | 113582003 |

## Overview

This project explores virtual-to-physical address translation in the Linux kernel on ARM64 architecture.

- **Problem 1**: Implement a custom Linux kernel system call `my_get_physical_addresses()` that walks the five-level page table (PGD → P4D → PUD → PMD → PTE) to translate virtual addresses (VA) to physical addresses (PA).
- **Problem 2**: Use Python's `ctypes` module to call the system call via a shared C library, and observe heap growth and lazy allocation behavior.

## Environment
| Item | Description |
|:-----|:------------|
| Platform | Ubuntu 22.04.5 (ARM64) on UTM |
| Kernel | Linux 5.15.137 (custom-built) |
| Syscall Number | 449 |
| GCC | 11.4.0 |
| Python | 3.10+ |

## Problem 1 – Kernel System Call

### Files
- `problem1/my_get_physical_addresses.c` – Kernel syscall implementation
- `problem1/test_getpa.c` – User-space test program

### Build & Run
Add `my_get_physical_addresses.c` to the kernel source, register syscall 449, then rebuild the kernel:
```bash
make -j$(nproc)
make modules_install install
reboot
```

Compile and run the test:
```bash
gcc test_getpa.c -o test_getpa
sudo ./test_getpa
```

## Problem 2 – Python ctypes

### Files
- `problem2/my_get_phy.c` – C wrapper for the syscall (compiled to shared library)
- `problem2/test_heap.py` – Python test program

### Build & Run
```bash
gcc -Wall -O2 -fPIC -shared -o lib_my_get_phy.so my_get_phy.c
sudo python3 test_heap.py
```
