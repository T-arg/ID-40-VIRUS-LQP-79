#ifndef BULLET_H
#define BULLET_H

// the velocity of a bullet in each of the 8 directions (also used for the camera)
const char BulletXVelocities[8] = { 0, -2, -3, -2, 0, 2, 3, 2 };

// addBullet
// searches the bullet list for an empty slot, adds one if available
void addBullet(int x, int y, byte direction)
{
  for (byte id = 0; id < BULLET_MAX; id++)
  {
    Bullet& bull = bullets[id];
    if (!bull.active)
    {
      bull.x = x - BULLET_SIZE / 2;
      bull.y = y - BULLET_SIZE / 2;
      bull.vx = BulletXVelocities[direction];
      bull.vy = BulletXVelocities[(direction + 6) % 8];
      bull.active = true;
      sfx(sfxShot);
      break;
    }
  }
}

// updateBullets
// updates the entire list of bullets
void updateBullets()
{
  for (byte id = 0; id < BULLET_MAX; id++)
  {
    Bullet& obj = bullets[id];
    if (!obj.active) continue;

    obj.x += obj.vx;
    obj.y += obj.vy;

    // collide with zombies
    for (byte z = 0; z < ZOMBIE_MAX; z++)
    {
      if (zombieCollision(zombies[z], obj.x, obj.y, BULLET_SIZE, BULLET_SIZE))
      {
        obj.active = false;
        zombieHurt(zombies[z]);
        break;
      }
    }

    // collide with walls
    if (getTileType(obj.x / TILE_WIDTH, obj.y / TILE_HEIGHT) > 10) obj.active = false;

    // delete if gone off screen
    if ((obj.x < mapPositionX) || (obj.y < mapPositionY) || (obj.x > WIDTH + mapPositionX) || (obj.y > HEIGHT + mapPositionY))
    {
      obj.active = false;
    }
  }
}

// drawBullets
// draws the entire list of bullets
void drawBullets()
{
  for (byte id = 0; id < BULLET_MAX; id++)
  {
    Bullet& bull = bullets[id];
    if (!bull.active) continue;
    int x = bull.x - mapPositionX;
    int y = bull.y - mapPositionY;
    if ((x > 0) && (y > 0) && (x < WIDTH) && (y < HEIGHT))
    {
      sprites.drawSelfMasked(x, y, dotMask, 0);
    }
  }
}

#endif
