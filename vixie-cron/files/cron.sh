#!/bin/sh
#

# PROVIDE: cron
# REQUIRE: LOGIN
# KEYWORD: shutdown

. /etc/rc.subr

name="cron"
rcvar=$name
command="/usr/sbin/${name}"
pidfile="/var/run/${name}.pid"

load_rc_config $name
run_rc_command "$1"
