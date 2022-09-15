# $NetBSD: buildlink3.mk,v 1.1 2020/05/10 15:02:44 maya Exp $

BUILDLINK_TREE+=	gcc10-aux

.if !defined(GCC10_AUX_BUILDLINK3_MK)
GCC10_AUX_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gcc10-aux+=	gcc10-aux>=${_GCC_REQD}
BUILDLINK_ABI_DEPENDS.gcc10-aux+=	gcc10-aux>=10.0
BUILDLINK_PKGSRCDIR.gcc10-aux=		../../wip/gcc10-aux
BUILDLINK_DEPMETHOD.gcc10-aux?=		build

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_PREFIX.gcc10-aux}/gcc10-aux

BUILDLINK_FILES.gcc10-aux=	# empty
BUILDLINK_AUTO_VARS.gcc10-aux=	no

pkgbase := gcc10-aux
.include "../../mk/pkg-build-options.mk"
.include "../../mk/dlopen.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.endif

BUILDLINK_TREE+=	-gcc10-aux
