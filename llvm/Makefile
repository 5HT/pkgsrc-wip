# $NetBSD: Makefile,v 1.82 2022/09/12 08:59:15 he Exp $
#
# When updating this, please also update:
# devel/include-what-you-use
# devel/lld
# devel/lldb
# devel/polly
# lang/clang
# lang/clang-tools-extra
# lang/compiler-rt
# lang/libcxx
# lang/libcxxabi
# lang/libunwind
# lang/wasi-compiler-rt
# lang/wasi-libcxx
# parallel/openmp
#
# Do not update:
#   lang/libLLVM
# because pkgsrc provides multiple versions and lang/libLLVM is
# logically libLLVM4.
#
# Always update all */buildlink3.mk to require the latest stable release
# version in BUILDLINK_API_DEPENDS, as there is no backwards compatibility.

.include "version.mk"

DISTNAME=	llvm-${LLVM_VERSION}.src
PKGNAME=	${DISTNAME:S/.src//}
CATEGORIES=	lang devel

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://llvm.org/
COMMENT=	Low Level Virtual Machine compiler infrastructure
LICENSE=	apache-2.0

# As of v15.0.0 llvm requires cmake source code to build
CMAKE=		cmake-${LLVM_VERSION}.src
EXTRA_DIST=	${CMAKE}${EXTRACT_SUFX}

SITES.${CMAKE}${EXTRACT_SUFX}=	\
	${MASTER_SITES:=${GITHUB_PROJECT}/releases/download/${GITHUB_RELEASE}/}

DISTFILES=	${DEFAULT_DISTFILES} ${EXTRA_DIST}

USE_LANGUAGES=		c c++14
USE_CMAKE=		yes
GCC_REQD+=		7
PYTHON_FOR_BUILD_ONLY=	yes

PYTHON_VERSIONS_INCOMPATIBLE=	27

NOT_FOR_PLATFORM+=	*-*-alpha
NOT_FOR_PLATFORM+=	*-*-vax

CONFIGURE_DIRS=		build
CMAKE_ARG_PATH=		${WRKSRC}

CMAKE_ARGS+=	-DCMAKE_BUILD_TYPE=Release
CMAKE_ARGS+=	-DCMAKE_C_COMPILER=${CC:Q}
CMAKE_ARGS+=	-DCMAKE_CXX_COMPILER=${CXX:Q}
CMAKE_ARGS+=	-DCMAKE_CXX_LINK_FLAGS=${LDFLAGS:Q}
CMAKE_ARGS+=	-DLLVM_BUILD_LLVM_DYLIB=ON
CMAKE_ARGS+=	-DLLVM_INCLUDE_BENCHMARKS=OFF
CMAKE_ARGS+=	-DLLVM_INSTALL_UTILS=ON
CMAKE_ARGS+=	-DLLVM_LINK_LLVM_DYLIB=ON
CMAKE_ARGS+=	-DLLVM_ENABLE_RTTI=ON

CMAKE_ARGS.Darwin+=	-DCMAKE_LIBTOOL=/usr/bin/libtool

CHECK_PORTABILITY_SKIP=	utils/buildit/build_llvm

# XXX perl is not added as a tool as it does not seem to be required
REPLACE_PERL+=		utils/*.pl
REPLACE_PERL+=		utils/codegen-diff
REPLACE_PERL+=		utils/llvm-native-gxx

REPLACE_PYTHON+=	tools/opt-viewer/*.py
REPLACE_PYTHON+=	tools/sancov/*.py
REPLACE_PYTHON+=	utils/*.py
REPLACE_PYTHON+=	utils/Misc/zkill
REPLACE_PYTHON+=	utils/bisect
REPLACE_PYTHON+=	utils/clang-parse-diagnostics-file
REPLACE_PYTHON+=	utils/lit/tests/Inputs/googletest-format/DummySubDir/OneTest.py
REPLACE_PYTHON+=	utils/llvm-build/llvm-build
REPLACE_PYTHON+=	utils/llvm-compilers-check
REPLACE_PYTHON+=	utils/llvm-lit/llvm-lit.in

TEST_TARGET=		check
TEST_ENV+=		LD_LIBRARY_PATH=${WRKDIR}/build/lib

# It may be that the Solaris linker is more strict here and they can be removed on
# all platforms.  Change this to a patch if verified.
SUBST_CLASSES.SunOS+=	linkmap
SUBST_STAGE.linkmap=	pre-configure
SUBST_FILES.linkmap=	tools/lto/lto.exports
SUBST_FILES.linkmap+=	tools/remarks-shlib/Remarks.exports
SUBST_SED.linkmap=	-e '/^LLVM/d'

LDFLAGS.SunOS+=		-lsocket -lnsl

.include "../../mk/bsd.prefs.mk"

PLIST_VARS+=	notdylib
.if ${SHLIB_TYPE} == "dylib"
SOEXT=		dylib
.else
SOEXT=		so
PLIST.notdylib=	yes
.endif
PLIST_SUBST+=	SOEXT=${SOEXT}
PLIST_SUBST+=	LLVM_MAJOR_VERSION=${LLVM_MAJOR_VERSION}

NOTDYLIBS=		LTO Remarks
.for libname in ${NOTDYLIBS}
PRINT_PLIST_AWK+=	/lib${libname}.${SOEXT}.${LLVM_MAJOR_VERSION}/ { gsub(/\.${SOEXT}\.${LLVM_MAJOR_VERSION}/, ".$${SOEXT}.$${LLVM_MAJOR_VERSION}"); print "$${PLIST.notdylib}" $$0; next }
.endfor
PRINT_PLIST_AWK+=	{ gsub(/\.${SOEXT}/, ".$${SOEXT}") }

# needs std::atomic with 64-bit CAS
.if ${MACHINE_ARCH} == "i386"
CXXFLAGS+=	-march=i586
.endif

.if ${MACHINE_ARCH:Mpowerpc*}
# Needed to avoid "relocation truncated to fit: R_PPC_REL24"
CFLAGS+=	-mlongcall
CXXFLAGS+=	-mlongcall
.  if ${OPSYS} == "NetBSD"
.    if ${OPSYS_VERSION} >= 099917
# The -mno-pltseq option is not available in gcc7, but is needed for
# the above-mentioned relocation truncation issue in newer GCC
CFLAGS+=	-mno-pltseq
CXXFLAGS+=	-mno-pltseq
.    endif # (just drop for older NetBSD)
.  else # Not NetBSD
# Let's just insist on newer gcc -- untested.
CFLAGS+=	-mno-pltseq
CXXFLAGS+=	-mno-pltseq
.  endif
.endif

.if ${OPSYS} == "NetBSD"
CMAKE_ARGS+=	-DPKGSRC_LLVM_PTHREADLIB=-lpthread
.endif

.include "options.mk"

# replacing config.guess is required even for cmake.
# It is used to detect correct LLVM_HOST_TRIPLE, e.g. for NetBSD/evbarm.
post-extract:
	${MKDIR} ${WRKSRC}/build
.for f in config.guess config.sub
	cp ../../mk/gnu-config/${f} ${WRKSRC}/cmake/${f}
.endfor
	${LN} -f -s ${WRKDIR}/${CMAKE} ${WRKDIR}/cmake

.include "../../devel/zlib/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../lang/python/tool.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/atomic64.mk"
.include "../../mk/bsd.pkg.mk"
