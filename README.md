# Wolf-3D:<br>a classic&emsp;[![Actions Status](https://github.com/rpeepz/Wolf-3D/workflows/C/Build/badge.svg)](https://github.com/rpeepz/Wolf-3D/actions)[![GitHub release](https://img.shields.io/github/v/release/rpeepz/Wolf-3D.svg)](https://github.com/rpeepz/Wolf-3D/releases)[![GitHub All Releases](https://img.shields.io/github/downloads/rpeepz/Wolf-3D/total.svg)](https://github.com/rpeepz/Wolf-3D/releases)[![GitHub license](https://img.shields.io/badge/Licence-The%20Unlicense-yellow.svg)](https://raw.githubusercontent.com/rpeepz/Wolf-3D/master/LICENSE)[![Twitter Follow](https://img.shields.io/twitter/follow/papagna94.svg?style=social&label=Follow)](https://twitter.com/papagna94)  
Here is my very basic implementation of a ray casting engine, inspired by the game Wolfenstein 3D <br/>


### Table Of Contents
* [Objective](#objective)
* [Installation](#installation)
* [Usage](#usage)
* [Project Structure](#project-structure)
* [Dependencies](#dependencies)
* [Future](#future)
* [Subject PDF](#subject-pdf)
* [Sources](#sources)
* [Keep In Touch](#keep-in-touch)

#### About 42  
[42][42] is a free, non profit, project-based, peer-to-peer learning coding school. It originated in France and now has over 20 campuses all over the world. More information can be found [here][42].

<br>

---

<br>

## Objective  
This projects goal: Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way  
sample with colored walls:  
![test](https://media.giphy.com/media/hqUNtN8YxAcxhASggN/giphy.gif "sample")  

<br>

Ive also played with data graphing during this time; here are my makefile dependencies
<img src="https://raw.githubusercontent.com/rpeepz/Wolf-3D/master/info/Makefile_graph.png" title="graph">  

<br>

## Installation
Download and compile repo:  
``` 
git clone https://github.com/rpeepz/Wolf-3D.git  
cd Wolf-3D  
make  
```  
Executable `wolf3d` will be created  
<br>

## Usage  

`./wolf3d [ file.map ]`
- file.map is any of the maps provided in the maps directory.  

For help run `./wolf3d help`  

Make sure you have the required [dependencies](#dependencies) before proceeding.  
For instructions and/or greater detail refer to the project [pdf](#subject-pdf)  

<br>

---  

<br>

## Project Structure

### Source files

```
src/
├── output/
|   └── out_console.c
├── utils/
│   ├── del.c
│   ├── init.c
|   └── parse.c
├── game.c
├── inputs.c
├── main.c
└── render.c

3 directories, 8 files
```

### Header files

```
includes/
├── keys.h
└── wolf3d.h

1 directory, 2 files
```
<br>

--- 

<br>

## Dependencies  
* A C language compiler most common would be GCC or Clang.
* Cmake to run the custom Makefile for fast instalation.
* Code was written to run on Unix based systems or anything with X Window System.

<br>

## Future 
No current plans for this project.  
<br>

## Subject PDF
[Wolf3D PDF][pdf]   

---  

## Sources  
[OneLoneCoder](https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA "informational")  
WolframAlpha.com - help with calculations  

<br>

---  

## Keep in Touch

You can find me on:
* [Github](https://github.com/rpeepz)  
* [Twitter](https://twitter.com/papagna94) 
* [LinkedIn](https://www.linkedin.com/in/rpapagna-510) 
<!-- * [Medium](https://medium.com/@themichaelbrave)  -->
<!-- * [Home] -->

<br>

---

_This project was attempted for learning purposes only. This repo may not be kept up to date and I cannot guarantee that it will work on your future machines. You are welcome to use and learn from this as you want, but do not implement code that you do not understand. These sources listed above have been invaluable and I advise you to do research on the subject before trying to copy the code you see here._  

<br>


[42]: http://42.us.org "42 USA"
[pdf]:  https://github.com/rpeepz/Wolf-3D/blob/master/info/wolf3d.en.pdf "wolf-3d"
