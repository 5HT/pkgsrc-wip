$NetBSD$

--- net/dns/address_sorter_posix.cc.orig	2020-07-15 18:56:00.000000000 +0000
+++ net/dns/address_sorter_posix.cc
@@ -13,7 +13,11 @@
 #include <sys/socket.h>  // Must be included before ifaddrs.h.
 #include <ifaddrs.h>
 #include <net/if.h>
+#if defined(OS_FREEBSD)
+#include <net/if_var.h>
+#endif
 #include <netinet/in_var.h>
+#include <netinet6/in6_var.h>
 #include <string.h>
 #include <sys/ioctl.h>
 #endif
