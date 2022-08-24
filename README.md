----<br>
simple program with a command line interface that allows to look at information on currently running processes<br>
can be used to dsiplay and keep track of newly launched processes<br>
features:<br>
 -a mode that scans and dumps all the newly launched processes (watchdog mode)<br>
 -detailed information on a process id<br>
 -shows what command was used to launch the process<br>
 -dump to file option<br>
 -run pmmanager h for more information<br>

INSTALL:<br>
 ./make.sh<br>
 sudo cp ./pmmanager /usr/local/bin

REQUIRES:
 gcc

Original code written by Evan Nikitin

SAMPLE OUTPUT:


$ pmmanager watchdog<br>
NEW: 85782 Thunar<br>
NEW: 85792 tumblerd<br>
NEW: 85970 folder-thumbnai<br>
NEW: 85972 convert<br>
NEW: 86604 <exited> - means the the process exited too fast to be logged<br>
NEW: 86652 xfce4-screensho<br>
^C
