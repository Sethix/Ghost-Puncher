#pragma once

#define WINDOW(a,b,c) sfw::initContext(a,b,c);
#define RUNNING sfw::stepContext()
#define INITIALIZE Game gs; \
srand(time(NULL));

#define PLAY gs.Run();
#define EXIT return 0;

#define FLAME_COUNT 8

#define SPLASH_TEXT "Press Start!"
#define MAINMENU_OPTION_ONE "Play"
#define MAINMENU_OPTION_TWO "Exit"
#define GAMEOVER_WIN_TEXT "You beat the high score! Play again?"
#define GAMEOVER_LOSE_TEXT "You lose! Try again?"
#define GAMEOVER_OPTION_ONE "Retry"
#define GAMEOVER_OPTION_TWO "Back"
#define GAMEOVER_OPTION_THREE "Exit"
#define EXIT_TEXT "Thanks for playing!"

#define TEXTURE_WIDTH(t) sfw::getTextureWidth(t)
#define TEXTURE_HEIGHT(t) sfw::getTextureHeight(t)

#define RENDER sfw::drawTexture

#define DRAW_TEXT(u,t,x,y,w,h,r,o,c) sfw::drawString(u,t,x,y,w,h,r,o,c);

#define BUTTON_ONE sfw::getGamepadPresent(0) && sfw::getGamepadButton(0,1) || sfw::getKey(81)
#define BUTTON_TWO sfw::getGamepadPresent(0) && sfw::getGamepadButton(0,2) || sfw::getKey(69)
#define BUTTON_THREE sfw::getGamepadPresent(0) && sfw::getGamepadButton(0,0) || sfw::getKey(82)
#define BUTTON_FOUR sfw::getGamepadPresent(0) && sfw::getGamepadButton(0,3) || sfw::getKey(70)
#define BUTTON_SELECT sfw::getGamepadPresent(0) && sfw::getGamepadButton(0,8) || sfw::getKey(258)
#define BUTTON_START sfw::getGamepadPresent(0) && sfw::getGamepadButton(0,9) || sfw::getKey(257)

#define BUTTON_LEFT sfw::getGamepadPresent(0) && sfw::getGamepadAxis(0,0) < -0.95f || sfw::getKey(65) && !sfw::getKey(68)
#define BUTTON_RIGHT sfw::getGamepadPresent(0) && sfw::getGamepadAxis(0,0) > 0.95f || sfw::getKey(68)
#define BUTTON_UP sfw::getGamepadPresent(0) && sfw::getGamepadAxis(0,1) < -0.95f || sfw::getKey(87) && !sfw::getKey(83)
#define BUTTON_DOWN sfw::getGamepadPresent(0) && sfw::getGamepadAxis(0,1) > 0.95f || sfw::getKey(83)
#define MOVEMENT_INACTIVE sfw::getGamepadPresent(0) && sfw::getGamepadAxis(0,1) == 0 || !sfw::getKey(65) && !sfw::getKey(68) && !sfw::getKey(65) && !sfw::getKey(87) && !sfw::getKey(83)