$NetBSD$

Build this file unconditionally.

--- src/linux_cmn.c.orig	2019-01-17 09:25:18.000000000 +0000
+++ src/linux_cmn.c
@@ -28,7 +28,6 @@
 /*                                                                                      */
 /*******************************************|********************************************/
 
-#if defined (unix) || (__unix)
 /*------------------------------------  Includes   -------------------------------------*/
 /*******************************************|********************************************/
 #include "epson-escpr-def.h"
@@ -302,7 +301,6 @@ void TermMutex(void)
 }
 
 
-#endif
 
 /*__________________________________   linux-cmn.c   ___________________________________*/
   
