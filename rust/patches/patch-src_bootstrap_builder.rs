$NetBSD: patch-src_bootstrap_builder.rs,v 1.11 2020/07/06 13:56:32 he Exp $

Do not install 'src'.
Use @PREFIX@, not $ORIGIN in rpath.

--- src/bootstrap/builder.rs.orig	2022-06-27 13:37:07.000000000 +0000
+++ src/bootstrap/builder.rs
@@ -742,7 +742,6 @@ impl<'a> Builder<'a> {
                 install::Clippy,
                 install::Miri,
                 install::Analysis,
-                install::Src,
                 install::Rustc
             ),
             Kind::Run => describe!(
@@ -1706,7 +1705,7 @@ impl<'a> Builder<'a> {
                 Some("-Wl,-rpath,@loader_path/../lib")
             } else if !target.contains("windows") {
                 rustflags.arg("-Clink-args=-Wl,-z,origin");
-                Some("-Wl,-rpath,$ORIGIN/../lib")
+                Some("-Wl,-rpath,@PREFIX@/lib")
             } else {
                 None
             };
