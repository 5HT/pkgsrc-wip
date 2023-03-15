# $NetBSD$

BUILDLINK_TREE+=	htslib

.if !defined(HTSLIB_BUILDLINK3_MK)
HTSLIB_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.htslib+=	htslib>=1.17
BUILDLINK_ABI_DEPENDS.htslib+=	htslib>=1.17
BUILDLINK_PKGSRCDIR.htslib?=	../../wip/htslib

.endif	# HTSLIB_BUILDLINK3_MK

BUILDLINK_TREE+=	-htslib
