$NetBSD$

Use local ncurses rather than ee's own implementation.

--- create.make.orig	2002-09-23 04:18:30.000000000 +0000
+++ create.make
@@ -154,35 +154,8 @@ else
 	catgets="-DNO_CATGETS"
 fi
 
-# make decisions about use of new_curse.c (use of new_curse is recommended 
-# rather than local curses)
-
-if [ -n "$terminfo_exists" -a -z "$termcap_exists" ]
-then
-	echo "Neither terminfo or termcap are on this system!  "
-	if [ -f /usr/include/curses.h ]
-	then
-		echo "Relying on local curses implementation."
-	else
-		cat <<-EOF
-		Don't know where to find curses, you'll need to modify 
-		source code to be able to build!
-		
-		Modify the file make.default and build ee by typing:
-		
-		make -f make.default
-		
-		EOF
-
-		exit 1
-	fi
-	
-	TARGET="curses"
-	curses=""
-else
-	curses="-DNCURSE"
-	TARGET="ee"
-fi
+curses="-DNCURSE"
+TARGET="curses"
 
 if [ -z "$termio" -a -z "$sgtty" ]
 then
@@ -205,7 +178,7 @@ then
 	fi
 	
 	TARGET="curses"
-	curses=""
+	curses="-DNCURSE"
 fi
 
 # check if this is a SunOS system
@@ -261,13 +234,15 @@ echo "DEFINES =	$termio $terminfo_exists
 echo "" >> make.local
 echo "CFLAGS =	$HAS_UNISTD $HAS_STDARG $HAS_STDLIB $HAS_CTYPE $HAS_SYS_IOCTL $HAS_SYS_WAIT $five_lib $five_include $select_hdr $other_cflags $termcap_exists" >> make.local
 echo "" >> make.local
+echo "LDFLAGS =	$LDFLAGS" >> make.local
+echo "" >> make.local
 echo "" >> make.local
 echo "all :	$TARGET" >> make.local
 
 cat  >> make.local << EOF
 
 curses :	ee.c
-	cc ee.c -o ee \$(CFLAGS) -lcurses 
+	cc ee.c -o ee \$(CFLAGS) \$(CFLAGS) \$(LDFLAGS) -lncurses
 
 ee :	ee.o new_curse.o
 	cc -o ee ee.o new_curse.o \$(CFLAGS) 
