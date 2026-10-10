#ifndef ENEMIES_H
#define ENEMIES_H

// spawnZombie
// adds a zombie in a random place in the map, as long as it is not close to the player
void spawnZombie()
{
  int x = random(16, LEVEL_WIDTH - SPRITE_SIZE - 16);
  int y = random(16, LEVEL_HEIGHT - SPRITE_SIZE - 16);

  if ((x < coolGirl.x - WIDTH) || (x > coolGirl.x + WIDTH) || (y < coolGirl.y - HEIGHT) || (y > coolGirl.y + HEIGHT))
  {
    // use the first free slot
    for (byte id = 0; id < ZOMBIE_MAX; id++)
    {
      Enemy& obj = zombies[id];
      if (!obj.active)
      {
        obj.frame = 0;
        obj.active = true;
        obj.direction = ENEMY_FACING_WEST;
        obj.x = x;
        obj.y = y;
        obj.type = random(3);
        obj.health = obj.type ? 2 : 3;
        obj.flashTime = 0;
        return;
      }
    }
  }
}

// moves a zombie one step along one axis: collides with other zombies, the player and the walls
void zombieMove(Enemy& obj, bool horizontal, char& vel)
{
  int& pos = horizontal ? obj.x : obj.y;
  pos += vel;

  zombieCollide(obj.x, obj.y, horizontal, vel);

  // collide with player
  if (zombieCollision(obj, coolGirl.x, coolGirl.y, SPRITE_SIZE, SPRITE_SIZE))
  {
    int playerPos = horizontal ? coolGirl.x : coolGirl.y;
    if (vel > 0) pos = playerPos - SPRITE_SIZE;
    else if (vel < 0) pos = playerPos + SPRITE_SIZE;

    playerHealthOffset(coolGirl, -1);
    vel = 0;
  }

  mapCollide(obj.x, obj.y, horizontal, vel);
}

// updateZombies
// moves every active zombie toward the player, zombies are "removed" (set inactive) when health reaches zero
void updateZombies()
{
  for (byte id = 0; id < ZOMBIE_MAX; id++)
  {
    Enemy& obj = zombies[id];
    if (!obj.active) continue;

    if (arduboy.everyXFrames(3))
    {
      // chase player
      char vx = 0;
      char vy = 0;
      if (obj.x < coolGirl.x) vx = 1;
      if (obj.x > coolGirl.x) vx = -1;
      if (obj.y < coolGirl.y) vy = 1;
      if (obj.y > coolGirl.y) vy = -1;

      // if out of bounds, delete this
      if ((obj.x < 0) || (obj.y < 0) || (obj.x >= LEVEL_WIDTH) || (obj.y >= LEVEL_HEIGHT))
      {
        obj.active = false;
        continue;
      }

      // update orientation
      if (vx < 0) obj.direction = ENEMY_FACING_WEST;
      else if (vx > 0) obj.direction = ENEMY_FACING_EAST;

      zombieMove(obj, true, vx);
      zombieMove(obj, false, vy);

      // animation
      if (vx || vy)
      {
        if (arduboy.everyXFrames(2)) obj.frame++;
        if (obj.frame >= 8) obj.frame = 0;
      }
      else obj.frame = 0;
    }

    if (obj.health == 0) obj.active = false;
  }
}

// drawZombies
// draws every zombie in the list
void drawZombies()
{
  for (byte id = 0; id < ZOMBIE_MAX; id++)
  {
    Enemy& obj = zombies[id];
    if (obj.active)
    {
      if (obj.flashTime > 0) obj.flashTime--;
      if ((obj.flashTime % 4) < 2)
      {
        int drawX = obj.x - mapPositionX;
        int drawY = obj.y - mapPositionY;
        if (obj.type) drawMasked(drawX, drawY, enemyZombieMask, obj.direction, enemyZombie, obj.frame + 8 * obj.direction);
        else drawMasked(drawX, drawY, zombieTwoMask, obj.direction, zombieTwo, (obj.frame % 2) + 2 * obj.direction);
      }
    }
    else if (obj.flashTime > 0)
    {
      // death effect
      obj.flashTime--;
      arduboy.drawCircle(obj.x - mapPositionX + SPRITE_SIZE / 2, obj.y - mapPositionY + SPRITE_SIZE / 2, 12 - obj.flashTime * 2, 1);
    }
  }
}

// zombieHurt
// a bullet hit the zombie: takes one health, kills the zombie if there is none left
void zombieHurt(Enemy& obj)
{
  obj.health--;
  obj.flashTime = ZOMBIE_FLASH_TIME;
  if (obj.health == 0)
  {
    sfx(sfxDie);
    obj.active = false;
    rollingScore += 100;
    addPickup(obj.x + 4, obj.y + 4);
  }
  else sfx(sfxHit);
}

// zombieCollision
// returns true if the zombie overlaps the box at (x, y) of size w x h
bool zombieCollision(Enemy& obj, int x, int y, byte w, byte h)
{
  return obj.active && boxHit(obj.x, obj.y, x, y, w, h);
}

// clearZombies
// clears the entire list of zombies
void clearZombies()
{
  for (byte id = 0; id < ZOMBIE_MAX; id++) zombies[id].active = false;
}

// zombieCollide
// pushes the 16x16 object at (x, y) out of any zombie it overlaps
void zombieCollide(int& x, int& y, bool horizontal, char& vel)
{
  int& pos = horizontal ? x : y;
  for (byte id = 0; id < ZOMBIE_MAX; id++)
  {
    Enemy& obj = zombies[id];
    if (zombieCollision(obj, x, y, SPRITE_SIZE, SPRITE_SIZE))
    {
      if (x == obj.x && y == obj.y) continue;
      int zombiePos = horizontal ? obj.x : obj.y;
      if (vel > 0) pos = zombiePos - SPRITE_SIZE;
      else if (vel < 0) pos = zombiePos + SPRITE_SIZE;
      vel = 0;
    }
  }
}

#endif
