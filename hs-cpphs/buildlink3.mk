# $NetBSD: buildlink3.mk,v 1.6 2011/11/16 16:49:53 phonohawk Exp $

BUILDLINK_TREE+=	hs-cpphs

.if !defined(HS_CPPHS_BUILDLINK3_MK)
HS_CPPHS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.hs-cpphs+=	hs-cpphs>=1.13.2
BUILDLINK_PKGSRCDIR.hs-cpphs?=	../../wip/hs-cpphs
.endif	# HS_CPPHS_BUILDLINK3_MK

BUILDLINK_TREE+=	-hs-cpphs
