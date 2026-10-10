#ifndef GAME_H
#define GAME_H

byte gameOverAndStageFase;
boolean bonusVisible;
boolean nextLevelVisible;
boolean pressKeyVisible;
int leftX;
byte rightX;

// stateGamePlaying
// called each frame the gamestate is set to playing
void stateGamePlaying()
{
  // Update Level
  byte spawnTime = (gameType != STATE_GAME_MAYHEM) ? 60 : 15;
  if (arduboy.everyXFrames(spawnTime * 3)) spawnZombie();

  // Check for Pause
  if (arduboy.pressed(A_BUTTON + B_BUTTON)) gameState = STATE_GAME_PAUSE;

  // Update Objects
  updatePlayer(coolGirl);
  updateBullets();
  updateZombies();
  updateSurvivors();

  // Draw
  drawLevel();
  drawDoor();
  drawPickups();
  drawSurvivors();
  drawZombies();
  drawBullets();
  drawPlayer(coolGirl);
  drawCompass();

  drawNumbers(86, 0, FONT_SMALL, DATA_SCORE);
  drawLife(coolGirl);
  drawAmountSurvivors();
  drawCoolDown();
}

// the positions in the level data are in tiles
int readSurvivorData(byte index)
{
  return read6(survivorLocation, (level - 1) * 10 + index) * TILE_WIDTH;
}

int readPlayerAndExitData(byte index)
{
  byte tempLevel = (gameType != STATE_GAME_MAYHEM) ? displayLevel : level;
  return read6(playerAndExitLocation, (tempLevel - 1) * 4 + index) * TILE_WIDTH;
}

// stateGamePrepareLevel
// called each frame the gamestate is set to prepare level
void stateGamePrepareLevel()
{
  clearSurvivors();
  clearPickups();
  clearZombies();

  level++;

  if (gameType != STATE_GAME_MAYHEM) level = (level - 1) % NUM_MAPS + 1;
  else level = random(NUM_MAPS) + 1;
  displayLevel++;

  pickupsCounter = 0;
  gameOverAndStageFase = 0;
  globalCounter = 0;

  gameState = STATE_GAME_NEXT_LEVEL;
}

void nextLevelStart()
{
  leftX = -50;
  rightX = 154;
  if ((displayLevel == 1) || (gameType == STATE_GAME_CONTINUE))
  {
    bonusVisible = false;
    nextLevelVisible = true;
    pressKeyVisible = false;
    gameOverAndStageFase = 4;
  }
  else
  {
    bonusVisible = true;
    nextLevelVisible = false;
    pressKeyVisible = false;
    gameOverAndStageFase++;
  }
}

void nextLevelBonusCount()
{
  if (exitDoor.counter > 0)
  {
    exitDoor.counter--;
    scorePlayer += 5;
  }
  else
  {
    if ((displayLevel < 129) || (gameType == STATE_GAME_MAYHEM)) gameOverAndStageFase++;
    else
    {
      gameState = STATE_GAME_END;
      gameOverAndStageFase = 0;
    }
  }
}

void nextLevelWait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 8)
  {
    gameOverAndStageFase++;
    globalCounter = 0;
  }
}

void nextLevelSlideToMiddle()
{
  bonusVisible = false;
  nextLevelVisible = true;
  if (leftX < 21)
  {
    leftX += 4;
    rightX -= 4;
  }
  else gameOverAndStageFase++;
}

void nextLevelEnd()
{
  if (arduboy.everyXFrames(30)) pressKeyVisible = !pressKeyVisible;
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_GAME_PLAYING;
    gameOverAndStageFase = 0;
    bonusVisible = false;
    nextLevelVisible = false;
    pressKeyVisible = false;
    leftX = -50;
    rightX = 154;

    coolGirl.x = readPlayerAndExitData(0);
    coolGirl.y = readPlayerAndExitData(1);
    setDoorPosition(readPlayerAndExitData(2), readPlayerAndExitData(3));
    swapSurvivorPool();

    byte maxId = 5;
    if (gameType != STATE_GAME_MAYHEM)
    {
      // save the game
      SaveData save = { gameID, displayLevel, scorePlayer, coolGirl.health, gameID };
      EEPROM.put(OFFSET_VLQP_START, save);
      maxId = (((displayLevel % TOTAL_LEVEL_AMOUNT) - 1) / NUM_MAPS) + 2;
    }

    for (byte id = 0; id < maxId; id++)
    {
      Element& surv = survivors[id];
      surv.x = readSurvivorData(2 * id);
      surv.y = readSurvivorData((2 * id) + 1);
      surv.active = true;
    }
  }
}

const FunctionPointer PROGMEM nextLevelFases[] =
{
  nextLevelStart,
  nextLevelWait,
  nextLevelBonusCount,
  nextLevelWait,
  nextLevelSlideToMiddle,
  nextLevelWait,
  nextLevelEnd,
};

void stateGameNextLevel()
{
  ((FunctionPointer) pgm_read_word (&nextLevelFases[gameOverAndStageFase]))();
  if (bonusVisible)
  {
    sprites.drawSelfMasked(32, 16, bonusPoints, 0);
    drawNumbers(78, 16, FONT_SMALL, DATA_TIMER);
    drawNumbers(36, 36, FONT_BIG, DATA_SCORE);
  }
  if (nextLevelVisible)
  {
    sprites.drawSelfMasked(leftX, 24, nextLevel, 0);
    if (pressKeyVisible)
    {
      if (gameType == STATE_GAME_MAYHEM) sprites.drawSelfMasked(41, 8, textMayhem, 0);
      else sprites.drawSelfMasked(43, 8, textNormal, 0);
      sprites.drawSelfMasked(37, 48, pressKey, 0);
    }
    drawNumbers(rightX, 24, FONT_BIG, DATA_LEVEL);
  }
}

// game over and game end
void gameOverEnd()
{
  if (arduboy.everyXFrames(30)) pressKeyVisible = !pressKeyVisible;
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
    gameOverAndStageFase = 0;
    pressKeyVisible = false;
  }
}

const FunctionPointer PROGMEM gameOverFases[] =
{
  nextLevelWait,
  nextLevelWait,
  nextLevelWait,
  nextLevelWait,
  gameOverEnd,
};

void stateGameOver()
{
  ((FunctionPointer) pgm_read_word (&gameOverFases[gameOverAndStageFase]))();
  if (gameType == STATE_GAME_MAYHEM) sprites.drawSelfMasked(41, 3, textMayhem, 0);
  else sprites.drawSelfMasked(43, 3, textNormal, 0);
  sprites.drawSelfMasked(11, 15, gameOver, 0);
  drawNumbers(35, 34, FONT_BIG, DATA_SCORE);
  if (pressKeyVisible) sprites.drawSelfMasked(37, 53, pressKey, 0);
}

void stateGameEnd()
{
  ((FunctionPointer) pgm_read_word (&gameOverFases[gameOverAndStageFase]))();
  sprites.drawSelfMasked(22, 8, youWon, 0);
  drawNumbers(36, 32, FONT_BIG, DATA_SCORE);
  if (pressKeyVisible) sprites.drawSelfMasked(37, 56, pressKey, 0);
}

void stateGamePause()
{
  drawBadge();
  sprites.drawSelfMasked(37, 40, pause, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_GAME_PLAYING;
    sprites.drawSelfMasked(22, 32, gameOver, 0);
  }
}

void stateGameNew()
{
  level = LEVEL_TO_START_WITH - 1;
  displayLevel = level;
  initializePlayer(coolGirl);
  gameState = STATE_GAME_PREPARE_LEVEL;
}

void stateGameContinue()
{
  SaveData save;
  EEPROM.get(OFFSET_VLQP_START, save);
  if ((save.idStart == gameID) && (save.idEnd == gameID))
  {
    initializePlayer(coolGirl);
    displayLevel = save.level - 1;
    level = (displayLevel % NUM_MAPS);
    scorePlayer = save.score;
    coolGirl.health = save.health;
    gameState = STATE_GAME_PREPARE_LEVEL;
  }
  else gameState = STATE_GAME_NEW;
}

void stateGameMayhem()
{
  displayLevel = 0;
  gameState = STATE_GAME_PREPARE_LEVEL;
  initializePlayer(coolGirl);
}

#endif
