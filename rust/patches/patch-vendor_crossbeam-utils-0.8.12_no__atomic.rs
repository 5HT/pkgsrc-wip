$NetBSD$

Add mipsel-unknown-netbsd target as not having 64-bit atomics.

--- vendor/crossbeam-utils-0.8.12/no_atomic.rs.orig	2023-01-25 01:49:15.000000000 +0000
+++ vendor/crossbeam-utils-0.8.12/no_atomic.rs
@@ -40,6 +40,7 @@ const NO_ATOMIC_64: &[&str] = &[
     "mipsel-unknown-linux-gnu",
     "mipsel-unknown-linux-musl",
     "mipsel-unknown-linux-uclibc",
+    "mipsel-unknown-netbsd",
     "mipsel-unknown-none",
     "mipsisa32r6-unknown-linux-gnu",
     "mipsisa32r6el-unknown-linux-gnu",
