Controls:
Up arrow: jump (hold down for full jump, release early to return to ground sooner)
Left arrow: move left
Right arrow: move right
Left Arrow + Right Arrow: beach ball movement left
Right Arrow + Left Arrow: beach ball movement right
1: switch to timeline speed of 0.50
2: switch to timeline speed of 1.00 (real time)
3: switch to timeline speed of 2.00
p: toggle between pausing and unpausing the game (can only change every .5 seconds)



Within the folders labelled ClientFolder and ServerFolder:
Open your linux distributor or follow the setting up SFML instructions in the CSC481 001 moodle (I used WSL:Ubuntu-20.04)
so that you have one terminal for ServerFolder and four terminals for ClientFolders

**If main files aren't compiled, which it should be already, type the following two commands in the terminal**
    1: make clean
    2: make


Instructions on how to run program(s):

in the linux terminal opened in ServerFolder, type the following to run the program: ./main
(give the server a second to start)
in the first linux terminal opened in ClientFolder, type the following to run the program: ./main
in the second linux terminal opened in ClientFolder, type the following to run the program: ./main
in the third linux terminal opened in ClientFolder, type the following to run the program: ./main
in the fourth linux terminal opened in ClientFolder, type the following to run the program: ./main

You should now have four synchronized client windows that take input when the window is open/focused


Ctrl + C to stop any terminal left running when closing programs



credit towards clip art PNG of beach ball used as client(s) texture:
https://clipart-library.com/clip-art/beach-ball-transparent-background-23.htm


