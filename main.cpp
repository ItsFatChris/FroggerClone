#include <allegro.h>

void init();
void deinit();

struct sprite
{
       int xLoc;
       int yLoc;
       };
void moveCharacter(sprite &myS);
void drawCharacter(sprite &myS, BITMAP *b, BITMAP *buffer);

int main() {
	init();
	int lives = 5;
	int startX = 375;
	int startY = 550;
	
	BITMAP *playerSprite;
	playerSprite = load_bitmap("spriteSmall.bmp", NULL);
	
    BITMAP *buffer =NULL; //create buffer
    buffer = create_bitmap(800, 600);
    sprite player = {startX, startY};
    
    
	while (!key[KEY_ESC]) {
		rectfill(buffer, 0, 0, 800, 600, makecol(0,0,0));
		rectfill(buffer, 0, 550, 800, 600, makecol(255,0,255));
		moveCharacter(player);
		//drawCharacter(player, playerSprite, buffer);
		draw_sprite(buffer, playerSprite, player.xLoc, player.yLoc);
		
		
		
		
		
	blit(buffer, screen, 0,0,0,0,800,600);
	rest(100);
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void moveCharacter(sprite &myS)
{
     
      if (key[KEY_LEFT]) { 
          if(myS.xLoc > 0)
          {
          myS.xLoc -= 1; 
          }             
     }
        if (key[KEY_RIGHT]) { 
          if(myS.xLoc < 800)
          {
          myS.xLoc += 1; 
          }    
                        // textprintf(screen, font, 0, 10, WHITE, "XLocation: %i", myS.xOld);
     }
        if (key[KEY_DOWN]) { 
        if(myS.yLoc+49 < 600)
          {
          myS.yLoc += 50; 
          }  
            
          
                        // textprintf(screen, font, 0, 10, WHITE, "XLocation: %i", myS.xOld);
     }
        if (key[KEY_UP]) {
           if(myS.yLoc-49 > 0)
          {
          myS.yLoc -= 50; 
          }     
                        // textprintf(screen, font, 0, 10, WHITE, "XLocation: %i", myS.xOld);
     }
     };
     
void drawCharacter(sprite &myS, BITMAP *b, BITMAP *buffer)
{
     
     //draw the sprite
     draw_sprite(buffer, b, myS.xLoc, myS.yLoc*50);
     
     
     }

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
