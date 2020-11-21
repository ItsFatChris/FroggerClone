#include <allegro.h>
#include <iterator>
#include <vector>
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
void init();
void deinit();
using namespace std;
struct sprite
{
       int xLoc;
       int yLoc;
       };
       
struct carSprite
{
       int xLoc;
       int yLoc;
       int carX;
       int carY;
       };
void moveCharacter(sprite &myS);
void drawCharacter(sprite &myS, BITMAP *b, BITMAP *buffer);
void drawCars(vector<carSprite> &carArray, BITMAP *cars[][21], BITMAP *buf, int speed);

int main() {
	init();
	int lives = 5;
	int startX = 375;
	int startY = 550;
	
	BITMAP *playerSprite;
	playerSprite = load_bitmap("spriteSmall.bmp", NULL);
	
	BITMAP *car_spritesheet;
     BITMAP *cars[8][21];     
	//load the car bitmap
	car_spritesheet = load_bitmap("Car Wars Counters A 24jun2013____GTA_1.bmp", NULL);
	//placeholder to blit the cars into
	BITMAP *placeholder;
	placeholder = create_bitmap(100, 50);
	
    BITMAP *buffer =NULL; //create buffer
    buffer = create_bitmap(800, 600);
    sprite player = {startX, startY};
    
    //split spritesheet into the array
    for(int x=0; x<8; x++)
	{
	         for(int y=0; y<21; y++)
	         {        
                      //needs a bitmap to copy to, so load a blank placeholder bitmap
                      cars[x][y] = load_bitmap("placeholder.bmp", NULL); //put the location of your file here
                      blit(car_spritesheet, //bitmap source
                      cars[x][y],           // bitmap destination
                      x*128 +14, y*64+7,              // source  x and y
                      0,0,                   // destination xand y
                      100, 50);              // width and height
                      
                      }
	
	
	
    }
    
    vector<carSprite> firstRow;
    carSprite csp = {0,0,0,0};
    firstRow.push_back(csp);
    //firstRow.push_back({100, 500, 7 ,1});
     
    
	while (!key[KEY_ESC]) {
		rectfill(buffer, 0, 0, 800, 600, BLACK);
		rectfill(buffer, 0, 550, 800, 600, makecol(255,0,255));
		moveCharacter(player);
		drawCharacter(player, playerSprite, buffer);
		drawCars(firstRow, cars, buffer, 20);
		
		
		
		
	      // write amount of lives on screen	
          //textprintf(buffer, font, 0, 10, WHITE, "Lives %i", lives);
	
	      //copy the buffer to the screen
	      blit(buffer, screen, 0,0,0,0,800,600);
	      rest(50);
	}


     //destroy bitmaps in memory
    destroy_bitmap(car_spritesheet);
    destroy_bitmap(playerSprite);
    destroy_bitmap(buffer);
   for(int x=0; x<8; x++)
	{
	         for(int y=0; y<21; y++)
	         {
                      destroy_bitmap(cars[x][y] );
                      
                      }
	
	
	
    }

	deinit();
	return 0;
}
END_OF_MAIN()
void drawCars(vector<carSprite> &carArray, BITMAP *cars[][21], BITMAP *buf, int speed)
{
     
     for(int i = 0; i < carArray.size(); i++)
     {
             
             
             draw_sprite(buf, cars[carArray.at(i).carX][carArray.at(i).carY], carArray.at(i).xLoc, carArray[i].yLoc);
		     carArray.at(i).xLoc += 20;
		     
           if(carArray.at(i).xLoc > 800 && speed > 0)
             {carArray.at(i).xLoc = 0;}
     
             if(carArray.at(i).xLoc < 0 && speed < 0)
             {carArray.at(i).xLoc = 800;}
     
     
             }
     
     
     }
void moveCharacter(sprite &myS)
{
     
      if (key[KEY_LEFT]) { 
          if(myS.xLoc > 0)
          {
          myS.xLoc -= 20; 
          }             
     }
        if (key[KEY_RIGHT]) { 
          if(myS.xLoc+50 < 800)
          {
          myS.xLoc += 20; 
          }    
                        // textprintf(screen, font, 0, 10, WHITE, "XLocation: %i", myS.xOld);
     }
        if (key[KEY_DOWN]) { 
        if(myS.yLoc+50 < 600)
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
     draw_sprite(buffer, b, myS.xLoc, myS.yLoc);
     
     
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
