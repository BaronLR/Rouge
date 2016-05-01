# Rouge in ncurses 
A version of Rouge written in C that runs in the terminal. Summer project based on some code from CIS2500. 

This code might require the Ncurses library to compile, if you don't have it just brew install ncurses 

#Run
pi@username ~/Rouge $ make

after you can run,

pi@username ~/Rouge ./rouge assets/hard.txt (this is the seed file) 
in the future you will be able to just ./rouge and it will randomly generate it for you. 

#Clean up
pi@username ~/Rouge $ make clean

this will remove the .o files from root directory
It creates an executable in the root directory called 'rouge'

#What to expect 
Things I plan on doing before the end of the summer, 

1. Random level generation 
2. Character level progression and stats saving 
3. Color 


This is live development, meaning that the code won't always compile, there might be times when I push broken code
