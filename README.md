# OP-TEE Portable IPC
## Contents
1. [Introduction](#1-introduction)
2. [Capabilities](#2-capabilities)
3. [Portability](#3-portability)


## 1. Introduction
`optee_ipc` is a portable client library that implements simplified IPC
with OP-TEE OS core in bootloader environments. Possible use cases:
- Verified boot, storing rollback indexes etc.
- Secure storage of a secret cryptographic keys/HMAC generation

---

## 2. Capabilties
It should be noticed in the beginning that `optee_ipc` isn't GlobaPlatform
compliant and doesn't follow any of TEE Client API specifications (and it's
not intented to).

Currently it supports:
- Open/close TEE session
- Perform both std/fast calls
- register_user_memory API
- ...

---

## 3. Portability
The suggested approach to porting `optee_ipc` is to copy of C sources and
headers into the bootloader source tree and integrate into its build system
respectively, so `optee_ipc` sources will be built mutually with the bootloader.

Alter `optee_sysdeps.c` to add support of bootloader dynamic memory allocators,
output printing and other runtime functions. In most cases (like porting to
U-boot) lib should work out-of-the-box with any alterations.

To enable debug output and run-time checks, library should be build with
`OPTEE_DEBUG` preprocessor symbol set.
