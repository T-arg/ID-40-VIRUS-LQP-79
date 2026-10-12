#ifndef DOOR_H
#define DOOR_H

#define EXIT_FACING_SOUTH       0
#define EXIT_FACING_WEST        1
#define EXIT_FACING_NORTH       2
#define EXIT_FACING_EAST        3

#define EXIT_ON_SOUTH_BORDER    0
#define EXIT_ON_WEST_BORDER     496
#define EXIT_ON_NORTH_BORDER    240

#define COMPASS_RADIUS          14                          // how far from the middle of the player the compass circles
#define COMPASS_DIAGONAL        10                          // and diagonally (14 / 1.4)

// the exit always sits on one of the borders of the level, that decides which way it faces
void setDoorPosition(int x, int y)
{
  exitDoor.x = x;
  exitDoor.y = y;
  if (y == EXIT_ON_SOUTH_BORDER) exitDoor.orientation = EXIT_FACING_SOUTH;
  else if (x == EXIT_ON_WEST_BORDER) exitDoor.orientation = EXIT_FACING_WEST;
  else if (y == EXIT_ON_NORTH_BORDER) exitDoor.orientation = EXIT_FACING_NORTH;
  else exitDoor.orientation = EXIT_FACING_EAST;
  exitDoor.active = false;
  exitDoor.counter = 255;
  exitDoor.loseLifeCounter = 255;
}

bool checkDoorCollision()
{
  return exitDoor.active && boxHit(exitDoor.x, exitDoor.y, coolGirl.x, coolGirl.y, SPRITE_SIZE, SPRITE_SIZE);
}

void drawDoor()
{
  int x = exitDoor.x - mapPositionX;
  int y = exitDoor.y - mapPositionY;
  if (exitDoor.active)
  {
    if ((!exitDoor.counter) && (exitDoor.loseLifeCounter > 0)) exitDoor.loseLifeCounter--;
    if (exitDoor.loseLifeCounter < 1)
    {
      playerHealthOffset(coolGirl, -1);
      exitDoor.loseLifeCounter = 255;
    }
    if (arduboy.everyXFrames(10))
    {
      exitDoor.frame++;
      if (exitDoor.counter > 0) exitDoor.counter--;
    }
    if (exitDoor.counter == 1) playerHealthOffset(coolGirl, -1);
    if (exitDoor.frame > 3) exitDoor.frame = 0;

    // the open door is made of four 8x8 pieces
    for (byte i = 0; i < 4; i++)
    {
      drawMasked(x + (i & 1) * 8, y + (i >> 1) * 8, exitOpenMask, 0, exitOpen, exitDoor.frame + 4 * exitDoor.orientation);
    }
  }
  else drawMasked(x, y, exitClosedMask, 0, exitClosed, exitDoor.orientation);
}

// the compass arrows, 5x5 pixels, one per direction: frame = (up/down + 1) * 3 + (left/right + 1)
const unsigned char PROGMEM compassArrow[] = {
  5, 5,
  0x07, 0x03, 0x05, 0x08, 0x10,   // NW
  0x04, 0x02, 0x1F, 0x02, 0x04,   // N
  0x10, 0x08, 0x05, 0x03, 0x07,   // NE
  0x04, 0x0E, 0x1F, 0x04, 0x04,   // W
  0x00, 0x00, 0x00, 0x00, 0x00,   // (the middle, never drawn)
  0x04, 0x04, 0x1F, 0x0E, 0x04,   // E
  0x1C, 0x18, 0x14, 0x02, 0x01,   // SW
  0x04, 0x08, 0x1F, 0x08, 0x04,   // S
  0x01, 0x02, 0x14, 0x18, 0x1C,   // SE
};

// drawCompass
// while the exit is open, a small arrow circles the player and points at the door (8 directions)
void drawCompass()
{
  if (!exitDoor.active) return;
  int dx = exitDoor.x - coolGirl.x;
  int dy = exitDoor.y - coolGirl.y;
  int ax = abs(dx);
  int ay = abs(dy);
  char hx = 0;                                              // -1, 0 or 1: the direction, left/right
  char hy = 0;                                              // and up/down
  if (ay * 2 < ax) hx = (dx < 0) ? -1 : 1;                  // mostly sideways
  else if (ax * 2 < ay) hy = (dy < 0) ? -1 : 1;             // mostly up or down
  else
  {
    hx = (dx < 0) ? -1 : 1;
    hy = (dy < 0) ? -1 : 1;
  }
  byte r = (hx && hy) ? COMPASS_DIAGONAL : COMPASS_RADIUS;
  sprites.drawSelfMasked(coolGirl.x - mapPositionX + 6 + hx * r, coolGirl.y - mapPositionY + 6 + hy * r, compassArrow, (hy + 1) * 3 + hx + 1);
}

#endif
