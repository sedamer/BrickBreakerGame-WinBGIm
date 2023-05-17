#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string.h>

#define BALL_RADIUS 8
#define PADDLE_WIDTH 80
#define PADDLE_HEIGHT 10
#define BRICK_WIDTH 50
#define BRICK_HEIGHT 20
#define Ball_speed 2
#define paddleSpeed 20


bool gameOver=false;
int score =0;
int lives=3;
	void drawMenu() { // giri� ekran� �izdirme
	    cleardevice();
	    settextstyle(EUROPEAN_FONT, HORIZ_DIR  , 1);
	    setcolor(CYAN);
	    outtextxy(getmaxx() / 4 - 30, getmaxy() / 2 - 140,"BRICK BREAKER GAME");
	    settextstyle(EUROPEAN_FONT, HORIZ_DIR  , 1);
	    setcolor(LIGHTMAGENTA);
	    outtextxy(getmaxx() / 2 - 160, getmaxy() / 2 - 60,"1.Press Enter to Start the game <3");
	    outtextxy(getmaxx() / 2 - 160, getmaxy() / 2 - 40,"2.Press Esc to Quit the game :(");
	    outtextxy(getmaxx() / 2 - 160, getmaxy() / 2 - 20,"3.Press i to Instructions.");
	    outtextxy(getmaxx() / 2 - 160, getmaxy() / 2 - 0,"4.Press k to back here :)");


	}
	
	void drawInstructions() { // i ye bast�g�nda Talimatlar b�l�m� a��l�r. Instruction k�sm�
	    cleardevice();
	    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
		setcolor(CYAN);
	    outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 - 100, "Instructions:");
	    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
		setcolor(LIGHTMAGENTA);
	    outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 - 70, 	"1.Break all the bricks or you lose a life.");
	    outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 - 50, 	"2.Use the left and right arrow keys to move the paddle.");
	    outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 - 30, 	"3.Press Enter to Start the game <3");
	    outtextxy(getmaxx() / 2 - 300, getmaxy() / 2 - 10 , "4.Press Esc to Quit the game :(");
	}

	
void IncreaseScore(int& score) { // Score u 100 artt�rma
    score += 100;
}
void decreaseLives(int &lives){ //L�ves i 1 azaltma
	lives--;
}
	int main(){
		int gd = DETECT, gm;
	    initgraph(&gd, &gm, "");
	
	    int NUM_BRICKS=63;  //brick say�s� 63 tane
    	 drawMenu(); //giri� men�s�n� ekrana �izdirmek i�in.

    while (true) {
        if (kbhit()) {
            int key = getch();
            if (key == 13) { // Enter key e bas�ld��� zaman oyun ba�lar.
                break; // Start the game
            }
            else if (key == 27) { // Esc key e bas�ld��� zaman oyun biter ve kapan�r.
                closegraph();
                return 0; // Quit the game
            }
            else if (key == 'i' || key == 'I') { // I veya i ye bas�ld�g� zaman talimatlar b�l�m� a��l�r.
                drawInstructions(); // Show instructions
            }
            else if(key =='k'|| key=='K'){ // k ya bas�ld��� zaman giri� ekran�na geri d�ner.
            	drawMenu();
			}
        }
    }
    
    

    //initialize the game objects
	    int ball_x = getmaxx() / 2, ball_y = getmaxy() / 2; //Topun pozisyonunu tutan de�i�kenler
	    //getmaxx ve getmaxy ekran�n geni�li�i ve y�ksekli�ini belirtir.
	    int ball_dx = 2, ball_dy = -2; //ba�lang�� konumunu belirler. bell_dx:sa�a , ball_dy:sola hareket
	    int paddle_x = getmaxx() / 2 - PADDLE_WIDTH / 2, paddle_y = getmaxy() - PADDLE_HEIGHT - 10; //paddle pozisyonunu belirler.
		//Paddle � ba�lang�� pozisyonu olarak ekran�n alt orta k�sm�na yerle�tirir.
	    int brick_x[NUM_BRICKS], brick_y[NUM_BRICKS];
	    bool brick_alive[NUM_BRICKS]; // bricklerin alive olup olmad�g�n� tutar.
	
	    // Initialize the bricks
	    int brick_count = 0; //tu�la say�s�n� tutan bir saya� de�i�keni.
	    for (int i = 0; i < 7; i++) { //toplamda 7 sat�r , 9 s�tun olmak �zere 63 brick vard�r.
	        for (int j = 0; j < 9; j++) {
	            brick_x[brick_count] = j * (BRICK_WIDTH + 10) + 50; //konumlar� (brickler aras 10 bo�luk)
	            brick_y[brick_count] = i * (BRICK_HEIGHT + 5) + 50;
	            brick_alive[brick_count] = true; //brickler ba�lang��ta alive durumundad�r.
	            brick_count++;
	        }
	        
    }
     while (!gameOver) {
        cleardevice();
        // Ball �izimi
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, MAGENTA);
        fillellipse(ball_x, ball_y, BALL_RADIUS, BALL_RADIUS); //topun merkez koordinatar�n� kullanrak tam dolu bir �ember �izer.

        // Draw the paddle
        setcolor(MAGENTA);
        setfillstyle(SOLID_FILL, MAGENTA);
        bar(paddle_x, paddle_y, paddle_x + PADDLE_WIDTH, paddle_y + PADDLE_HEIGHT); //koordinatlar� alarak dikd�rtgen �izer.

        // Draw the bricks
        for (int i = 0; i < NUM_BRICKS; i++) {
            if (brick_alive[i]) { //e�er tu�la hala alive durumunda ise o tu�la belirtilen renk ve �ekilde �izilir.
                setcolor(LIGHTMAGENTA);
                setfillstyle(SOLID_FILL,LIGHTMAGENTA);
                bar(brick_x[i], brick_y[i], brick_x[i] + BRICK_WIDTH, brick_y[i] + BRICK_HEIGHT);
            }
        }


        // Move the ball
        ball_x += ball_dx * Ball_speed; //ballSpeed ile topun h�z�n� belirker ve her d�ng�de de�i�ebilir.
        ball_y += ball_dy * Ball_speed;

        // Check for collisions with the screen edges
        //topun ekran�n kenarlar�na �arp�p �arpmad�g� kontrol edilir.
        if (ball_x - BALL_RADIUS < 0 || ball_x + BALL_RADIUS > getmaxx()) { //ball_x 0 dan k���kse yani ekran�n sa� ve sol kenarlar�na �arpt�ysa ;
            ball_dx = -ball_dx; // tersi y�n�ne hareket eder.
        }
        if (ball_y - BALL_RADIUS < 0) { //top �st kenara �arpt�ysa ;
            ball_dy = -ball_dy; //tersi y�n�nde hareket eder.
        }
        if (ball_y + BALL_RADIUS >=getmaxy()) { //topun alt kenara(zemine) �arp�p �arpmad�g� kontrol edilir.

        	decreaseLives(lives); //e�er zemine �arpt�ysa lives 1 azal�r.
        		if (lives == 0){ //e�er can say�s� 0 a d��erse oyun sonlan�r.
				gameOver=true; //oyun sonlan�r.
			}
			else{ //e�er oyuncunun can� kalm��sa; 
				ball_x = getmaxx() / 2; //topun ba�lang�� de�erlerine d�nd�r�l�r
	            ball_y = getmaxy() / 2;
	            ball_dx = 2;
	            ball_dy = -2;
	            paddle_x = getmaxx() / 2 - PADDLE_WIDTH / 2; //paddle ba�lang�� de�erlerine d�nd�r�l�r.
	            paddle_y = getmaxy() - PADDLE_HEIGHT - 10;
			}
        }

        //top ve paddle �n �arp��ma kontrol�
        if (ball_y + BALL_RADIUS >= paddle_y && ball_x >= paddle_x && ball_x <= paddle_x + PADDLE_WIDTH) {
        	//e�er top paddle a �arparsa, topun y�n� de�i�erek yukar� do�ru hareket eder.
            ball_dy = -ball_dy;
        }

        // top ve bricklerin �arp��ma kontrol�
        
       for (int i = 0; i < NUM_BRICKS; i++) { //t�m tu�lalar i�in kontrol
    	if (brick_alive[i]) { //e�er hala alive tu�la varsa opun tu�la ile �arp���p �arp��mad���n� kontrol edecek.
       		 if (ball_x + BALL_RADIUS >= brick_x[i] && ball_x - BALL_RADIUS <= brick_x[i] + BRICK_WIDTH &&
          	 	 ball_y + BALL_RADIUS >= brick_y[i] && ball_y - BALL_RADIUS <= brick_y[i] + BRICK_HEIGHT) {
           		 brick_alive[i] = false; //e�er �arp��ma olursa alive false durumuna d��er.
           		 IncreaseScore(score); // ve score 100 puan ekler
            // Topun y�n�n� tersine �evir
             if (ball_x + BALL_RADIUS <= brick_x[i] || ball_x - BALL_RADIUS >= brick_x[i] + BRICK_WIDTH) {
                ball_dx = -ball_dx; //ve topu tersi y�n�ne d�nd�r�r.
            } else {
                ball_dy = -ball_dy;
            }
            // T�m tu�lalar�n yok edilip edilmedi�ini kontrol et
            for (int j = 0; j < NUM_BRICKS; j++) {
                if (brick_alive[j]) {//e�er oyun bitmi�se yani alive brick kalmam��sa
                    gameOver = false;
                    break;
                }
            }
            if (gameOver) { //e�er oyun bitmi�se game over true yap�l�r.
                gameOver = true;
            }
        }
    }
}
	// Move the paddle
	if (kbhit()) {
	    int key = getch();
	    if (key == 75 || key == 'a' || key == 'A') { // a ya bas�ld�g� zaman paddle sola do�ru hareket edecek.
	        paddle_x = std::max(paddle_x - paddleSpeed, 0);
	    }
	    else if (key == 77 || key == 'd' || key == 'D') { // d ye bas�ld�g� zaman paddle sa�a do�ru hareket edecek.
	        paddle_x = std::min(paddle_x + paddleSpeed, getmaxx() - PADDLE_WIDTH);
	    }

	delay(20);
}
	
		// oyuncunun t�m tu�lalar� yok etmesi durumunda yani oyun kazan�ld�g� zman kontrol eder.
	  int bricks_left = 0;
	  for (int i = 0; i < NUM_BRICKS; i++) {
	      if (brick_alive[i]) { //e�er hala alive tu�la varsa
	          bricks_left++; //e�er alive tu�la varsa brickleft 1 artt�r�l��
	      }
	  }
	  if (bricks_left == 0) { //bricks_left 0 ise t�m tu�lalar�n yok edildi�i anla��lca�� i�in;
	  //gameover true olarak atan�r.
	gameOver = true;

	}
	
	setcolor(LIGHTMAGENTA);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	char scoreStr[20];
	sprintf(scoreStr, "Score: %d", score); //Score u ekrana yazd�r�r.
	outtextxy(10, 10, scoreStr);
	delay(10);
	cleardevice();
	

	
	setcolor(LIGHTMAGENTA);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	char livesStr[10];
	sprintf(livesStr, "Lives: %d", lives); //Lives i ekrana yazd�r�r.
	outtextxy(500, 10, livesStr);
	delay(10);
	cleardevice();

	}
	
	setcolor(RED); //oyun bitti�i zaman Game Over yaz�s�n� ekrana yazd�r�r.
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	outtextxy(getmaxx() / 2 - textwidth("Game Over") / 2, getmaxy() / 2 - textheight("Game Over") / 2, "Game Over");
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	
	setcolor(LIGHTBLUE);
	settextstyle(BOLD_FONT, HORIZ_DIR,2);
	char scoreStr[20];
	sprintf(scoreStr, "Score: %d", score); //Score yaz�s�n� ekrana yazd�r�r.
	outtextxy(180, 300, scoreStr);
	
	getch(); // wait for a key press
	closegraph(); // close the graphics window
	//return�0;
	}
