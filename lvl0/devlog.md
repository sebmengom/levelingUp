# Devlog LVL0

## What I did:
Wrote my first Raspberry Pi Pico Project. A ticker using my own CMakeLists.txt, and my own basic ticker logic.

## Bugs I found:
While I added the USB code in the CMakeLists.txt file, I forgot to initialize it on my main.cpp. I noticed that after I copied the executable into my Raspberry Pi Pico and my mac could not find the Pico, meaning they never had a handshake. After I added it it worked out.
I also learned about the order of the CMakeLists file lines, and why its important to set up many things before the sdk init and before the creation of the executable. PICO_BOARD goes before the include, and the other two go before add_executable because the target copies the settings when it's created

# NEXT: LVL1
