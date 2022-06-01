$NetBSD$

Assume non-Windows is unixy.

--- src/codegen_backend_arm.c.orig	2020-12-01 20:40:51.000000000 +0000
+++ src/codegen_backend_arm.c
@@ -11,12 +11,11 @@
 #include "x86.h"
 #include "x87.h"
 
-#if defined(__linux__) || defined(__APPLE__)
-#include <sys/mman.h>
-#include <unistd.h>
-#endif
 #if defined WIN32 || defined _WIN32 || defined _WIN32
 #include <windows.h>
+#else
+#include <sys/mman.h>
+#include <unistd.h>
 #endif
 
 void *codegen_mem_load_byte;
