$NetBSD$

Patch for pkgsrc feature "err" (USE_FEATURES).
Add forward declarations for lexer and parser functions.

--- src/config.y.orig	2021-04-17 20:18:01.000000000 +0000
+++ src/config.y
@@ -18,9 +18,25 @@
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
- 
+
+#if defined(HAVE_NBCOMPAT_H)
+#include <nbcompat/config.h>    /* Needed for the other headers */
+#include <nbcompat/cdefs.h>     /* Needed for the other headers */
+#include <nbcompat/err.h>
+#else
+#include <err.h>
+#endif
+
 #include "main.h"
 
+/* Lexer generated by flex */
+extern int
+yylex(void);
+
+/* Parser generated by bison */
+int
+yyparse(void);
+
 extern char *yytext;
 extern FILE *yyin;
 extern int size_sockinfo_t; /* is set to 0 on startup in main.c */