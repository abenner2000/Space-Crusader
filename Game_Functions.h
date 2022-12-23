// Author: Andrew Benner, andrewbenner918@gmail.com
// Function protoypes for Game Functions driver

#include <stdint.h>

#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

void Game_HomeSetup(void);

void Game_LaserShoot(void);
void Game_MissileShoot(void);

void Game_Level1Setup(void);
void Game_Level2Setup(void);
void Game_Level3Setup(void);

void Game_PlayerMove(uint16_t slideVal);

void Game_Level1EnemyMove(void);
void Game_Level1CheckHit(void);

_Bool Game_Level1CheckLose(void);
_Bool Game_Level1CheckWin(void);

void Game_Level2EnemyMove(void);
void Game_Level2CheckHit(void);

_Bool Game_Level2CheckLose(void);
_Bool Game_Level2CheckWin(void);

void Game_Level3EnemyMove(void);
void Game_Level3CheckHit(void);

_Bool Game_Level3CheckLose(void);
_Bool Game_Level3CheckWin(void);

void Game_CalcScore(void);
void Game_EndScreen(void);

void Game_Level1Draw(void);
void Game_Level2Draw(void);
void Game_Level3Draw(void);

#endif
