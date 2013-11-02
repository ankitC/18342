make clobber
echo "********** make clobber done ***********"
make
echo "********** make done ***********"
sudo cp ./kernel/kernel.bin /media/bootfs
echo "********** copied kernel.bin ***********"
sudo cp ./tasks/bin/hello.bin /media/bootfs
echo "********** copied hello.bin **********"
sudo cp ./tasks/bin/twister.bin /media/bootfs
echo "********** copied twister.bin **********"
sudo cp ./tasks/bin/typo.bin /media/bootfs
echo "********** copied typo.bin **********"
sudo cp ./tasks/bin/splat.bin /media/bootfs
echo "********** copied splat.bin **********"
sync
sync
echo "********** synced ***********"
make clobber
echo "********** again make clobber **********"
