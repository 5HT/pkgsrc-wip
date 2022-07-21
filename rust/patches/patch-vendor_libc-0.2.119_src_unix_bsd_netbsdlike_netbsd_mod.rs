$NetBSD$

Copy execinfo function definitions from openbsd's mod.rs.

--- vendor/libc-0.2.119/src/unix/bsd/netbsdlike/netbsd/mod.rs.orig	2022-05-18 03:01:05.000000000 +0000
+++ vendor/libc-0.2.119/src/unix/bsd/netbsdlike/netbsd/mod.rs
@@ -2788,6 +2788,23 @@ extern "C" {
     pub fn kinfo_getvmmap(pid: ::pid_t, cntp: *mut ::size_t) -> *mut kinfo_vmentry;
 }
 
+#[link(name = "execinfo")]
+extern "C" {
+    pub fn backtrace(addrlist: *mut *mut ::c_void, len: ::size_t) -> ::size_t;
+    pub fn backtrace_symbols(addrlist: *const *mut ::c_void, len: ::size_t) -> *mut *mut ::c_char;
+    pub fn backtrace_symbols_fd(
+        addrlist: *const *mut ::c_void,
+        len: ::size_t,
+        fd: ::c_int,
+    ) -> ::c_int;
+    pub fn backtrace_symbols_fmt(
+        addrlist: *const *mut ::c_void,
+        len: ::size_t,
+        fmt: *const ::c_char,
+    ) -> *mut *mut ::c_char;
+}
+
+
 cfg_if! {
     if #[cfg(target_arch = "aarch64")] {
         mod aarch64;