#ifndef ELEMENTS_H
#define ELEMENTS_H

// animation frame for all survivors
byte survivorFrame = 0;
boolean showHelp = true;
byte survivorType[SURVIVOR_MAX] = {0, 1, 2, 3, 4};

// swapSurvivorPool
// shuffles which survivor sprite is used by which survivor
void swapSurvivorPool()
{
  for (byte i = 0; i < SURVIVOR_MAX; i++)
  {
    byte k = random(SURVIVOR_MAX);
    byte temp = survivorType[i];
    survivorType[i] = survivorType[k];
    survivorType[k] = temp;
  }
}

// updateSurvivors
// updates the survivor animation (4 frames)
void updateSurvivors()
{
  if (arduboy.everyXFrames(10)) survivorFrame++;
  if (survivorFrame >= 4) survivorFrame = 0;
}

// drawSurvivors
// draws every active survivor in the list to the display
void drawSurvivors()
{
  if (arduboy.everyXFrames(30)) showHelp = !showHelp;
  for (byte id = 0; id < SURVIVOR_MAX; id++)
  {
    Element& surv = survivors[id];
    if (!surv.active) continue;
    drawMasked(surv.x - mapPositionX, surv.y - mapPositionY, survivorMask, survivorType[id], survivor, survivorFrame + (4 * survivorType[id]));
    if (showHelp) sprites.drawPlusMask(surv.x + 16 - mapPositionX, surv.y - 9 - mapPositionY, help_plus_mask, 0);
  }
}

// clearSurvivors
// clears the entire list of survivors
void clearSurvivors()
{
  for (byte id = 0; id < SURVIVOR_MAX; id++) survivors[id].active = false;
}

byte countAmountActiveSurvivors()
{
  byte countAmount = 0;
  for (byte id = 0; id < SURVIVOR_MAX; id++)
  {
    if (survivors[id].active) countAmount++;
  }
  return countAmount;
}

// drawAmountSurvivors
// shows the survivors left to find, or the exit timer when they are all found
void drawAmountSurvivors()
{
  byte amount = countAmountActiveSurvivors();
  for (byte i = 0; i < amount; i++)
  {
    sprites.drawPlusMask(40 + i * 9, 0, HUD_plus_mask, 2);
  }
  if (!amount)
  {
    if (showHelp)
    {
      sprites.drawPlusMask(45, 0, HUD_plus_mask, 3);
      sprites.drawPlusMask(54, 0, HUD_plus_mask, 4);
    }
    sprites.drawPlusMask(65, 0, HUD_plus_mask, 5);
    sprites.drawPlusMask(74, 0, HUD_plus_mask, 6);
    drawNumbers(68, 1, FONT_TINY, DATA_TIMER);
  }
}

// survivorCollide
// collects the survivors the player touches, opens the exit when all are found
void survivorCollide(int x, int y)
{
  for (byte id = 0; id < SURVIVOR_MAX; id++)
  {
    Element& surv = survivors[id];
    if (surv.active && boxHit(surv.x, surv.y, x, y, SPRITE_SIZE, SPRITE_SIZE))
    {
      surv.active = false;
      sfx(sfxRescue);
      rollingScore += 500;
      if (!countAmountActiveSurvivors()) exitDoor.active = true;
    }
  }
}

#endif
