https://www.raspberrypi.org/documentation/configuration/wireless/access-point-routed.md
# get IP address
$(grep -w storresb /var/lib/misc/dnsmasq.leases | cut -b 30,31,32,33,34,35,36,37,38,39,40)
