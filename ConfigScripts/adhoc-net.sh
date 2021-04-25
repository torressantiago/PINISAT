#!/bin/bash
INTERFACE=wlan0
sudo ip addr add 192.169.1.1/24 dev $INTERFACE
sudo dnsmasq --no-daemon --listen-address 192.169.1.1 --interface $INTERFACE --dhcp-range=192.169.1.50,192.169.1.150,12h
