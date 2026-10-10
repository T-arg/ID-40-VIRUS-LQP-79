#ifndef MENU_H
#define MENU_H

byte menuSelection = STATE_MENU_PLAY;
byte slideCounter = 0;

void drawTitleScreen()
{
  sprites.drawSelfMasked(0, 0, titleScreen00, 0);
  sprites.drawSelfMasked(62, 32, titleScreen01, 0);
  sprites.drawSelfMasked(66, 0, titleScreen02, 0);
}

void drawBadge()
{
  sprites.drawSelfMasked(30, 0, titleScreen02, 0);
  sprites.drawSelfMasked(92, 0, titleScreen03, 0);
}

void setSlidersToZero()
{
  globalCounter = 0;
  slideCounter = 0;
}

void makeItSlide()
{
  slideCounter++;
  if (slideCounter > 22)
  {
    globalCounter++;
    slideCounter = 22;
  }
  if (globalCounter > 5) globalCounter = 5;
}

// the title screen with the sliding in panel behind the menu text
void drawMenuPanel()
{
  drawTitleScreen();
  for (byte i = 0; i < 3; i++)
  {
    sprites.drawOverwrite(127 - slideCounter + (8 * i), 25, smallMask, 0);
  }
}

// draws the menu texts, the selected one slides out a bit further
void drawMenuItems(byte amount, byte firstText)
{
  if (menuSelection == 2) sprites.drawOverwrite(98, 25, smallMask, 0);
  for (byte i = 0; i < amount; i++)
  {
    byte x = 128 - slideCounter;
    if (((2 + i) - menuSelection) == 0) x -= globalCounter;
    sprites.drawSelfMasked(x, 25 + (9 * i), menuText, firstText + i);
  }
}

// moves the selection up or down, lowest selection is 2
void menuMoveSelection(byte highest)
{
  if (arduboy.justPressed(DOWN_BUTTON) && (menuSelection < highest))
  {
    menuSelection++;
    globalCounter = 0;
  }
  if (arduboy.justPressed(UP_BUTTON) && (menuSelection > 2))
  {
    menuSelection--;
    globalCounter = 0;
  }
}

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(49, 20, T_arg, 0);
  if (globalCounter > 120)
  {
    globalCounter = 0;
    gameState = STATE_MENU_MAIN;
  }
}

void stateMenuMain()
{
  drawMenuPanel();
  drawMenuItems(4, 0);
  menuMoveSelection(5);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    setSlidersToZero();
    gameState = menuSelection;
    menuSelection = STATE_GAME_NEW - 10;
  }
  makeItSlide();
}

void stateMenuHelp()
{
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuPlay()
{
  drawMenuPanel();
  drawMenuItems(3, 7);
  menuMoveSelection(4);
  if (arduboy.justPressed(B_BUTTON))
  {
    setSlidersToZero();
    gameState = menuSelection + 10;
    gameType = gameState;
  }
  else if (arduboy.justPressed(A_BUTTON))
  {
    setSlidersToZero();
    gameState = STATE_MENU_MAIN;
  }
  makeItSlide();
}

void stateMenuInfo()
{
  drawBadge();
  sprites.drawSelfMasked(48, 33, madeBy00, 0);
  sprites.drawSelfMasked(22, 33, madeBy01, 0);
  sprites.drawSelfMasked(27, 47, madeBy02, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  drawMenuPanel();

  if (arduboy.justPressed(DOWN_BUTTON))
  {
    arduboy.audio.on();
    globalCounter = 0;
  }
  if (arduboy.justPressed(UP_BUTTON))
  {
    arduboy.audio.off();
    globalCounter = 0;
  }
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    setSlidersToZero();
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }

  // text 4 is the title, 5 is "on" and 6 is "off", the selected one slides out
  sprites.drawSelfMasked(128 - slideCounter, 25, menuText, 4);
  byte on = arduboy.audio.enabled();
  sprites.drawSelfMasked(128 - slideCounter - (on ? 0 : globalCounter), 34, menuText, 5);
  sprites.drawSelfMasked(128 - slideCounter - (on ? globalCounter : 0), 43, menuText, 6);
  makeItSlide();
}

#endif
