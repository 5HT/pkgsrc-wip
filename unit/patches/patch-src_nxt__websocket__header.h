$NetBSD$

Include endian.h for endianness test to work.

--- src/nxt_websocket_header.h.orig	2020-10-08 16:04:40.000000000 +0000
+++ src/nxt_websocket_header.h
@@ -6,6 +6,7 @@
 #ifndef _NXT_WEBSOCKET_HEADER_H_INCLUDED_
 #define _NXT_WEBSOCKET_HEADER_H_INCLUDED_
 
+#include <endian.h>
 #include <netinet/in.h>
 
 
