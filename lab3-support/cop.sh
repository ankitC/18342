make clobber
make
sudo cp ./kernel/kernel.bin /media/bootfs
sudo cp ./tasks/bin/hello.bin /media/bootfs
sync
sync
