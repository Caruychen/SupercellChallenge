#pragma once

const int ScreenWidth = 1200;
const int ScreenHeight = 675;
const int FramerateLimit = 60;

const float Gravity = 18000.0f;
const float JumpYVelocity = -230.0f;

const float PlayerHeight = 60.0f;
const float PlayerWidth = 40.0f;
const float PlayerSpeed = 155.0f;
const float PlayerJumpTime = 0.7f;

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
