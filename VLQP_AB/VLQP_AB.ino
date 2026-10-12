/*
  VIRUS LQP-79: https://t-arg.github.io/ID-40-VIRUS-LQP-79/

  Arduboy version 2.0.0:  https://github.com/T-arg/ID-40-VIRUS-LQP-79/releases/latest

  MADE by TEAM a.r.g. : https://t-arg.github.io

  2016 - FUOPY - JO3RI - STG - CASTPIXEL - JUSTIN CYR

  UPDATED

  2026 - JO3RI

  Game License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID                  40

#include "globals.h"
#include "music.h"
#include "bitmaps.h"
#include "level.h"
#include "bullet.h"
#include "enemies.h"
#include "elements.h"
#include "door.h"
#include "pickup.h"
#include "player.h"
#include "menu.h"
#include "game.h"

const FunctionPointer PROGMEM mainGameLoop[] =
{
  stateMenuIntro,
  stateMenuMain,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGamePrepareLevel,
  stateGameNextLevel,
  stateGamePlaying,
  stateGameOver,
  stateGamePause,
  stateGameEnd,
  stateGameNew,
  stateGameContinue,
  stateGameMayhem,
  stateMenuJbox,
};

void setup()
{
  arduboy.boot();                                           // begin with the boot logo en setting up the device to work
  arduboy.audio.begin();
  arduboy.bootLogoSpritesSelfMasked();
  arduboy.setFrameRate(60);
  gameID = GAME_ID;
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  musicUpdate();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}
