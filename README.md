# Flipper Zero Powerglove
Control the Flipper Zero nav buttons via GPIO

This is a modification of the Flipper Zero cfw, [Unleashed-Firmware](https://github.com/DarkFlippers/unleashed-firmware) that adds a service to the device startup that loops through the GPIO pins (specifically pa7, pa6, pa4, pb3, pb2, and pc3) and then invokes a input event via pubsub


This is still very heavily experimental and is a work in progress - I offer no garuntees that using this won't brick your device, I certainly have had my own struggles with that

Currently all I can offer in way of instructions on how to install this is to add these files to a git clone of the unleashed-firmware files, and then build + flash to your device using FBT

[Video demonstration of it working](https://youtu.be/2p73w9Z-eLI)

---

(side note: There are some modifications to the settings, but these are not finished or functional yet, it just adds a little UI line for now and steals its data from another system setting... I will in time make it actually functional, but until then, feel free to not build that.)


(side side note: I have never had to write anything in C, my home language is Python and Powershell, so this has been a very confusing and difficult process, please keep in mind that many of the things I've written CAN be executed in much better and safer ways, but I'm fully committed to rapid prototyping and bodging to make something that covers the basic funtion, and then coming back and making it good, thank you for your patience )