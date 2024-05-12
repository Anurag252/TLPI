# Chapter-12

## `/Proc`
Proc file system is a virtual one as OS creates it on the fly. There are a number of files in 
/proc/pid

- fd : list of open file descriptors with symbolic links
- task - contains one sub dir per thread. Under each folder there is a dir structure same as /proc/pid

and many more

Under `/proc` there are anumber of files to provide system wide information.
like `/proc/net`

## uname
uname is prensent in `utsname.h` and contains important information about system, like sysname, nodename, release etc.

