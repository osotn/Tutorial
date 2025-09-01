# intall PS4 Dual Shock gamepad
sudo apt-get install libpython3.6-dev
python3.6 -m pip install ds4drv
ds4drv

# Usb drive works straightforward.
# Bluetooth needs to pair.

PlayStation 4 joypads
=====================
Those devices use “cable-pairing” as well. Plug the joypads in via USB with the Bluetooth Settings opened, and Bluetooth turned on. You will get asked whether to set those joypads up without needing to press the PS button. Unplug them and press the PS button to use them over Bluetooth.

Using the “PS” and “Share” button combination to pair the joypad can also be used to make the joypad visible and pair it like any other Bluetooth device, if you don’t have a USB cable at hand.


Install SDL2
============

#install sdl2
sudo apt install libsdl2-dev libsdl2-2.0-0 -y;

#install sdl image  - if you want to display images
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;

#install sdl mixer  - if you want sound
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;

#install sdl true type fonts - if you want to use text
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;

`sdl2-config --cflags --libs`  -lSDL2_mixer -lSDL2_image -lSDL2_ttf


