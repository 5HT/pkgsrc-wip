$NetBSD$

Shell portability.

--- storage/rocksdb/rocksdb/build_tools/fb_compile_mongo.sh.orig	2021-02-18 23:22:28.000000000 +0000
+++ storage/rocksdb/rocksdb/build_tools/fb_compile_mongo.sh
@@ -13,7 +13,7 @@ EXTRA_LDFLAGS=""
 if test -z $ALLOC; then
   # default
   ALLOC=tcmalloc
-elif [[ $ALLOC == "jemalloc" ]]; then
+elif [ $ALLOC = "jemalloc" ]; then
   ALLOC=system
   EXTRA_LDFLAGS+=" -Wl,--whole-archive $JEMALLOC_LIB -Wl,--no-whole-archive"
 fi
