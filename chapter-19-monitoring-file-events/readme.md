` fd = inotify_init()` creates file descriptor for notify
`inotify_add_watch` adds watch on a file descriptor
` nftw(directory_to_watch, add_watch_all, fd_limit, flags);` reads and walks the file
`inotify_rm_watch` removes watch.

Program works for happy path and only creation part. TODO deletion and renames