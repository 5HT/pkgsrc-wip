$NetBSD$

--- include/sound/uapi/asoc.h.orig	2020-06-29 10:51:08.000000000 +0000
+++ include/sound/uapi/asoc.h
@@ -16,7 +16,9 @@
 #ifndef __LINUX_UAPI_SND_ASOC_H
 #define __LINUX_UAPI_SND_ASOC_H
 
+#if defined(__linux__)
 #include <linux/types.h>
+#endif
 
 /*
  * Maximum number of channels topology kcontrol can represent.
