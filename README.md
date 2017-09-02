# Game_liSokoban
#### Sokoban, also called push boxes or box pushing, is a game where you must push boxes in their right places.

#### Author: Haozheng Li
#### Email: sai-2008@qq.com or akaHaozhengLi@gmail.com

## 0 How to initialize?

This project is coded in C++ using MFC, in Visual Studio 2010 or 2013.

To initialization, please change the codes in the function "void CPushingBoxView::Start()" as follow steps:

#### 1) Set the walls

cell[i][j].weitu = 1;

#### 2) Set boxes' destination

cell[i][j].weitu = 2;

#### 3) Set boxes' first places

cell[i][j].thing = 2;

#### 4) Set player's first place

renx = t_renx = 4;

reny = t_reny = 1;

#### Be careful, all the i or x means col index, and all the j and y means row index.

## 1 How to play?

Press up, down, left and right to control the player.

Move and move until all the boxes are in their right places.

Press F2 to replay.

Press r to return to last step, but you only have one chance to return.

Press space to pause.

![image](https://github.com/HaozhengLi/Game_liSokoban/blob/master/result/result.jpg)

# Have fun!! :)

