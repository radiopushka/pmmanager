----
simple program with a command line interface that allows to look at information on currently running processes
can be used to dsiplay and keep track of newly launched processes
features:
 -a mode that scans and dumps all the newly launched processes (watchdog mode)
 -detailed information on a process id
 -shows what command was used to launch the process
 -dump to file option
 -run pmmanager h for more information

INSTALL:
 ./make.sh
 sudo cp ./pmmanager /usr/local/bin

REQUIRES:
 gcc

Original code written by Evan Nikitin

SAMPLE OUTPUT:


$ pmmanager watchdog
NEW: 85782 Thunar
NEW: 85792 tumblerd
NEW: 85970 folder-thumbnai
NEW: 85972 convert
NEW: 86604 <exited> - means the the process exited too fast to be logged
NEW: 86652 xfce4-screensho
^C
