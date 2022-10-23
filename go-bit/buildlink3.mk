# $NetBSD$

BUILDLINK_TREE+=	bit

.if !defined(BIT_BUILDLINK3_MK)
BIT_BUILDLINK3_MK:=

BUILDLINK_CONTENTS_FILTER.bit=	${EGREP} gopkg/
BUILDLINK_DEPMETHOD.bit?=		build

BUILDLINK_API_DEPENDS.bit+=	bit>=20130913
BUILDLINK_PKGSRCDIR.bit?=	../../wip/go-bit
.endif	# BIT_BUILDLINK3_MK

BUILDLINK_TREE+=	-bit
