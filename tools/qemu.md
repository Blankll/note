## qemu setup ubuntu in macos

```bash
# install
brew install qemu
# check version
qemu-system-x86_64 --version
# create disk image
qemu-img create -f qcow2 ubuntu-20.04.1-desktop-amd64.qcow2 20G
# check host cpu arch
sysctl -n machdep.cpu.brand_string
# Boot machine with Ubuntu ISO mounted
qemu-system-x86_64 \
    -machine type=q35,accel=hvf \
    -cpu CoffeeLake \
    -smp 2 \
    -hda ubuntu-20.04.1-desktop-amd64.qcow2 \
    -cdrom ~/Documents/iso/ubuntu-20.04.4-desktop-amd64.iso \
    -m 4G \
    -vga virtio \
    -usb \
    -device usb-tablet \
    -display default,show-cursor=on
```

