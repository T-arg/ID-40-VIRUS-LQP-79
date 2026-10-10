#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>
#include "ATMconfig.h"
#include <ATMlib.h>

// constants /////////////////////////////////////////////////////////////////

#define OFFSET_VLQP_START        (EEPROM_STORAGE_SPACE_START + 64)

//define menu states (on main menu)
#define STATE_MENU_INTRO         0
#define STATE_MENU_MAIN          1
#define STATE_MENU_HELP          2
#define STATE_MENU_PLAY          3
#define STATE_MENU_INFO          4
#define STATE_MENU_SOUNDFX       5

//define game states
#define STATE_GAME_PREPARE_LEVEL 6
#define STATE_GAME_NEXT_LEVEL    7
#define STATE_GAME_PLAYING       8
#define STATE_GAME_OVER          9
#define STATE_GAME_PAUSE         10
#define STATE_GAME_END           11
#define STATE_GAME_NEW           12
#define STATE_GAME_CONTINUE      13
#define STATE_GAME_MAYHEM        14

#define LEVEL_WIDTH              512
#define LEVEL_HEIGHT             256
#define TILE_WIDTH               8
#define TILE_HEIGHT              8

#define NUM_MAPS                 32
#define LEVEL_TO_START_WITH      1               // normal game starts with level 1
#define TOTAL_LEVEL_AMOUNT       (NUM_MAPS * 4)

#define FONT_TINY                0
#define FONT_SMALL               1
#define FONT_BIG                 2

#define DATA_TIMER               0
#define DATA_SCORE               1
#define DATA_LEVEL               2

// everything in the game that moves is 16x16 pixels
#define SPRITE_SIZE              16

#define PLAYER_FACING_SOUTH      0
#define PLAYER_FLASH_TIME        60
#define PLAYER_MAXHEALTH         8
#define PLAYER_START_HEALTH      5
#define WEAPON_OVERHEAT          35

#define BULLET_MAX               6
#define BULLET_SIZE              2

#define ZOMBIE_MAX               24
#define ZOMBIE_FLASH_TIME        5
#define ENEMY_FACING_WEST        0
#define ENEMY_FACING_EAST        1

#define SURVIVOR_MAX             5
#define PICKUP_MAX               3
#define PICKUP_TYPE_INACTIVE     0
#define PICKUP_TYPE_COIN         1
#define PICKUP_TYPE_HEART        2

typedef void (*FunctionPointer) ();

// structures ////////////////////////////////////////////////////////////////

struct Bullet
{
  int x;
  int y;
  char vx;
  char vy;
  byte active;
};

struct Door
{
  int x;
  int y;
  byte active;
  byte orientation;
  byte frame;
  byte counter;
  byte loseLifeCounter;
};

struct Element
{
  int x;
  int y;
  byte active;
};

struct Enemy
{
  int x;
  int y;
  byte frame;
  byte direction;
  byte health;
  byte active;
  byte flashTime;
  byte type;
};

struct Pickup
{
  int x;
  int y;
  byte type;
  byte frame;
  byte counter;
  boolean isVisible;
};

struct Player
{
  boolean walking;
  byte direction;
  byte frame;
  byte shotDelay;
  int x;
  int y;
  byte health;
  byte flashTime;
  byte camDirection;
  boolean coolDownVisible;
  boolean overHeated;
  byte coolDownCounter;
};

// the saved game, same layout in the EEPROM as before
struct __attribute__((packed)) SaveData
{
  byte idStart;
  int level;
  unsigned long score;
  byte health;
  byte idEnd;
};

// globals ///////////////////////////////////////////////////////////////////

Arduboy2Base arduboy;
Sprites sprites;
ATMsynth ATM;

byte gameID;
byte gameState = STATE_MENU_INTRO;
byte gameType = STATE_GAME_NEW;
byte globalCounter = 0;
unsigned long scorePlayer;
int rollingScore = 0;
int level;
int displayLevel;
int mapPositionX;
int mapPositionY;

Player coolGirl;
Door exitDoor;
Bullet bullets[BULLET_MAX];
Enemy zombies[ZOMBIE_MAX];
Element survivors[SURVIVOR_MAX];
Pickup pickups[PICKUP_MAX];
byte pickupsCounter;

// function prototypes ///////////////////////////////////////////////////////
// (every header is part of one sketch, so they can all call each other)

// level.h
byte read6(const unsigned char *data, unsigned int i);
unsigned char getTileType(unsigned int posX, unsigned int posY);
void drawLevel();
void drawNumbers(byte numbersX, byte numbersY, byte fontType, byte dataType);
void mapCollide(int& x, int& y, bool horizontal, char& vel);

// bullet.h
void addBullet(int x, int y, byte direction);
void updateBullets();
void drawBullets();

// enemies.h
void spawnZombie();
void updateZombies();
void drawZombies();
void zombieHurt(Enemy& obj);
bool zombieCollision(Enemy& obj, int x, int y, byte w, byte h);
void clearZombies();
void zombieCollide(int& x, int& y, bool horizontal, char& vel);

// elements.h
void swapSurvivorPool();
void updateSurvivors();
void drawSurvivors();
void clearSurvivors();
byte countAmountActiveSurvivors();
void drawAmountSurvivors();
void survivorCollide(int x, int y);

// door.h
void setDoorPosition(int x, int y);
void drawDoor();
bool checkDoorCollision();

// pickup.h
void addPickup(int x, int y);
void drawPickups();
void clearPickups();
void pickupCollision(int x, int y);

// player.h
void updatePlayer(Player& obj);
void drawPlayer(Player& obj);
void playerHealthOffset(Player& obj, char amount);
void initializePlayer(Player& obj);
void drawLife(Player& obj);
void drawCoolDown();

// menu.h
void stateMenuIntro();
void stateMenuMain();
void stateMenuHelp();
void stateMenuPlay();
void stateMenuInfo();
void stateMenuSoundfx();

// game.h
void stateGamePrepareLevel();
void stateGameNextLevel();
void stateGamePlaying();
void stateGameOver();
void stateGamePause();
void stateGameEnd();
void stateGameNew();
void stateGameContinue();
void stateGameMayhem();

// helpers ///////////////////////////////////////////////////////////////////

// true if the 16x16 box at (ax, ay) overlaps the box at (bx, by) of size w x h
bool boxHit(int ax, int ay, int bx, int by, byte w, byte h)
{
  return (ax < bx + w) && (ax + SPRITE_SIZE > bx) && (ay < by + h) && (ay + SPRITE_SIZE > by);
}

// draws a sprite: erases its outline with the mask first, then draws the image
void drawMasked(int x, int y, const unsigned char *mask, byte maskFrame, const unsigned char *image, byte frame)
{
  sprites.drawErase(x, y, mask, maskFrame);
  sprites.drawSelfMasked(x, y, image, frame);
}

// drawFlipped
// draws a 16x16 image and its mask mirrored left to right (column c comes from column k - c). Sprites can't
// mirror, so this erases with the mirrored mask and ORs the mirrored image straight into the screen buffer.
// img and mask point at the first byte of the frame, k is the last used column (15, or 14 for the zombies)
void drawFlipped(int x, int y, const unsigned char *img, const unsigned char *mask, byte k)
{
  byte *buf = arduboy.getBuffer();
  byte shift = y & 7;
  for (byte c = 0; c <= k; c++)
  {
    int sx = x + c;
    if (sx < 0 || sx > 127) continue;
    for (byte p = 0; p < 2; p++)
    {
      byte i = (p << 4) + k - c;
      unsigned int im = (unsigned int)pgm_read_byte(img + i) << shift;
      unsigned int mk = (unsigned int)pgm_read_byte(mask + i) << shift;
      for (byte h = 0; h < 2; h++)
      {
        int page = (y >> 3) + p + h;
        if (page < 0 || page > 7) continue;
        byte *s = buf + page * 128 + sx;
        *s = (*s & ~(byte)(mk >> (h << 3))) | (byte)(im >> (h << 3));
      }
    }
  }
}

// burp
// moves start toward goal; step is given in 4.4 fixed point
short burp(short start, short goal, unsigned char step)
{
  short a = goal;
  short b = start;
  char sign = 0;

  if (start > goal)
  {
    a = start;
    b = goal;
    sign = -1;
  }
  else if (start < goal)
  {
    sign = 1;
  }

  start += sign * (1 + ((a - b) * step) / 16);
  if (a < b) return goal;

  return start;
}

#endif
