$NetBSD$

--- components/crypto/src/lib.rs.orig	2020-06-30 18:11:35.000000000 +0000
+++ components/crypto/src/lib.rs
@@ -1,5 +1,5 @@
 #![deny(trivial_numeric_casts, warnings)]
-#![allow(intra_doc_link_resolution_failure)]
+#![allow(broken_intra_doc_links)]
 #![allow(
     clippy::too_many_arguments,
     clippy::implicit_hasher,
