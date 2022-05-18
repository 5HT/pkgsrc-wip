$NetBSD$

--- src/java.base/unix/native/libnio/ch/Net.c.orig	2022-02-05 03:44:09.000000000 +0000
+++ src/java.base/unix/native/libnio/ch/Net.c
@@ -66,7 +66,7 @@
   #endif
 #endif
 
-#if defined(__OpenBSD__)
+#if defined(__OpenBSD__) || defined(__NetBSD__)
   #ifndef IP_ADD_SOURCE_MEMBERSHIP
     #define IP_ADD_SOURCE_MEMBERSHIP        70   /* join a source-specific group */
     #define IP_DROP_SOURCE_MEMBERSHIP       71   /* drop a single source */
