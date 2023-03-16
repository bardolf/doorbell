#!/bin/bash

export DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/$(id -u)/bus
echo $DBUS_SESSION_BUS_ADDRESS
DISPLAY=:0.0 notify-send -t 3 -i dialog-warning "Doorbell" 
#DISPLAY=:0 gxmessage WARNING -nearmouse -timeout 1 -borderless -buttons "" -ontop -nofocus
echo "Done"
