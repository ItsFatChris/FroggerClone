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
void collision(vector<carSprite> &carArray, sprite &myS, int &score);

int main() {
	init();
	int lives = 5;
	int startX = 375;
	int startY = 550;
	
	BITMAP *playerSprite;
	playerSprite = load_bitmap("spriteSmallBlackBackground.bmp", NULL);
	
	BITMAP *car_spritesheet;
     BITMAP *cars[8][21];     
	//load the car bitmap
	car_spritesheet = load_bitmap("Car Wars Counters A 24jun2013____GTA_2.bmp", NULL);
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
    
    //create vectors of cars for the first row of cars
    vector<carSprite> firstRow;
    carSprite csp = {-100,500,rand() % 8,rand() % 21};
    firstRow.push_back(csp);
    carSprite csp1 = {200,500,rand() % 8,rand() % 21};
    firstRow.push_back(csp1);
    carSprite csp2 = {500,500,rand() % 8,rand() % 21};
    firstRow.push_back(csp2);
    carSprite csp3 = {800,500,rand() % 8,rand() % 21};
    firstRow.push_back(csp3);
    
    
     vector<carSprite> thirdRow;
    carSprite csp4 = {0,300,rand() % 8,rand() % 21};
    thirdRow.push_back(csp4);
    carSprite csp5 = {200,300,rand() % 8,rand() % 21};
    thirdRow.push_back(csp5);
    carSprite csp6 = {500,300,rand() % 8,rand() % 21};
    thirdRow.push_back(csp6);
    
    vector<carSprite> fifthRow;
    carSprite csp7 = {12,350,rand() % 8,rand() % 21};
    fifthRow.push_back(csp7);
    carSprite csp8 = {225,350,rand() % 8,rand() % 21};
    fifthRow.push_back(csp8);
    carSprite csp9 = {476,350,rand() % 8,rand() % 21};
    fifthRow.push_back(csp9);
    carSprite csp10 = {789,350,rand() % 8,rand() % 21};
    fifthRow.push_back(csp10);
	while (!key[KEY_ESC]) {
		rectfill(buffer, 0, 0, 800, 600, BLACK);
		rectfill(buffer, 0, 550, 800, 600, makecol(255,0,255));
		moveCharacter(player);
		drawCharacter(player, playerSprite, buffer);
		drawCars(firstRow, cars, buffer, 20);
		drawCars(thirdRow, cars, buffer, 10);
		drawCars(fifthRow, cars, buffer, 7);
		collision(firstRow, player, lives);
		collision(thirdRow, player, lives);
		collision(fifthRow, player, lives);
		
		
		
	      // write amount of lives on screen	
          textprintf(buffer, font, 0, 10, WHITE, "Lives %i", lives);
	
	      //copy the buffer to the screen
	      blit(buffer, screen, 0,0,0,0,800,600);
	      rest(75);
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

void collision(vector<carSprite> &carArray, sprite &myS, int &score)
{
     if(myS.yLoc == carArray.at(0).yLoc)
     {
                 for(int i = 0; i < carArray.size(); i++)
                 {
                         if(myS.xLoc > carArray.at(i).xLoc && myS.xLoc < carArray.at(i).xLoc +75)
                         {
                                 myS.xLoc = 375;
                                 myS.yLoc = 550;  
                                 score -=1;  
                                 return;
                         }
                 
                 
                 }
     
     
     
     }
}
void drawCars(vector<carSprite> &carArray, BITMAP *cars[][21], BITMAP *buf, int speed)
{
     
     for(int i = 0; i < carArray.size(); i++)
     {
             
             
             draw_sprite(buf, cars[carArray.at(i).carX][carArray.at(i).carY], carArray.at(i).xLoc, carArray[i].yLoc);
		     carArray.at(i).xLoc += speed;
		     
           if(carArray.at(i).xLoc > 900 && speed > 0)
             {carArray.at(i).xLoc = -100;}
     
             if(carArray.at(i).xLoc < -100 && speed < 0)
             {carArray.at(i).xLoc = 900;}
     
     
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
