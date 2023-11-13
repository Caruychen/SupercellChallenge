#pragma once

const int ScreenWidth = 1200;
const int ScreenHeight = 675;
const int FramerateLimit = 60;

const float Gravity = 18000.0f;


const float PlayerHeight = 30.0f;
const float PlayerWidth = 20.0f;
const float PlayerAcceleration = 60000;
const float PlayerDashVelocityX = 1250;
const float PlayerDashVelocityY = 1000;
const float PlayerJumpVelocity = 500;
const float PlayerMaxVelocityX = 350;
const float PlayerMaxVelocityY = 750;
const float PlayerMaxAccelerationX = 5000;
const float PlayerMaxAccelerationY = 2000;


const float CoinRadius = 17.0f;


const float TileSize = 25;

enum class eTile
{
	eEmpty			= 0,
	eBlock			= 1,
	eHazard			= 2,
    eDoor           = 3,
	ePlayerSpawn	= 4,
    eCoin           = 5,
    eMax
};
