#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Graphics.hpp"
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <math.h>
#include <string>

using namespace sf;
//using namespace std;

const int M = 20;
const int N = 10;
const int sf1 = 4;

class Point
{
public:
	int x;
	int y;

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void setX(int val) {
		x = val;
	}
	void setY(int val) {
		y = val;
	}
	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}
	Point() {
		x = y = 0;
	}
};

class Figura
{
protected:
	Point arr[sf1];
public:
	Figura() {
		for (int i = 0; i < sf1; i++) {
			arr[i].x = 0;
			arr[i].y = 0;
		}
	}
	Figura(const Figura&obj) {
		for (int i = 0; i < sf1; i++) {
			arr[i].x = obj.arr[i].x;
			arr[i].y = obj.arr[i].y;
		}
	}
	

	virtual int getCentre() {
		return 2;
	}
	virtual void rotate() {
		Point centre = arr[getCentre()];
		for (int i = 0; i<4; i++)
		{
			int x = arr[i].y - centre.y;
			int y = arr[i].x - centre.x;
			arr[i].x = centre.x - x;
			arr[i].y = centre.y + y;
		}
	}
	Point & operator[](int n) {
		return arr[n];
	}
	Figura& operator+(int n) {
		for (int i = 0; i < 4; i++)
			arr[i].x += n;
		return *this;
	}
	Figura& operator++() {
		for (int i = 0; i < 4; i++)
			arr[i].y++;
		return *this;
	}
};

class Figura_i :public Figura {
public:
	Figura_i() {
		arr[0] = Point(0, 0); arr[1] = Point(1, 0);
		arr[2] = Point(2, 0); arr[3] = Point(3, 0);
		for (int i = 0; i < 4; i++)
			arr[i].x += 4;
	}
	int getCentre() {
		return 1;
	}
	
};

class Figura_s :public Figura {
public:
	Figura_s() {
		arr[0] = Point(0, 0); arr[1] = Point(0, 1);
		arr[2] = Point(1, 1); arr[3] = Point(1, 2);
		for (int i = 0; i < 4; i++)
			arr[i].x += 4;
	}
	int getCentre() {
		return 2;
	}
};

class Figura_z :public Figura {
public:
	Figura_z() {
		arr[0] = Point(1, 0); arr[1] = Point(1, 1);
		arr[2] = Point(0, 1); arr[3] = Point(0, 2);
		for (int i = 0; i < 4; i++)
			arr[i].x += 4;
	}
	int getCentre() {
		return 2;
	}
};

class Figura_t :public Figura {
public:
	Figura_t() {
		arr[0] = Point(1, 0); arr[1] = Point(1, 1);
		arr[2] = Point(0, 1); arr[3] = Point(1, 2);
		for (int i = 0; i < 4; i++)
			arr[i].x += 4;
	}
	int getCentre() {
		return 1;
	}
};


class Figura_L :public Figura {
public:
	Figura_L() {
		arr[0] = Point(0, 0); arr[1] = Point(1, 0);
		arr[2] = Point(1, 1); arr[3] = Point(1, 2);
		for (int i = 0; i < 4; i++)
			arr[i].x += 4;
	}
	int getCentre() {
		return 2;
	}
};

class Figura_J :public Figura {
public:
	Figura_J() {
		arr[0] = Point(1, 0); arr[1] = Point(1, 1);
		arr[2] = Point(1, 2); arr[3] = Point(0, 2);
		for (int i = 0; i < 4; i++)
			arr[i].x += 5;
	}
	int getCentre() {
		return 1;
	}
};

class Figura_o :public Figura {
public:
	Figura_o() {
		arr[0] = Point(0, 0); arr[1] = Point(1, 0);
		arr[2] = Point(0, 1); arr[3] = Point(1, 1);
		for (int i = 0; i < 4; i++)
			arr[i].x += 4;
	}
	void rotate() override {  }//переписанная ф-я ротейт для квадрата
};


class Field
{
	int field[M][N]{ 0 };
public:
	Field() {}

	void clear() {
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++) {
				field[i][j] = 0;
			}
	}

	void full(int n) {
		clear();
		if (n < 0) n = 0;
		if (n > 10)n = 10;
		for (int i = M - n; i < M; i++)
			for (int j = 0; j < N; j++) {
				int zal = rand() % 2;
				if (zal)
					field[i][j] = rand() % 7 + 1;
			}
	}
	int& operator()(int i, int j) {
		if (i < 20 && i >= 0 && j < 10 && j >= 0)
			return field[i][j];
		else return field[0][0];
	}
	bool upalo(Figura a1) {
		for (int i = 0; i<4; i++)
			if (a1[i].x < 0 || a1[i].x >= N || a1[i].y >= M || a1[i].y<0) return 0; //stenka potolok i dno
			else if (field[a1[i].y][a1[i].x])  return 0;							//upalo na kubiki
			return 1;
	}

};

class FigFactory
{
public:
	void newFig(Figura*&fig) {
		
		int wyb = rand() % 7;
		
		switch (wyb)
		{
		case 0:
			fig = new Figura_i;
			break;
		case 1:
			fig = new Figura_z;
			break;
		case 2:
			fig = new Figura_s;
			break;
		case 3:
			fig = new Figura_L;
			break;
		case 4:
			fig = new Figura_J;
			break;
		case 5:
			fig = new Figura_t;
			break;
		case 6:
			fig = new Figura_o;
			break;
		}
	}
	void copyfig(Figura*&dest, Figura*&obj) {
	
		Figura_i * ipt = dynamic_cast<Figura_i*>(obj);
		if (ipt)
			dest = new Figura_i(*ipt);
		else
		{	
			Figura_s * spt = dynamic_cast<Figura_s*>(obj);
			if (spt)
				dest = new Figura_s(*spt);
			else {		Figura_z * zpt = dynamic_cast<Figura_z*>(obj);
				if (zpt)
					dest = new Figura_z(*zpt);
				else
				{	
					Figura_t * tpt = dynamic_cast<Figura_t*>(obj);
					if (tpt)
						dest = new Figura_t(*tpt);
					else {		
						Figura_L * lpt = dynamic_cast<Figura_L*>(obj);
						if (lpt)
							dest = new Figura_L(*lpt);
						else {		
							Figura_J * jpt = dynamic_cast<Figura_J*>(obj);
							if (jpt)
								dest = new Figura_J(*jpt);
							else{	
								Figura_o * opt = dynamic_cast<Figura_o*>(obj);
								if (opt)
									dest = new Figura_o(*opt);
								
							}
						}
					}
				}
			}
		}
	}


};



class Game
{
protected:
	int o4ki;
	int level;
	Texture t1, t2, t3, t4,t5,t6;
	Font font;

	Field field;
	Figura f,a1,d;
	Figura *dubl=&d;
	Figura *nextF=&f;
	Figura *a=&a1;
	 
public:


	Game() {
		o4ki = 0;
		level = 1;
	}
	int getO() {
		return o4ki;
	}
	void setO(int n) {
		o4ki = n;
	}
	virtual void setFiles(int vib) {
		
		if (vib == 0) {
			t1.loadFromFile("images/tiles1.bmp");
			t2.loadFromFile("images/background1.png");
			t5.loadFromFile("images/pusto1.png");
			
		}
		else if (vib == 1) {
			t1.loadFromFile("images/tiles2.bmp");
			t2.loadFromFile("images/background2.png");
			t5.loadFromFile("images/pusto2.png");
		}
		else {
			t1.loadFromFile("images/tiles3.bmp");
			t2.loadFromFile("images/background3.png");
			t5.loadFromFile("images/pusto3.png");
		}
		
	}

	int load() {
		int shor = 0;
		FILE *f0 = fopen("Shores.bin", "rb");
		if (f0) {
			fread(&shor, sizeof(int), 1, f0);
			fclose(f0);
		}
		return shor;
	}
	void safe(int shor) {
		FILE *f0 = fopen("Shores.bin", "wb");
		if (f0) {
			fwrite(&shor, sizeof(int), 1, f0);
			fclose(f0);
		}

	}
	~Game()
	{
		if (a) delete a;
		if (nextF) delete nextF;
		if (dubl) delete dubl;
	}
	void play() {
		srand(time(0));
		setFiles(1);
		t4.loadFromFile("images/lose.png");
		t6.loadFromFile("images/control.png");
		font.loadFromFile("Arial_Narrow.ttf");
		Sprite s(t1), background(t2), frame(t3), back_lose(t4), pusto(t5),control(t6);
		int dx = 0; bool rotate = 0; int colorNum = 1, newColor = rand() % 7 + 1;
		Clock cl;
		RenderWindow window(VideoMode(376, 450), "Tetris ");

		sf::Text mytext, tx1, tx2, tx3,tx4,tx5,tx6, menu_t[5];
		mytext.setFont(font);
		mytext.setString("lines to \nnext level");
		mytext.setCharacterSize(20);
		mytext.setStyle(sf::Text::Bold);
		mytext.setFillColor(sf::Color::Black);
		
		tx2.setFont(font);
		tx2.setCharacterSize(20);
		tx2.setStyle(sf::Text::Bold);
		tx2.setFillColor(sf::Color::Black);
		
		tx1 = tx4 = tx5 = tx6 = tx3 = tx2;
		tx1.setString("NEXT LEVEL");
		tx3.setString("NEXT");
	
	
		for (int i = 0; i < 5; i++)
		{
			menu_t[i].setFont(font);
			menu_t[i].setCharacterSize(45);
			menu_t[i].setStyle(sf::Text::Bold);
			menu_t[i].setFillColor(sf::Color::Black);
		}

		
		FigFactory figfactory;
		float delay = 0.8;
		figfactory.newFig(nextF);
		figfactory.newFig(a);
		dubl = nullptr;
		float timer = 0;
		int menuvib = 0,skinvib=0,shores=0,maxshores=0;
		Event null;
		window.pollEvent(null);
		maxshores = load();

		bool begin_game = 0;
		
		while (window.isOpen())
		{
			float time = cl.getElapsedTime().asSeconds();
			cl.restart();
			timer += time;

			Event e,p,p1,contr;

			
			//osnownoje menu
			if (!begin_game) {
				shores = 0;
				o4ki = 0;
				window.clear(Color::Green);
				menu_t[0].setString("SKINS");
				menu_t[1].setString("NEW GAME");
				menu_t[2].setString("BEST SHORES");
				menu_t[3].setString("Control");
				menu_t[4].setString("EXIT");
				p1 = null;
				window.pollEvent(p1);
				p1 = null;
				window.pollEvent(p1);
				if (p1.type == Event::Closed) window.close();
				while (p1.key.code != 27 && p1.key.code != 13) {
					while (window.pollEvent(p1))
					{
						if (p1.type == Event::KeyPressed) {
							if (p1.type == Event::Closed) window.close();else
								if (p1.key.code == Keyboard::Up || p1.key.code == Keyboard::Left) menuvib--;else
									if (p1.key.code == Keyboard::Down || p1.key.code == Keyboard::Right) menuvib++;
							if (menuvib == 5) menuvib = 0;
							if (menuvib < 0 ) menuvib = 4;
						}

					}	
					
					window.clear(Color::Green);
					for (int i = 0; i < 5; i++)
					{
						if (i == menuvib) {
							menu_t[i].setFillColor(sf::Color::Yellow);
							menu_t[i].setPosition(48, 49 + 65 * i);
							window.draw(menu_t[i]);
							menu_t[i].setFillColor(sf::Color::Red);
							menu_t[i].setPosition(50, 50 + 65 * i);
							window.draw(menu_t[i]);
						}
						else {
							menu_t[i].setFillColor(sf::Color::White);
							menu_t[i].setPosition(48, 49 + 65 * i);
							window.draw(menu_t[i]);
							menu_t[i].setFillColor(sf::Color::Black);
							menu_t[i].setPosition(50, 50 + 65 * i);
							window.draw(menu_t[i]);
						}
						
					}
					if (p1.type == Event::Closed) window.close();
					window.display();
				}
				if (p1.key.code == 27|| p1.key.code == 13&& menuvib == 4) window.close();
				if (p1.key.code == 13&&menuvib==1) begin_game = 1;
			}
			
			//vibor tipa igri
			if (menuvib == 0&&!begin_game) {
				window.clear(Color::Green);
				menu_t[0].setString("SIMPLE GAME");
				menu_t[1].setString("CRYSTAL GAME");
				menu_t[2].setString("CLASSIC GAME");
				Event p2=null;
				window.pollEvent(p2);
				printf("+++++++");
				if (p2.type == Event::Closed) window.close();
				int skin = -1;
				
				while (p2.key.code != 27 || skin > -1 && skin<3) {
					while (window.pollEvent(p2))
					{
						if (p2.type == Event::KeyPressed) {
							if (p2.type == Event::Closed) window.close(); else
								if (p2.key.code == Keyboard::Up || p2.key.code == Keyboard::Left) skinvib--; else
									if (p2.key.code == Keyboard::Down || p2.key.code == Keyboard::Right) skinvib++; else
										if (p2.key.code == 13) { skin = skinvib; break;
										};
							if (skinvib == 3) skinvib = 0;
							if (skinvib == -1) skinvib = 2;
						}

					}
					if (skin > -1 && skin < 3) { setFiles(skin); break; }
					if (p2.key.code == 13) { skin = skinvib; setFiles(skin); break; }
					window.clear(Color::Green);
					for (int i = 0; i < 3; i++)
					{
						if (i == skinvib) {
							menu_t[i].setFillColor(sf::Color::Yellow);
							menu_t[i].setPosition(48, 99 + 65 * i);
							window.draw(menu_t[i]);
							menu_t[i].setFillColor(sf::Color::Red);
							menu_t[i].setPosition(50, 100 + 65 * i);
							window.draw(menu_t[i]);
						}
						else {
							menu_t[i].setFillColor(sf::Color::White);
							menu_t[i].setPosition(48, 999 + 65 * i);
							window.draw(menu_t[i]);
							menu_t[i].setFillColor(sf::Color::Black);
							menu_t[i].setPosition(50, 100 + 65 * i);
							window.draw(menu_t[i]);
						}

					}
					if (p2.type == Event::Closed) window.close();
					window.display();
				}
				if (p2.type == Event::Closed) window.close();
				menuvib = 0;
				
			}

			//munu control
			if (menuvib == 3 && !begin_game) {
				window.clear(Color::Yellow);
				window.draw(control);
				window.display();
				menuvib = 0;
				contr = null;
				window.pollEvent(contr);
				if (contr.type == Event::Closed)
						window.close();
				while (contr.type != Event::KeyPressed) {
					window.pollEvent(contr);
					if (contr.type == Event::Closed)
						window.close();
				}
			}

			//menu maxshores
			if (menuvib == 2 && !begin_game) {
				window.clear(Color::Yellow);
				char buf1[10];
				_itoa(maxshores, buf1, 10);
				char str3_lev[30] = "Best ";
				strcat(str3_lev, buf1);
				tx6.setString(str3_lev);
				tx6.setCharacterSize(50);
				tx6.setFillColor(sf::Color::White);
				tx6.setPosition(69, 169);
				window.draw(tx6);
				tx6.setFillColor(sf::Color::Black);
				tx6.setPosition(70, 170);
				window.draw(tx6);
				tx6.setCharacterSize(20);
				window.display();
				menuvib = 0;
				contr = null;

				window.pollEvent(contr);
				if (contr.type == Event::Closed)
					window.close();
				while (contr.type != Event::KeyPressed) {
					window.pollEvent(contr);
					if (contr.type == Event::Closed)
						window.close();
				}
			}

			//igra
			if (begin_game)
			{


				//sobitija igri
				while (window.pollEvent(e))
				{
					if (e.type == Event::Closed)
						window.close();

					if (e.type == Event::KeyPressed)
						if (e.key.code == Keyboard::Up) rotate = true;
						else if (e.key.code == Keyboard::Left) dx = -1;
						else if (e.key.code == Keyboard::Right) dx = 1;
						if (e.key.code == 27) {
							begin_game = 0; 
							field.clear(); 
							o4ki = 0; 
							if (a) delete a;
							figfactory.copyfig(a, nextF);
							if (nextF) delete nextF;
							figfactory.newFig(nextF);
							break;
						}
				}

				if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
				//perezapisatj maxshores
				if(shores>maxshores){ 
					maxshores = shores;
					safe(maxshores);
				}

				//wprawo-wlewo 
				if (dubl) delete dubl;
				figfactory.copyfig(dubl, a); *a = *a + dx;
				if (!field.upalo(*a)) {
					if (a) delete a;
					figfactory.copyfig(a, dubl);
				}


				//perewert
				if (rotate)
				{
					a->rotate();
					if (!field.upalo(*a))
					{
						if (a) delete a;
						figfactory.copyfig(a, dubl);
					}
				}

				char buf1[10];
				_itoa(level, buf1, 10);
				char str1_lev[50] = "level ";
				strcat(str1_lev, buf1);
				tx2.setString(str1_lev);
				_itoa(shores, buf1, 10);
				char str2_lev[30] = "Shores ";
				strcat(str2_lev, buf1);
				tx5.setString(str2_lev);
				_itoa(maxshores, buf1, 10);
				char str3_lev[30] = "Best ";
				strcat(str3_lev, buf1);
				tx6.setString(str3_lev);

				//prowlo wremja
				if (timer > delay)
				{
					if (dubl) delete dubl;
					figfactory.copyfig(dubl, a);  ++(*a);
					if (!field.upalo(*a))
					{
						for (int i = 0; i < 4; i++) field((*dubl)[i].y, (*dubl)[i].x) = colorNum;
						if ((*a)[3].y <= 2 || (*a)[1].y <= 1 || (*a)[0].y <= 2 || (*a)[2].y <= 1) {
							window.clear(Color::Green);
							window.draw(back_lose);
							window.pollEvent(p);
							if (p.type == Event::Closed) window.close();
							while (p.key.code != 27 && p.key.code != 13) {
								if (p.type == Event::Closed) window.close();
								window.clear(Color::Red);
								window.draw(back_lose);
								window.pollEvent(p);
								window.display();
							}
							if (p.key.code == 27) {
								begin_game = 0;
								break;
							}
							if (p.key.code == 13) {
								field.clear();
								shores = 0;
							}
							p = e;
							level = 1;
							o4ki = 0;

						}
						if (a) delete a;
						figfactory.copyfig(a, nextF);
						if (nextF) delete nextF;
						figfactory.newFig(nextF);

						colorNum = newColor;
						newColor = 1 + rand() % 7;
					}

					timer = 0;
				}

				//upalo li
				int k = M - 1;
				for (int i = M - 1; i > 0; i--)
				{
					int count = 0;
					for (int j = 0; j < N; j++)
					{
						if (field(i, j)) count++;
						field(k, j) = field(i, j);
					}
					if (count < N) k--;
					else {
						shores += 100;
						o4ki++;
						if (o4ki >= To_next_lev(level) - 1) {
							for (int i = 0; i < o4ki; i++) {
								s.setTextureRect(IntRect(level % 7 * 18, 0, 18, 18));
								s.setPosition(kordO4kiX(i), kordO4kiY(i));
								s.move(28, 31);
								window.draw(s);
							}
							level++;
							tx1.setPosition(50, 100);
							window.draw(tx1);
							o4ki = 0;
							window.display();
							Sleep(2000);
							field.clear();
							field.full(level + 1);
							//if (level > 10) { window.close();/*end of game win*/ }
						}
					}

				}

				dx = 0; rotate = 0;
				if (level < 10)	delay = pow(0.82, level);
				else delay = 0.2;

				//narisowatj wse
				window.clear(Color::White);
				window.draw(background);

				for (int i = 0; i < M; i++)
					for (int j = 0; j < N; j++)
					{
						if (field(i, j) == 0) continue;
						s.setTextureRect(IntRect(field(i, j) * 18, 0, 18, 18));
						s.setPosition(j * 18, i * 18);
						s.move(28, 31);
						window.draw(s);
					}

				for (int i = 0; i < 4; i++)
				{
					s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
					s.setPosition((*a)[i].x * 18, (*a)[i].y * 18);
					s.move(28, 31);
					window.draw(s);
				}
				for (int i = 0; i < 4; i++)
				{
					s.setTextureRect(IntRect(newColor * 18, 0, 18, 18));
					s.setPosition(((*nextF)[i].x + 8) * 18, ((*nextF)[i].y + 2) * 18);
					s.move(28, 31);
					window.draw(s);
				}
				for (int i = 0; i < To_next_lev(level) - 1; i++)
				{
					pusto.setTextureRect(IntRect(0, 0, 18, 18));
					pusto.setPosition(kordO4kiX(i), kordO4kiY(i));
					pusto.move(28, 31);
					window.draw(pusto);
				}
				for (int i = 0; i < o4ki; i++)
				{
					s.setTextureRect(IntRect(level % 7 * 18, 0, 18, 18));
					s.setPosition(kordO4kiX(i), kordO4kiY(i));
					s.move(28, 31);
					window.draw(s);
				}

				mytext.setFillColor(sf::Color::White);
				mytext.setPosition(239, 169);
				window.draw(mytext);
				mytext.setFillColor(sf::Color::Black);
				mytext.setPosition(240, 170);
				window.draw(mytext);

				tx3.setFillColor(sf::Color::White);
				tx3.setPosition(239, 39);
				window.draw(tx3);
				tx3.setFillColor(sf::Color::Black);
				tx3.setPosition(240, 40);
				window.draw(tx3);

				tx2.setFillColor(sf::Color::White);
				tx2.setPosition(29, 419);
				window.draw(tx2);
				tx2.setFillColor(sf::Color::Black);
				tx2.setPosition(30, 420);
				window.draw(tx2);

				tx5.setFillColor(sf::Color::White);
				tx5.setPosition(109, 419);
				window.draw(tx5);
				tx5.setFillColor(sf::Color::Black);
				tx5.setPosition(110, 420);
				window.draw(tx5);

				tx6.setFillColor(sf::Color::White);
				tx6.setPosition(249, 419);
				window.draw(tx6);
				tx6.setFillColor(sf::Color::Black);
				tx6.setPosition(250, 420);
				window.draw(tx6);

				window.display();
			}
		}
	}

	virtual int kordO4kiX(int i) {
		int j=0;
		if (i < 10) j = 1;
		else {
			if (i >= 10 && i < 20)
				j = 2;
			else j = 3;
		}
		return (16 - j) * 18;
	}
	virtual int kordO4kiY(int i) {
		return (M - i % 10) * 18 - 10;
	}
	virtual int To_next_lev(int l) {
		return 25 - l;
	}



};


int main()
{
	srand(time(0));
	
	Game B;
	B.play();



	return 0;
}