# $NetBSD$

BUILDLINK_TREE+=	raqm

.if !defined(RAQM_BUILDLINK3_MK)
RAQM_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.raqm+=	raqm>=0.7.1
BUILDLINK_PKGSRCDIR.raqm?=	../../wip/raqm

.endif	# RAQM_BUILDLINK3_MK

BUILDLINK_TREE+=	-raqm
