#!/bin/sh -e
#
# rc.local
#
# This script is executed at the end of each multiuser runlevel.
# Make sure that the script will "exit 0" on success or any other
# value on error.
#
# In order to enable or disable this script just change the execution
# bits.
#
# By default this script does nothing.

# Print the IP address
#!/bin/bash

cd /home/pi/epaper/test/c-weather/src
LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH
cd /home/pi/epaper/test/bcm2835
export LD_LIBRARY_PATH
./epd-connecting

sleep 17

wget -q --spider http://google.com

if [ $? -eq 0 ]; then
	echo "Online"
	./epd-main
else
	echo "Offline, rebooting..."
	./epd-error
	sleep 10
	shutdown -r now
fi

exit 0
