# Game Command Terminal 2

This is a library that allows the use of custom scripts in the game Red Dead Redemption 2 and Red Dead Online. It supports scripts in Python, Lua, and C++. The library is available in two languages: English and Russian. 

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)

## Description

It's a useful tool for modders in Red Dead Online with which you can create missions, add additional custom content to the game, and make big changes to gameplay. Also included with the GCT2 is a set of various features that even the average gamer can use. And also if you have already learnt the game completely you can try to play the example mission that comes with the package, which you can start by typing `missions` in the terminal and then select the mission called `Example mission`.

The native caller of GCT2 is developed by me and it intercepts the execution of game function and executes the function that was requested from some external script, and after the requested function will be executed it will return the execution of the original function again.

When injecting GCT2 in the game launcher may hang for a while this is due to the fact that the launcher copies all the necessary files to the root folder of Red Dead Redemptio 2 and when you close the launcher all these files will be automatically deleted if the game is closed, so before closing the launcher close the game or you can not do it then GCT2 will inject much faster.

## Installation

Installation should be done automatically at the first start of `Launcher.exe` you should restart your computer and see if in the system environment variable `PATH` path to the root folder with GCT2, if there is no such path, then add it manually otherwise GCT2 will not be able to work.

## Usage

If you are a developer, you can create scripts in a GCT2 supported programming language and place them in the Scripts folder, from which they will be automatically launched when GCT2 starts, or if GCT2 is already running you can enter the restart scripts command in the console to restart all scripts and run new ones. GCT2 itself can be launched with the help of `Launcher.exe`, a programme that allows you to introduce GCT2 into the game during the game and also with the help of Launcher you can customise GCT2 for yourself. Also in the Launcher there is a built-in terminal, but for its correct operation you need to disable the in-game console in the environment settings, on the terminal tab there is a button `Commands` in the lower right corner, which provides a list of commands that can be entered into the terminal and their detailed description.

If you are not a developer you can start GCT2 and use the terminal to enter commands such as `set time` or `set infinity ammo` and many others. You can also click on the first side button to quickly regenerate or you can click on this button twice to force all your and your horse's statuses, you can also click on the second side button to open a small interactive menu

## Examples

Examples can be found in the `Scripts/examples` folder and in the `Scripts` folder. And also an example of a C++ script in `Scripts\Sample` which you only have to compile and move to the `Scripts` folder and then it will run.