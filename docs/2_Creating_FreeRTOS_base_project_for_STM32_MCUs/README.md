# Creating FreeRTOS base project for STM32 MCUs

![image](Project.png)
- add FreeRTOS folder into project
\- in portable folder delete all folders exept GCC and MemMang
- add Config folder into project
- add Include part 
\- open Properties(alt+enter) => C/C++ General => Paths and Symbols => add include parth
![image](Properties.png)
- wite "#define configSUPPORT_DYNAMIC_ALLOCATION 1" in main file