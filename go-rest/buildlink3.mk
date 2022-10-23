# $NetBSD$

BUILDLINK_TREE+=	go-rest

.if !defined(GO_REST_BUILDLINK3_MK)
GO_YAML_GHODSS_BUILDLINK3_MK:=

BUILDLINK_CONTENTS_FILTER.go-rest=	${EGREP} gopkg/
BUILDLINK_DEPMETHOD.go-rest?=		build

BUILDLINK_API_DEPENDS.go-rest+=		go-rest>=0.0
BUILDLINK_PKGSRCDIR.go-rest?=		../../wip/go-rest
.endif  # GO_REST_BUILDLINK3_MK

BUILDLINK_TREE+=	-go-rest
