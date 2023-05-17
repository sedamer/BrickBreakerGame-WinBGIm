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
	void drawMenu() { // giriþ ekraný çizdirme
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
	
	void drawInstructions() { // i ye bastýgýnda Talimatlar bölümü açýlýr. Instruction kýsmý
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

	
void IncreaseScore(int& score) { // Score u 100 arttýrma
    score += 100;
}
void decreaseLives(int &lives){ //LÝves i 1 azaltma
	lives--;
}
	int main(){
		int gd = DETECT, gm;
	    initgraph(&gd, &gm, "");
	
	    int NUM_BRICKS=63;  //brick sayýsý 63 tane
    	 drawMenu(); //giriþ menüsünü ekrana çizdirmek için.

    while (true) {
        if (kbhit()) {
            int key = getch();
            if (key == 13) { // Enter key e basýldýðý zaman oyun baþlar.
                break; // Start the game
            }
            else if (key == 27) { // Esc key e basýldýðý zaman oyun biter ve kapanýr.
                closegraph();
                return 0; // Quit the game
            }
            else if (key == 'i' || key == 'I') { // I veya i ye basýldýgý zaman talimatlar bölümü açýlýr.
                drawInstructions(); // Show instructions
            }
            else if(key =='k'|| key=='K'){ // k ya basýldýðý zaman giriþ ekranýna geri döner.
            	drawMenu();
			}
        }
    }
    
    

    //initialize the game objects
	    int ball_x = getmaxx() / 2, ball_y = getmaxy() / 2; //Topun pozisyonunu tutan deðiþkenler
	    //getmaxx ve getmaxy ekranýn geniþliði ve yüksekliðini belirtir.
	    int ball_dx = 2, ball_dy = -2; //baþlangýç konumunu belirler. bell_dx:saða , ball_dy:sola hareket
	    int paddle_x = getmaxx() / 2 - PADDLE_WIDTH / 2, paddle_y = getmaxy() - PADDLE_HEIGHT - 10; //paddle pozisyonunu belirler.
		//Paddle ý baþlangýç pozisyonu olarak ekranýn alt orta kýsmýna yerleþtirir.
	    int brick_x[NUM_BRICKS], brick_y[NUM_BRICKS];
	    bool brick_alive[NUM_BRICKS]; // bricklerin alive olup olmadýgýný tutar.
	
	    // Initialize the bricks
	    int brick_count = 0; //tuðla sayýsýný tutan bir sayaç deðiþkeni.
	    for (int i = 0; i < 7; i++) { //toplamda 7 satýr , 9 sütun olmak üzere 63 brick vardýr.
	        for (int j = 0; j < 9; j++) {
	            brick_x[brick_count] = j * (BRICK_WIDTH + 10) + 50; //konumlarý (brickler aras 10 boþluk)
	            brick_y[brick_count] = i * (BRICK_HEIGHT + 5) + 50;
	            brick_alive[brick_count] = true; //brickler baþlangýçta alive durumundadýr.
	            brick_count++;
	        }
	        
    }
     while (!gameOver) {
        cleardevice();
        // Ball çizimi
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, MAGENTA);
        fillellipse(ball_x, ball_y, BALL_RADIUS, BALL_RADIUS); //topun merkez koordinatarýný kullanrak tam dolu bir çember çizer.

        // Draw the paddle
        setcolor(MAGENTA);
        setfillstyle(SOLID_FILL, MAGENTA);
        bar(paddle_x, paddle_y, paddle_x + PADDLE_WIDTH, paddle_y + PADDLE_HEIGHT); //koordinatlarý alarak dikdörtgen çizer.

        // Draw the bricks
        for (int i = 0; i < NUM_BRICKS; i++) {
            if (brick_alive[i]) { //eðer tuðla hala alive durumunda ise o tuðla belirtilen renk ve þekilde çizilir.
                setcolor(LIGHTMAGENTA);
                setfillstyle(SOLID_FILL,LIGHTMAGENTA);
                bar(brick_x[i], brick_y[i], brick_x[i] + BRICK_WIDTH, brick_y[i] + BRICK_HEIGHT);
            }
        }


        // Move the ball
        ball_x += ball_dx * Ball_speed; //ballSpeed ile topun hýzýný belirker ve her döngüde deðiþebilir.
        ball_y += ball_dy * Ball_speed;

        // Check for collisions with the screen edges
        //topun ekranýn kenarlarýna çarpýp çarpmadýgý kontrol edilir.
        if (ball_x - BALL_RADIUS < 0 || ball_x + BALL_RADIUS > getmaxx()) { //ball_x 0 dan küçükse yani ekranýn sað ve sol kenarlarýna çarptýysa ;
            ball_dx = -ball_dx; // tersi yönüne hareket eder.
        }
        if (ball_y - BALL_RADIUS < 0) { //top üst kenara çarptýysa ;
            ball_dy = -ball_dy; //tersi yönünde hareket eder.
        }
        if (ball_y + BALL_RADIUS >=getmaxy()) { //topun alt kenara(zemine) çarpýp çarpmadýgý kontrol edilir.

        	decreaseLives(lives); //eðer zemine çarptýysa lives 1 azalýr.
        		if (lives == 0){ //eðer can sayýsý 0 a düþerse oyun sonlanýr.
				gameOver=true; //oyun sonlanýr.
			}
			else{ //eðer oyuncunun caný kalmýþsa; 
				ball_x = getmaxx() / 2; //topun baþlangýç deðerlerine döndürülür
	            ball_y = getmaxy() / 2;
	            ball_dx = 2;
	            ball_dy = -2;
	            paddle_x = getmaxx() / 2 - PADDLE_WIDTH / 2; //paddle baþlangýç deðerlerine döndürülür.
	            paddle_y = getmaxy() - PADDLE_HEIGHT - 10;
			}
        }

        //top ve paddle ýn çarpýþma kontrolü
        if (ball_y + BALL_RADIUS >= paddle_y && ball_x >= paddle_x && ball_x <= paddle_x + PADDLE_WIDTH) {
        	//eðer top paddle a çarparsa, topun yönü deðiþerek yukarý doðru hareket eder.
            ball_dy = -ball_dy;
        }

        // top ve bricklerin çarpýþma kontrolü
        
       for (int i = 0; i < NUM_BRICKS; i++) { //tüm tuðlalar için kontrol
    	if (brick_alive[i]) { //eðer hala alive tuðla varsa opun tuðla ile çarpýþýp çarpýþmadýðýný kontrol edecek.
       		 if (ball_x + BALL_RADIUS >= brick_x[i] && ball_x - BALL_RADIUS <= brick_x[i] + BRICK_WIDTH &&
          	 	 ball_y + BALL_RADIUS >= brick_y[i] && ball_y - BALL_RADIUS <= brick_y[i] + BRICK_HEIGHT) {
           		 brick_alive[i] = false; //eðer çarpýþma olursa alive false durumuna düþer.
           		 IncreaseScore(score); // ve score 100 puan ekler
            // Topun yönünü tersine çevir
             if (ball_x + BALL_RADIUS <= brick_x[i] || ball_x - BALL_RADIUS >= brick_x[i] + BRICK_WIDTH) {
                ball_dx = -ball_dx; //ve topu tersi yönüne döndürür.
            } else {
                ball_dy = -ball_dy;
            }
            // Tüm tuðlalarýn yok edilip edilmediðini kontrol et
            for (int j = 0; j < NUM_BRICKS; j++) {
                if (brick_alive[j]) {//eðer oyun bitmiþse yani alive brick kalmamýþsa
                    gameOver = false;
                    break;
                }
            }
            if (gameOver) { //eðer oyun bitmiþse game over true yapýlýr.
                gameOver = true;
            }
        }
    }
}
	// Move the paddle
	if (kbhit()) {
	    int key = getch();
	    if (key == 75 || key == 'a' || key == 'A') { // a ya basýldýgý zaman paddle sola doðru hareket edecek.
	        paddle_x = std::max(paddle_x - paddleSpeed, 0);
	    }
	    else if (key == 77 || key == 'd' || key == 'D') { // d ye basýldýgý zaman paddle saða doðru hareket edecek.
	        paddle_x = std::min(paddle_x + paddleSpeed, getmaxx() - PADDLE_WIDTH);
	    }

	delay(20);
}
	
		// oyuncunun tüm tuðlalarý yok etmesi durumunda yani oyun kazanýldýgý zman kontrol eder.
	  int bricks_left = 0;
	  for (int i = 0; i < NUM_BRICKS; i++) {
	      if (brick_alive[i]) { //eðer hala alive tuðla varsa
	          bricks_left++; //eðer alive tuðla varsa brickleft 1 arttýrýlýç
	      }
	  }
	  if (bricks_left == 0) { //bricks_left 0 ise tüm tuðlalarýn yok edildiði anlaþýlcaðý için;
	  //gameover true olarak atanýr.
	gameOver = true;

	}
	
	setcolor(LIGHTMAGENTA);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	char scoreStr[20];
	sprintf(scoreStr, "Score: %d", score); //Score u ekrana yazdýrýr.
	outtextxy(10, 10, scoreStr);
	delay(10);
	cleardevice();
	

	
	setcolor(LIGHTMAGENTA);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	char livesStr[10];
	sprintf(livesStr, "Lives: %d", lives); //Lives i ekrana yazdýrýr.
	outtextxy(500, 10, livesStr);
	delay(10);
	cleardevice();

	}
	
	setcolor(RED); //oyun bittiði zaman Game Over yazýsýný ekrana yazdýrýr.
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	outtextxy(getmaxx() / 2 - textwidth("Game Over") / 2, getmaxy() / 2 - textheight("Game Over") / 2, "Game Over");
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	
	setcolor(LIGHTBLUE);
	settextstyle(BOLD_FONT, HORIZ_DIR,2);
	char scoreStr[20];
	sprintf(scoreStr, "Score: %d", score); //Score yazýsýný ekrana yazdýrýr.
	outtextxy(180, 300, scoreStr);
	
	getch(); // wait for a key press
	closegraph(); // close the graphics window
	//return 0;
	}
