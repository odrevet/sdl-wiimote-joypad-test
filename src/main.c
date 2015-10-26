/**
   @file   main.c
   @note  Published under the GPL 3 license (see license.txt for more info)
*/

//standard includes
#include <stdlib.h>

#include "fontmap.h"		//for display purpose

#ifndef GEKKO
#include <stdbool.h>
#else
//Wii includes
#include <gccore.h>
#include <fat.h>
#endif

//SDL includes
#include <SDL/SDL.h>

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH  640

/*
  define an array of pointer of joysticks,
  for games with one player,
  use just a SDL_Joystick*
  SDL_NumJoysticks and a malloc is also a good alternative for variable number of joysticks at runtime (not usual thougth)
*/
#define JOYNUMS 4
SDL_Joystick* joysticks[JOYNUMS];

int p1_x = 0;
int p1_y = 0;

int main(int argc,
	 char** argv)
{
#ifdef GEKKO
  fatInitDefault();
#endif

  srand(time(NULL));

  // SDL_INIT_JOYSTICK must be passed to the init function
  if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0 )
    {
      fprintf(stderr,
	      "Unable to init SDL: %s\n",
	      SDL_GetError() );
      exit(EXIT_FAILURE);
    }


  fontmap_init();

  //Open all joysticks
  for(int i=0;i<JOYNUMS;i++){
    joysticks[i] = SDL_JoystickOpen(i);
  }

  SDL_WM_SetCaption("joytest",
		    NULL);

  atexit(SDL_Quit);
  SDL_ShowCursor(SDL_DISABLE);

  // create a new window
  SDL_Surface *screen=NULL;
  screen = SDL_SetVideoMode(WINDOW_WIDTH,
			    WINDOW_HEIGHT,
			    16,
			    SDL_HWSURFACE);
  if (!screen){
    fprintf(stderr,
	    "Unable to set video: %s\n",
	    SDL_GetError());
    exit(EXIT_FAILURE);
  }

  state_in_game(screen);

  //Close all joysticks
  for(int i=0;i<JOYNUMS;i++){
    SDL_JoystickClose(i);
  }

  SDL_Quit();
  return EXIT_SUCCESS;
}

void state_in_game(SDL_Surface *screen)
{
  bool done=false;
  int i = 0;
  int offset_x = 25;
  int offset_y = 8;

  int jaxis_value=0;
  int jaxis_axis=0;
  int jaxis_which=0;

  int x_move=0;
  int y_move=0;

  while (!done)
    {
      SDL_FillRect(screen,
		   0,
		   SDL_MapRGB(screen->format,
			      35,
			      75,
			      0));

      //joysticks properties can be fetched
      for(i=0;i<JOYNUMS;i++){
	fontmap_printf(i * (FONTMAP_SIZE * offset_x),
		       0,
		       screen,
		       "JOYPAD %d\nHAS %d AXES \nAND %d BUTTONS \nAND %d BALLS \nAND %d HATS ",
		       i,
		       SDL_JoystickNumAxes(joysticks[i]),
		       SDL_JoystickNumButtons(joysticks[i]),
		       SDL_JoystickNumBalls(joysticks[i]),
		       SDL_JoystickNumHats(joysticks[i]));
      }

      SDL_JoystickUpdate();						//Update jotsticks status each loop
      SDL_Event event;
      while (SDL_PollEvent(&event)){

	if(event.type ==  SDL_QUIT){
	  exit(EXIT_SUCCESS);
	}


	// Check button status is almost like handling keyboard events,
	//use SDL_JOYBUTTONDOWN and SDL_JOYBUTTONUP

	switch ( event.type )
	  {
	  case SDL_JOYBUTTONDOWN:
	    switch(event.jbutton.button)
	      {
	      case 0:					//A
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"A DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 1:					//B
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"B DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 2:					//1
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"1 DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 3:					//2
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"2 DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 4:					//-
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"MINUS DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 5:					//+
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"PLUS DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 6:					//HOME
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"HOME DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 7:					//Z
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"Z DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 8:					//C
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"C DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 9:					//a
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"A DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 10:				//b
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"B DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 11:				//x
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"X DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 12:				//y
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"Y DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 13:				//l
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"1 DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 14:				//r
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"L DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 15:				//zl
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"R DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 16:				//zr
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"ZR DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 17:				//-
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"MINUS DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 18:				//+
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"PLUS DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 19:				//HOME
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"HOME DOWN AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      default:
		break;
	      }
	    break;
	  case SDL_JOYBUTTONUP:
	    switch(event.jbutton.button)
	      {
	      case 0:					//A
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"A UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 1:					//B
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"B UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 2:					//1
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"1 UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 3:					//2
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"2 UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 4:					//-
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"MINUS UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 5:					//+
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"PLUS UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 6:					//HOME
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"HOME UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 7:					//Z
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"Z UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 8:					//C
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"C UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 9:					//a
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"A UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 10:				//b
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"B UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 11:				//x
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"X UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 12:				//y
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"Y UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 13:				//l
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"1 UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 14:				//r
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"L UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 15:				//zl
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"R UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 16:				//zr
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"ZR UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 17:				//-
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"MINUS UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 18:				//+
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"PLUS UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      case 19:				//HOME
		fontmap_printf( event.jbutton.which * (FONTMAP_SIZE * offset_x),
				FONTMAP_SIZE * (event.jbutton.button + offset_y),
				screen,
				"HOME UP AND %s",
				(event.jbutton.state == SDL_PRESSED ? "PRESSED": "RELEASED"));
		break;
	      default:
		break;
	      }
	    break;

	    //An axis motion
	  case SDL_JOYAXISMOTION:
	    if ( ( event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) ) {
	      jaxis_which = event.jaxis.which;
	      jaxis_axis = event.jaxis.axis;
	      jaxis_value = event.jaxis.value;

	      if( event.jaxis.axis == 0)
		{
		  /* Left and right movement (according to jaxis_value) of the nunchuck stick or left analogic stick of the classic pad*/
		}

	      if( event.jaxis.axis == 1)
		{
		  /* Up and Down movement (according to jaxis_value) of the nunchuck stick or left analogic stick of the classic pad */
		}


	    }
	    break;

	  }

	//Infra Red is mapped as a mouse
	if( event.type == SDL_MOUSEMOTION ) {
	  p1_x = event.motion.x;
	  p1_y = event.motion.y;
	}

      }	//end of pool event

      fontmap_printf( jaxis_which * (FONTMAP_SIZE * offset_x),
		      FONTMAP_SIZE * (SDL_JoystickNumButtons(joysticks[jaxis_which]) + offset_y),
		      screen,
		      "IR X %d IR Y %d",
		      p1_x,
		      p1_y);
      fontmap_printf( jaxis_which * (FONTMAP_SIZE * offset_x),
		      FONTMAP_SIZE * (SDL_JoystickNumButtons(joysticks[jaxis_which]) + offset_y + 1),
		      screen,
		      "JOYAXISMOTION OF PAD %d\nAXIS %d\nVALUE %.4d",
		      jaxis_which,
		      jaxis_axis,
		      jaxis_value);

      // The hat report the Directional PAD status
      for(int joy_number=0;joy_number<JOYNUMS;joy_number++){
	int hat_number = SDL_JoystickNumHats(joysticks[joy_number]);
	for(int curhat=0;curhat<hat_number;curhat++){
	  int joystate = SDL_JoystickGetHat(joysticks[joy_number],
					    curhat);
	  switch (joystate){
	  case SDL_HAT_CENTERED:
	    fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			    offset_y  * FONTMAP_SIZE,
			    screen,
			    "HAT %d CENTERED",
			    curhat);
	    break;

	  case SDL_HAT_UP:
	    fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			    offset_y  * FONTMAP_SIZE,
			    screen,
			    "HAT %d UP",
			    curhat);
	    break;

	  case SDL_HAT_RIGHT:
	    fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			    offset_y  * FONTMAP_SIZE,
			    screen,
			    "HAT %d RIGHT",
			    curhat);
	    break;

	  case SDL_HAT_DOWN:
	    fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			    offset_y  * FONTMAP_SIZE,
			    screen,
			    "HAT %d DOWN",
			    curhat);
	    break;

	  case SDL_HAT_LEFT:
	    fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			    offset_y  * FONTMAP_SIZE,
			    screen,
			    "HAT %d LEFT",
			    curhat);
	    break;

	  case SDL_HAT_RIGHTUP:
	    fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			    offset_y  * FONTMAP_SIZE,
			    screen,
			    "HAT %d RIGHTUP",
			    curhat);
	    break;

	  case SDL_HAT_RIGHTDOWN:
	    fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			    offset_y  * FONTMAP_SIZE,
			    screen,
			    "HAT %d RIGHTDOWN",
			    curhat);
	    break;

	  case SDL_HAT_LEFTUP:
	    fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			    offset_y  * FONTMAP_SIZE,
			    screen,
			    "HAT %d LEFTUP",
			    curhat);
	    break;

	  case SDL_HAT_LEFTDOWN:
	    fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			    offset_y  * FONTMAP_SIZE,
			    screen,
			    "HAT %d LEFTDOWN",
			    curhat);
	    break;
	  }
	}

	//Axis events can be fetched with a get axis function
	x_move=SDL_JoystickGetAxis(joysticks[joy_number],
				   0);
	y_move=SDL_JoystickGetAxis(joysticks[joy_number],
				   1);

	fontmap_printf( joy_number * (FONTMAP_SIZE * offset_x),
			FONTMAP_SIZE * (SDL_JoystickNumButtons(joysticks[joy_number])+ offset_y + 5),
			screen,
			"JOYSTICKGETAXIS\nX MOVE %d Y MOVE %d",
			x_move,
			y_move);

      }

      SDL_Flip(screen);
    }
}
