# $NetBSD: Makefile,v 1.15 2022/08/14 13:52:26 tnn Exp $

.include "../../wip/llvm/version.mk"

DISTNAME=	libcxxabi-${LLVM_VERSION}.src
PKGNAME=	${DISTNAME:S/.src//}
CATEGORIES=	lang devel

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://libcxxabi.llvm.org/
COMMENT=	C++ Standard Library
LICENSE=	apache-2.0

# libcxx requires libcxxabi's cxxabi.h to build, but libcxxabi requires
# libcxx's includes to build, so we have this unholy extra distfiles thing
# in both of them to get them to build against each other without causing
# circular dependencies.  This must be kept in sync with libcxxabi/Makefile.
# As of v15.0.0 libcxxabi requires cmake source code to build
LIBCXX=		libcxx-${LLVM_VERSION}.src
LLVMDIST=	llvm-${LLVM_VERSION}.src
CMAKE=		cmake-${LLVM_VERSION}.src
EXTRA_DIST=	${LIBCXX}${EXTRACT_SUFX} ${LLVMDIST}${EXTRACT_SUFX} ${CMAKE}${EXTRACT_SUFX}

SITES.${LIBCXX}${EXTRACT_SUFX}=	\
	${MASTER_SITES:=${GITHUB_PROJECT}/releases/download/${GITHUB_RELEASE}/}
SITES.${LLLVMDIST}${EXTRACT_SUFX}=	\
	${MASTER_SITES:=${GITHUB_PROJECT}/releases/download/${GITHUB_RELEASE}/}
SITES.${CMAKE}${EXTRACT_SUFX}=	\
	${MASTER_SITES:=${GITHUB_PROJECT}/releases/download/${GITHUB_RELEASE}/}

DISTFILES=	${DEFAULT_DISTFILES} ${EXTRA_DIST}

CONFIGURE_DIRS=	build
CMAKE_ARG_PATH=	${WRKSRC}

USE_LANGUAGES=	c c++17
USE_CMAKE=	yes
SSP_SUPPORTED=	no
GCC_REQD+=	12	# must be in sync with libcxx

CMAKE_ARGS+=	-DCMAKE_BUILD_TYPE=Release
CMAKE_ARGS+=	-DCMAKE_C_COMPILER=${CC:Q}
CMAKE_ARGS+=	-DCMAKE_CXX_COMPILER=${CXX:Q}
CMAKE_ARGS+=	-DLIBCXXABI_LIBCXX_INCLUDES=${WRKDIR}/${LIBCXX}/include
CMAKE_ARGS+=	-DLIBCXXABI_USE_LLVM_UNWINDER=ON

# avoid conflict with stddef.h
CXXFLAGS.NetBSD+=	-D__DEFINED_max_align_t=1

.include "../../mk/compiler.mk"

.if !empty(CC_VERSION:Mgcc-[0-9].*) || !empty(CC_VERSION:Mgcc-10.*)
# Avoid GCC < 11 error https://github.com/llvm/llvm-project/issues/54018
CXXFLAGS+=		-std=c++17 -D_LIBCPP_STD_VER=17
.endif

post-extract:
	${MKDIR} ${WRKSRC}/build
	${LN} -f -s ${WRKDIR}/${LIBCXX} ${WRKDIR}/libcxx
	${LN} -f -s ${WRKDIR}/${LLVMDIST} ${WRKDIR}/llvm
	${LN} -f -s ${WRKDIR}/${CMAKE} ${WRKDIR}/cmake
# TODO: not sure what should create this and with which contents
	${TOUCH} ${WRKDIR}/${LIBCXX}/include/__config_site

.include "../../wip/libunwind/buildlink3.mk"
.include "../../wip/llvm/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
