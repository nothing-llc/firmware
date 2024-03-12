# radio firmware
more description to come!

## getting started
make sure you have the right stuff installed. on linux (or in wsl):
```bash
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
```

clone the repo, change directory into it, then:
```bash
cd pico-sdk/
git submodule update --init
```
read [the getting started guide] for more info if you need it.

[the getting started guide]: https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf
