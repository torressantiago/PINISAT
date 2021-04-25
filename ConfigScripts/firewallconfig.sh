#!/bin/bash
# Note: $1 corresponds to the destination address and $2 to the source (rpi)
sudo iptables -t filter -A INPUT -d $1 -s $2/24 -p udp -m state --state NEW -j ACCEPT
