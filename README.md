
# The-OrcaClaw
Resembling (sort of) Victor's Hexclaw from League of Legends/Arcane, the OrcaClaw is a powerful(weak) arm that can be controlled remotely, and has the ability to grab and point using a laser!

This is my first ever project outside of tinkering with a breadboard and sensors. I've never modeled, made a pcb, or know a lot about assembly(hardware components, screw types). However, after a lot of work and hours done, I was able to learn a lot, and also was able to produce this project, the OrcaClaw!

**What makes this unique**: You will never see this in the real world(cause it's kinda useless), that's just how unique it is! Resembling a Hexclaw and an Orca, the OrcaClaw is able to be able to grab _some_ items in your daily life! Whether you need to hold on to an empty soda can(for some reason), or claw menacingly at someone you don't like, the OrcaClaw, _in addition_, allows you to point at things using it's built in laser! Just like the Hexclaw, it's dangerous(if you shine it in someone's eyes, don't do that), and can ward off people who don't like light(like vampires)!

**Why I made this project**: Originally, I was going to create just a robot arm that is able to write something, with remote capabilities, like either being remote controlled or master-slave. The reason the idea pivoted was because after joining the Fallout kickoff call, I was more inspired to create something not so boring and unoriginal. An arm seemed like a perfect guide in my opinion; I will be able to make something move(neurons firing!), and learn modeling, creating PCB's, and wireless communication. I was still able to learn everything; but now the idea is much cooler! 

Here is a list of things I learned from this project:

**Modeling**

**PCB Creation**

Assembly: 
- Different screw uses (M3 Machine Vs Thread forming, M2.6 for circuit boards)
- Onshape Assembly
- Claw Machine/Linkage style claw mechanism
- Tolerances
  
Hardware:
- Voltage step-down (Buck Converter)
- Wary of current draw (Increasing wire thickness and AWG sizes)
- Wary of current draw x2 (Capacitors for MG996R Servos)
- MOSFET gate

And more!

Here is a list of _problems_ I ran into for this project:
- WHY IS EVERYTHING EXPENSIVE
- Batteries < $20 having the battery life of a potato
- One of the batteries I bought was fine then I realized later the turtle from the tortoise and the hare race was the one delivering the product
- Buying components irl to accomodate in the design, and then realising there were cheaper options so now I have to buy those ones to stick to the BOM and source material
- Errors in OnShape
- Extrude? Hello? It's a closed area?
- Had to restart early on, not too bad though
- Screws not screwing (There's two types of screws, machine screws and thread-forming???)
- Tolerances not tolerating
- Logic errors
- Having to sacrifice a lot of rotation degrees
- Chance of the first MG996R not being able to hold up
- Trying to install the XIAO footprint (wth is git submodules and somethingEDA)
- Trying to upload the PCB to JLCPCB (literally only the holes appeared for some reason)
- AliExpress shipping lowkey being the product
- AliExpress being a master of manipulation (they removed a $20 off deal the moment I hit buy)
- One of the only good laser modules is $20 (wth)
- Slack, Fallout issues (why is fallout using a slack I never technically created?)
- Doing research at night, thinking it'd only take me a few minutes but taking me 1-2 hours I could've tracked
- Github uploading the individual files instead of the folder
- AAAAAHHH


OrcaClaw 3D Model:
<img width="622" height="521" alt="image" src="https://github.com/user-attachments/assets/dbcac449-9fe1-40d9-a951-2ceeaea3f03e" />
<img width="668" height="698" alt="image" src="https://github.com/user-attachments/assets/f82676ca-1439-454b-a341-600e9959188d" />

OrcaController 3D Model:
<img width="1031" height="573" alt="image" src="https://github.com/user-attachments/assets/1a6d5f7a-f654-44dc-a249-d4d6a6fdf5a7" />

<img width="611" height="541" alt="image" src="https://github.com/user-attachments/assets/62a1dd37-85e0-4a50-88f5-573379ae11fc" />


OrcaClaw PCB:
<img width="574" height="482" alt="image" src="https://github.com/user-attachments/assets/679ef34f-4b4b-41da-ac92-7c2b3d4af311" />
<img width="571" height="483" alt="image" src="https://github.com/user-attachments/assets/db288cec-d0c4-48b3-a4e3-090a292321d8" />



OrcaClaw Controller PCB:
<img width="747" height="393" alt="image" src="https://github.com/user-attachments/assets/566920ae-2fcd-4147-8d87-605b8b50dac6" />

**Wiring Diagram / Schematic:**

OrcaClaw Schematic:
<img width="1497" height="705" alt="OrcaClawSchematic" src="https://github.com/user-attachments/assets/3fc98e9a-3065-4878-b0c6-d830a4fd9c4d" />


The OrcaClaw controller schematic is just the PCB schematic with a extra battery:
<img width="803" height="690" alt="OrcaClawControllerSchematic" src="https://github.com/user-attachments/assets/cada2a1d-b18e-49df-b277-aab466843458" />



**How to use:** Attach arm and backpack straps with the clips onto the backplate. Wear it like a backpack. Congratulations! The OrcaClaw is now mounted on your back! 

On the controller, there is two buttons. One of them allow for movement control. By pressing it down and moving your arm accordingly, the accelerometer will translate that movement into the servo movement. The other button activates the claw to open/close.

The absolute MESS of a cad(LISTEN. THIS THE FIRST TIME I'M ACTUALLY DOING MODELING. I DIDN'T REALIZE IT WOULD LOOK THIS UNORGANIZED. PLEASE SPARE ME):
https://cad.onshape.com/documents/d7ad806e815c1aad37a0e64a/w/e4d9f00fe60cfe8595f9785c/e/b1601408fc0aed2b47a9de74?renderMode=0&uiState=69e82076497156923c10f2e7 

You may find the **BOM** here: https://github.com/OrcaTheWhale/The-OrcaClaw/blob/d58308c58e4bb3730a3b75af7c206a2e41ff7d3b/Bill%20of%20Materials.csv

**HEADS UP!** The BOM assumes you have a soldering iron. The prices are in CAD(Canadian money, not modeling software you nerds), and shipping prices will vary from region.
The printing legion shipping cost also may vary.

The firmware is also set in platformio! If you are using Arduino IDE, please feel free to do so.

