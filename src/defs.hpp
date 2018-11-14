#ifndef __DEFS_HPP__
#define __DEFS_HPP__

static const int ROOM_MAX_SIZE{12};
static const int ROOM_MIN_SIZE{6};
static const int MAX_ROOM_MONSTERS{3};
static const int MAX_NAME_LENGTH{260};

// How many turns the monster chases the player after losing sight of them
static const int TRACKING_TURNS{3};

static const int PANEL_HEIGHT{7};
static const int BAR_WIDTH{20};
static const int MSG_X{BAR_WIDTH + 2};
static const int MSG_HEIGHT{PANEL_HEIGHT - 1};

#endif
