# Flight-Simulator-Cpp

Flight Simulator is a cpp program that control a plane From FlightGear Game.

Created by [KfirYehuda](https://github.com/kfiryehuda) and 
 [BenAzoulayDev](https://github.com/benazoulaydev)

Link to [Repository](https://github.com/benazoulaydev/Flight-Simulator-Cpp)

## Installation
Please read flightgear [installations](https://www.flightgear.org/download/main-program/) carefully! It explicitly says how to download on which OS and where the files exist once you download onto your machine.
**newest mac users with Catalina, you may have problems with the simulator. I suggest finding a parter without the newest version of Mac OS. Those in dualboot on ubuntu, you can install flightgear from the app store (software center) that ubuntu has.


- Install [FlightGear](https://sourceforge.net/projects/flightgear/files/) to install Flight Simulator.

- Download the [code](https://github.com/benazoulaydev/Flight-Simulator-Cpp/archive/master.zip) from our repo.

- In the FlightGear Game Folder : game/flightgear/Protocol
add the file generic_small.xml. The file is in the asset directory (in the code you download from github). 
Note: You may need to change the permissions for copying this file to the folder. In my computer the folder is at : '/usr/share/games/flightgear/Protocol' 

- Open the FlightGear app, go to settings and to Additional Settings write : 
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small   
--telnet=socket,in,10,127.0.0.1,5402,tcp

- Copy fly.txt From the Assets folder to the same folder as the main.cpp.

## Usage
You can change the content inside fly.txt according to how you want the plane acts.
You can read the FlightSimulator - Clarifications.pdf and the hebrew explanation.pdf for a better understanding.
```cpp
g++ -std=c++14 *.cpp 
-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread 

./a.out fly.txt
```
- In Flight Gear app press Fly Button.


## Resources:
- How to install [Git](https://www.youtube.com/watch?v=SWYqp7iY_Tc) on Youtube.

- A [Video](https://drive.google.com/file/d/1Hn2pse_LFLGliL5lF6xQm9vHV6xEAYSg/view) on communication between windows and your virtual machine with the simulator.

- [New](http://wiki.flightgear.org/New_to_FlightGear) To FlightGear

- [Autostart](http://wiki.flightgear.org/Autostart) To FlightGear


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.



## License
[MIT](https://choosealicense.com/licenses/mit/)

