# Flipper Zero Powerglove
Control the Flipper Zero nav buttons via GPIO

![image](https://github.com/user-attachments/assets/316f0d01-c32c-47c4-a7de-948ed3c14242)

This is a modification of the Flipper Zero cfw, [Unleashed-Firmware](https://github.com/DarkFlippers/unleashed-firmware) that adds a service to the device startup that loops through the GPIO pins (specifically pa7, pa6, pa4, pb3, pb2, and pc3) and then invokes a input event via pubsub


This is still very heavily experimental and is a work in progress - I offer no garuntees that using this won't brick your device, I certainly have had my own struggles with that

Currently all I can offer in way of instructions on how to install this is to add these files to a git clone of the unleashed-firmware files, and then build + flash to your device using FBT

[Video demonstration of it working](https://youtu.be/2p73w9Z-eLI)

![image](https://github.com/user-attachments/assets/f93fa504-114e-4821-99fe-7dd111294c63)


---

It is a known bug that having this code running makes the existing physical "Ok" and the "Down" not work - I do not currently know why, but the GPIO OK and Down buttons still work

(side note: There are some modifications to the settings, but these are not finished or functional yet, it just adds a little UI line for now and steals its data from another system setting... I will in time make it actually functional, but until then, feel free to not build that.)


(side side note: I have never had to write anything in C, my home language is Python and Powershell, so this has been a very confusing and difficult process, please keep in mind that many of the things I've written CAN be executed in much better and safer ways, but I'm fully committed to rapid prototyping and bodging to make something that covers the basic funtion, and then coming back and making it good, thank you for your patience )

---

This project is HEAVILY WIP, but once I've created a fully functional prototype, I will be creating a video with instructions on the physical build of the device
