#include <stdio.h>     
#include <stdlib.h>   
#include <time.h>       
#include <conio.h>
#include <windows.h>
#include <string.h>

#define HIGHSCORE_1 "highscore1.dat"
#define HIGHSCORE_2 "highscore2.dat"
#define HIGHSCORE_3 "highscore3.dat"

/* _________________________________________ Variabel Global  _________________________________________________ */

int menu=0;
int level=0;
int waktuMain;
int Pilihan;
//char Input;
int game = 1;
char kata[7];
int jmlhrf;
int giliran;
char bell = 07;
int peek;

typedef struct {
	char name[21];
	int skor;
//	int numberOfMoves;
//	int numberOfKicks;
//	long long int duration;
} HighscoreData;

HighscoreData data, list[100], temp;



typedef struct{
	char nama[200];
	int skor;
	int menyerah;
}Player;

Player one, two;

typedef struct{
	int menit;
	int detik;
}waktu;

typedef struct{
	char huruf;
	int banyak;
	int bobot;
} DataHuruf;

DataHuruf Rakhuruf[27] ={
		{'A', 9, 1},
		{'B', 2, 3},
		{'C', 2, 3},
		{'D', 4, 2},
		{'E', 9, 1},
		{'F', 2, 4},
		{'G', 2, 2},
		{'H', 2, 4},
		{'I', 9, 1},
		{'J', 1, 8},
		{'K', 1, 5},
		{'L', 4, 1},
		{'M', 2, 3},
		{'N', 6, 1},
		{'O', 9, 1},
		{'P', 2, 3},
		{'Q', 1, 10},
		{'R', 6, 1},
		{'S', 4, 1},
		{'T', 6, 1},
		{'U', 9, 1},
		{'V', 2, 4},
		{'W', 2, 4},
		{'X', 1, 8},
		{'Y', 2, 4},
		{'Z', 1, 10},
		{' ', 2, 0},
		
};

typedef struct{
	int DL ;
	int DW ;
	int TL ;
	int TW ;
	int bintang;
	DataHuruf Letter ;
} DataPapan;

DataPapan Board[13][13];

/* ##################################### Modul yang digunakan ################################################# */
void setcolor(unsigned short color); // Prosedur dari referensi untuk mengubah warna teks atau background
void delay(int x); // Prosedur dari referensi untuk membuat animasi berjalan
void gotoxy(int x, int y); // Prosedur dari referensi untuk menentukan posisi kursor
void loading();  // Prosedur dari referensi untuk menampilkan loading
void judul(); // Prosedur untuk menampilkan judul game
void bingkai(void); // Prosedur dari referensi untuk membuat bingkai 
int menu_game(); // Fungsi untuk menampilkan dan memilih menu game
int cursor(int option,int x,int y); // Fungsi dari referensi untuk menggerakkan kursor
int pilihanmenu(); // Fungsi untuk menerapkan kondisi yang terjadi sesuai menu yang dipilih
void help(); // Prosedur untuk menampilkan file cara bermain
void LearnKamus(); // Prosedur untuk menampilkan kamus di awal game jika dipilih
void NamaPlayer(void); // Prosedur untuk memberikan nilai pada variabel global 
void PilihLevel(); // Prosedur untuk menampilkan dan memilih level	
//void waktubermain(); // Fungsi  untuk menampilkan dan memilih waktu bermain
void KondisiPapan(); // Prosedur untuk Pengkondisian nilai bonus pada Papan
void penampilanPermainan(); // Prosedur untuk Menampilkan tampilan Permainan
void ketpoin(); // Prosedur untuk menampilkan bobot poin masing-masing huruf
void bonus(); // Prosedur untuk menampilkan keterangan kode Bonus poin
//void Timergame( int x ); // Prosedur untuk menghitung mundur waktu bermain
void hrftersedia(); // Prosedur untuk menghitung jumlah huruf yang tersisa
void Acakhuruf(); // Prosedur untuk mengacak huruf
int bentuk(); // Fungsi untuk menginputkan bentuk kata yang ingin dibuat user lalu mengembalikkan nilainya
int chooseline(); // Fungsi untuk menginputkan posisi baris huruf pertama lalu mengembalikkan nilainya
int chooseclm(); // Fungsi untuk menginputkan posisi kolom huruf pertama lalu mengembalikkan nilainya
int UseLetter(); // Fungsi untuk Menentukan banyak huruf yang akan digunakan
int IsvalidPosition(int baris, int kolom, int bykhuruf, int BentukKata); // Fungsi untuk menentukan valid tidaknya posisi
int Iswordvalid(int baris, int kolom, int BentukKata, char Input ); // Fungsi untuk memeriksa kata yang tercipta dari huruf yang berdekatan dengan Input
int Vertikal(int baris, int kolom, int bykhuruf, int BentukKata); // Fungsi untuk input kata secara vertikal dan mengembalikkan poin yang diperoleh 
int Horizontal(int baris, int kolom, int bykhuruf, int BentukKata); // Fungsi untuk input kata secara Horizontal dan mengembalikkan poin yang diperoleh 
void Perintah(char Input); // Prosdur untuk mengkondisikan perintah yang mungkin terjadi
int CekKamus(char input[]); // Fungsi untuk mengecek kesesuaian kata dengan kamus
void KamusBenar(int baris, int kolom, char hasil[], int bykhuruf, int BentukKata); // Prosedur untuk menampilkan kata pada papan jika kata tersebut ada dalam kamus
void KamusSalah(); // Prosedur untuk menampilkan pemberitauan kalau kata tidak ada dalam kamus
void BackHurufNotUse(char temp[]); // Prosedur untuk mengembalikkan huruf yang tidak terpakai sehingga jumlahnya sesuai
int skor(char temp[],int baris, int kolom, int bykhuruf, int BentukKata); // Fungsi untuk menghitung poin dan  mengembalikkan poin yang diperoleh 
void playerGame(); // Prosedur untuk menjalankan instruksi permainan
void clsperintah(); // Prosedur untuk Membersikah perintah saat Input posisi
void BackLetterNotUse(char temp[]); // Prosedur untuk mengembalikkan huruf yang tidak dipakai
void BackAllLetter(); //Prosedur Mengembalikkan kata jika kata salah
void GameOver(); // Prosedur yang menentukan Game berakhir
int checkWin(); // Fungsi untuk menentukan pemenang
void writeData(); // Prosedur dari referensi untuk Memindahkan data pemain ke data highscore
int GetData(); // Fungsi dari referensi untuk Mengambil data dari file highscore yang sudah disimpan dari modul writeData
void sortHighscore(int N ); // Prosedur dari referensi untuk Mengurutkan highscore
void swap(int i, int j); // Prosedur dari referensi untuk menukar jika kondisi sorting terpenuhi
void highscore(); // Prosedur dari referensi untuk menampilkan highscore
void showWin(); // Prosedur yang menampilkan player yang memenangkan 
int PoinSalah(); // Fungsi untuk memberi dan mengembalikan nilai poin ketika kata yang dihasilkan salah


/* _______________________________________________ Program Modul ________________________________________________ */
/* ______________________________________________ Sebelum Game mulai ____________________________________________ */

// Prosedur dari referensi untuk mengubah warna teks atau background
void setcolor(unsigned short color)
{
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hCon,color);
}

// Prosedur dari referensi untuk membuat animasi berjalan
void delay(int x)
{
	int delay = 1;
	while(delay < x){
		delay++;
	}
}


// Prosedur dari referensi internet untuk menentukan posisi 
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;  
	COORD dwCursorPosition;  
	dwCursorPosition.X = x;  
	dwCursorPosition.Y = y;  
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);   
}

// Prosedur dari referensi internet untuk menampilkan loading
void loading()
{
	int i;
		for(i = 50; i<=90; i++){
		gotoxy(i,18);
		printf("-");
		gotoxy(i,20);
		printf("-");
		system("color 70");
		delay(10000000);
	}
	
	for(i = 1; i <= 100; i++){
		gotoxy(63,19);
		printf("L O A D I N G ");
		printf("%d %%", i);
		delay(100000000);
	}
}

// Prosedur untuk menampilkan judul game
void judul()
{
	int i;
	system("cls");
	i=1;
	while (i<=10)
	{
	gotoxy(i,1);     printf("  *++++++    *++++++*   *+++++*      *+++*     *+++++*    *+++++*    ++       ++++++ \n");
	gotoxy(19-i,2);  printf(" ++         ++     ++    ++    ++    *+   +*    ++    ++   ++    ++   ++       ++     \n");
	gotoxy(i-1,3);   printf(" ++        ++            ++    ++   *+     +*   ++    +*   ++    +*   ++       ++     \n");
	gotoxy(19-i,4);  printf("  *++++*  *              *+++++*   *+ ***** +*  ++*****    ++*****    ++       *+++++ \n");
	gotoxy(i-1,5);   printf("       ++  ++            ++  ++    ++       ++  ++    +*   ++    +*   ++       ++     \n");
	gotoxy(19-i,6);  printf("       ++  ++      ++    ++   ++   ++       ++  ++    ++   ++    ++   ++       ++     \n");
	gotoxy(i-1,7);   printf(" ++++++*    *++++++*     ++    ++  ++       ++  *+++++*    *+++++*    *++++++  ++++++ \n");
		delay(100000000);
		i++;
	}
}


// Prosedur dari referensi untuk membuat bingkai
void bingkai(void)
{
int i;
for (i = 9; i <= 80; i++){
		gotoxy(i,12);
		printf("_");
		gotoxy(i,24);
		printf("_");
		delay(10000000);
	}
	//bingkai samping
	for (i = 12; i <= 24; i++){
		gotoxy(9,i);
		printf("|");
		gotoxy(80,i);
		printf("|");
		delay(10000000);
	}	
}


// Fungsi untuk menampilkan dan memilih menu game
int menu_game()
{
	system("cls");
	judul();
	bingkai();
	gotoxy(5,14);
	printf("\t\t\t               MENU GAME    \n");
	printf("\t\t\t                            \n");
	printf("\t\t\t                 PLAY       \n");
	printf("\t\t\t                 HELP       \n");
	printf("\t\t\t               DICTIONARY   \n");
	printf("\t\t\t               HIGHSCORE    \n");	
	printf("\t\t\t                 EXIT       \n");
	printf("\t\t\t                            \n");
	printf("\t\t\t           CHOOSE THE MENU  \n\n\n\n\n");
	return cursor(5,35,16);	
}

// Fungsi dari referensi untuk menggerakkan kursor
int cursor(int option,int x,int y)											
{
int select=1;
	int input;
	gotoxy(x,y);printf("%c",16);
	do
	{
		input=getch();															
		if(input==80)														
		{
			gotoxy(x,y);printf(" ");
			y++;select++;
			if(select>option)
			{
				y=y-option;
				select=1;
			}
			gotoxy(x,y);printf("%c",16);
		}
		if(input==72)											
		{
			gotoxy(x,y);printf(" ");
			y--;select--;
			if(select<1)
			{
				y=y+option;
				select=option;
			}
			gotoxy(x,y);printf("%c",16);			
		}
		if(input==8) //backspace
		{
			select=8;
		}
	}
	while(input!=13 && input!=8);														//berakhir saat input berisi enter
	return select;																
}

// Fungsi untuk menerapkan kondisi yang terjadi sesuai menu yang dipilih
int pilihanmenu()
{
	int end;		
	menu = menu_game();
	switch(menu)
	{
		case 1:
			NamaPlayer();
			PilihLevel();
			waktubermain();
			playerGame();
			break;
		case 2:
			help();
			pilihanmenu();
			break;
		case 3:
			LearnKamus();
			pilihanmenu();
			break;
		case 4:
			highscore();
			break;
		case 5:
		    exit(1);
			end=1;					//end bernilai 1 setelah memilih exit
			break;
	}
	return end;
}

// Prosedur untuk menampilkan file cara bermain
void help()																	
{
	FILE *AturanMain;
	char help;
	char Input;
	AturanMain=fopen("help.txt","r");
	if (AturanMain == NULL)
	{
		printf("File tidak dapat dibuka\n\r");
		exit(0);
	}
	
	system("cls");	
	while((help=getc(AturanMain))!=EOF)
	   {
	   	putch(help);
	   }
  	system("pause");
  	gotoxy(0,0);printf("Ketik Apapun Untuk Kembali");
	system("cls");
	Input = getchar();
	fclose(AturanMain);
}

// Prosedur untuk menampilkan kamus di awal game jika dipilih
void LearnKamus() 
{
	FILE *Seekamus;
	char kamus;
	char Input;
	Seekamus=fopen("kamus2.txt","r");
	if (Seekamus == NULL)
	{
		printf("File tidak dapat dibuka\n\r");
		exit(0);
	}
	
	system("cls");	
	while((kamus=getc(Seekamus))!=EOF)
	   {
	   	putch(kamus);
	   	Sleep(200);
	   }
	system("cls");
	gotoxy(0,0);printf("Ketik Apapun Untuk Kembali");
	Input = getchar();
	fclose(Seekamus);

}	

// Prosedur untuk memberikan nilai pada variabel global nama1 dan nama2	
void NamaPlayer(void)
{
	system("cls");
	judul();
	bingkai();
	gotoxy(0,14);
	printf("\t\t\t             PLEASE ENTER YOUR NAME\n");
	printf("\t\t\t 	          CHATTERBOX	  	        \n");
	printf("\t\t\t                  PLAYER 1 	            \n\n");
	printf("\t\t\t       [                         ]      \n\n");
	gotoxy(37,18);fgets(one.nama, sizeof(one.nama), stdin);
	printf("\n");
	printf("\t\t\t                  PLAYER 2 		         \n\n");
	printf("\t\t\t       [                         ]       \n");
	gotoxy(37,22); fgets(two.nama, sizeof(two.nama), stdin);
}

// Prosedur untuk menampilkan dan memilih level
void PilihLevel() 
{
	system("cls");
	judul();
	bingkai();
	gotoxy(0,14);
	printf("\t\t\t               SELECT LEVEL       \n");
	printf("\t\t\t                                  \n");
	printf("\t\t\t                   EASY           \n");
	printf("\t\t\t                  MEDIUM          \n");
	printf("\t\t\t                   HARD           \n"); 
	printf("\t\t\t                                  \n");
	printf("\t\t\t                                  \n");
	printf("\t\t\t             CHOOSE THE LEVEL     \n");
	menu=cursor(3,38,16);
 	if(menu!=8)														//level dipilih dengan menggunakan kursor
	{
		switch(menu)
		{
			case 1: level = 1;
				break;
			case 2: level = 2;
				break;
			case 3: level = 3;
				break;
		}	
	}
}

// Fungsi  untuk menampilkan dan memilih waktu bermain
void waktubermain()
{
	system("cls");
	judul();
	bingkai();
	gotoxy(5,14);
	printf("\t\t\t              SELECT TIME        \n");
	printf("\t\t\t                              \n");
	printf("\t\t\t              30 MINUTES           \n");
	printf("\t\t\t              45 MINUTES           \n");
	printf("\t\t\t              60 MINUTES           \n"); 
	printf("\t\t\t                                   \n");
	printf("\t\t\t                                   \n");
	printf("\t\t\t            CHOOSE THE TIME     \n");
	menu=cursor(3,36,16);
	if(menu!=8)														//Waktu dipilih dengan menggunakan kursor
	{
		switch(menu)
		{
			case 1: waktuMain = 30;
				break;
			case 2: waktuMain = 45;
				break;
			case 3: waktuMain = 60;
				break;
		}
	}
//		KondisiPapan();
//		penampilanPermainan();
	//	Timergame(waktuMain);
}

/* ____________________________________________ Saat Game Berlangsung _________________________________________ */

// Prosedur untuk Pengkondisian nilai bonus pada Papan
void KondisiPapan() 
{
	int i, j;
	for(i = 0; i < 13; i++){
		for(j = 0; j < 13; j++){
			if(i == 1 || i == 11){
				if(j == 1 || j == 6 ||j == 11){
					Board[i][j].DL =1;
				}else if( j == 3 || j== 9 ){
					Board[i][j].DW = 1;
				}
			}else if(i == 2 || i == 10){
				if(j == 2 || j == 10){
					Board[i][j].TL = 1;
				}else if(j == 4 || j == 8){
					Board[i][j].TW = 1;
				}
			}else if(i == 3 || i == 9){
				if(j == 1 || j == 5 || j == 7 || j == 11){
					Board[i][j].DW = 1;
				}else if(j == 3|| j == 9){
					Board[i][j].TL = 1;
				}	
			}else if(i == 4 || i == 8){
				if(j == 2 || j == 4 || j == 8 || j == 10){
					Board[i][j].TW = 1;
				}else if(j == 6){
					Board[i][j].DW = 1;
				}
			}else if(i == 5 || i == 7){
				if(j == 3|| j == 5 || j == 7 || j == 9){
					Board[i][j].DW = 1;
				}
			}else if(i == 6){
				if(j == 1 || j == 11){
					Board[i][j].DL = 1;
				}else if(j == 4 || j == 8 ){
					Board[i][j].DW = 1;
				}else if(j == 6){
					Board[i][j].bintang = 1;
				}
			}
		}
	}
		for(i = 0; i < 13; i++){
			for(j = 0; j < 13; j++){
				Board[i][j].Letter.huruf =' ';
			}
		}
}

// Prosedur untuk Menampilkan tampilan Permainan
void penampilanPermainan()
{
	char kata[27];
	system ("cls");
	int a,l;
	hrftersedia();
//	gotoxy(65,3);printf("Banyak Huruf: %d", jmlhrf);
	gotoxy(24,0);printf("S C R A B B L E");
	gotoxy(8,4); printf("PLAYER 1" );
	gotoxy(8,5); printf("Nama: %s",strupr(one.nama) );
	gotoxy(45,4); printf("PLAYER 2" );
	gotoxy(45,5); printf("Nama: %s",strupr(two.nama) );
	gotoxy(8,6); printf("Score: %d",one.skor );
	gotoxy(45,6); printf("Score: %d",two.skor );
	gotoxy(8,8);printf("  1    2    3    4    5    6    7    8    9    10    11");
	gotoxy(8,9); printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	a = 10; 
	for(int k = 0; k < 11; k++){
		gotoxy(8,a);
		for(int l = 0; l < 11; l++){
		if(Board[k][l].DL == 1){
			printf("| ");
			printf("@  ");
		}else if(Board[k][l].DW == 1){
			printf("| ");
			printf("&  ");
		}else if(Board[k][l].TW == 1){
			printf("| ");
			printf("$  ");
	    }else if(Board[k][l].TL == 1){
	    	printf("| ");
			printf("#  ");         
		}else if(Board[k][l].bintang == 1){
			printf("| ");
			printf("*  ");
		}else{
			printf("| ");
			printf("   ");
			}
		}
		gotoxy(8,a+1);printf("-------------------------------------------------------");
		a = a + 2;
	}
	a = 10;
	for(int k = 1; k < 12; k++){
		gotoxy(8,a);
		for(int l = 1; l < 12; l++){
		if(Board[k][l].DL == 1){
			printf("| ");
			printf("@  ");
		}else if(Board[k][l].DW == 1){
			printf("| ");
			printf("&  ");
		}else if(Board[k][l].TW == 1){
			printf("| ");
			printf("$  ");
	    }else if(Board[k][l].TL == 1){
	    	printf("| ");
			printf("#  ");         
		}else if(Board[k][l].bintang == 1){
			printf("| ");
			printf("*  ");
		}else{
			printf("| ");
			printf("   ");
			}
		}
		gotoxy(8,a+1);printf("-------------------------------------------------------");
		a = a + 2;
	}
	a = 10;
	for (int i = 1; i < 12; i++){
	gotoxy(6,a);printf("%d", i);
	a= a+2;
	}
	a=10;
	for (int i = 1; i < 12; i++){
		gotoxy(62,a);
		printf("|");
		a = a + 2;
	}		
	ketpoin();
	bonus();
	//bentuk();

//	Acakhuruf();
	
}

// Prosedur untuk menampilkan bobot poin masing-masing huruf
void ketpoin() 
{
	gotoxy(65,2);printf("  Point Each Letter                     \n"); 
	gotoxy(65,3);printf("[A, I, U, E, O, N, R, S, T, U]	:  1 Poin\n");
	gotoxy(65,4);printf("[D, G]	                    	:  2 Poin\n");
	gotoxy(65,5);printf("[B, C, M, P]	                :  3 Poin\n");
	gotoxy(65,6);printf("[F, H, V, W]	                :  4 Poin\n");
	gotoxy(65,7);printf("[K]                            :  5 Poin\n");
	gotoxy(65,8);printf("[J, X]	                    	:  8 Poin\n");
	gotoxy(65,9);printf("[Q, Z]                         :  10 Poin\n");
	gotoxy(65,10);printf("[BLANK]                       :  0 Poin\n");
	gotoxy(73,13);printf("CLICK ENTER AFTER INPUT LETTER        ");
}
	
//Prosedur untuk menampilkan keterangan kode Bonus poin
void bonus()  
{
	gotoxy(124,2);printf("    Box Bonus"); 
	gotoxy(124,3);printf("@ :  Double Letter");
	gotoxy(124,4);printf("& :  Double Word");
	gotoxy(124,5);printf("$ :  Triple Word");
	gotoxy(124,6);printf("# :  Triple Letter");
	gotoxy(124,7);printf("* :  Posisi huruf pertama pada kata pertama ");

}

// Prosedur untuk menghitung jumlah huruf yang tersisa
void hrftersedia()  
{
	int i;
	int jumlah = 0;
	for (i= 0; i < 27; i++){
	jumlah = jumlah + Rakhuruf[i].banyak;
	}
	jmlhrf = jumlah;
	gotoxy(8,2);printf("                          ");
	gotoxy(8,2);printf("Many Letter : %d", jmlhrf);
}

// Prosedur untuk mengacak huruf
void Acakhuruf() 
{
int temp[27] = {0};	
int i, j, k, l, n, a;
int sama, banyak, simpan;
char Input;
n = 0;
banyak = 0;
	for ( i = 0; i < 27; i++){
		if(Rakhuruf[i].banyak != 0){
			temp[n]=  i;
			banyak++;
			n++;
		}
	}
	
	srand(time(0));
	for(k = 0; k < banyak; k++){
		j = rand()% banyak;
		simpan = temp[j];
		temp[j]=temp[k];
		temp[k]=simpan;
	}if(banyak >= 7){ 
		for(l = 0; l < 7; l++){
			kata[l]=Rakhuruf[temp[l]].huruf;
			Rakhuruf[temp[l]].banyak = Rakhuruf[temp[l]].banyak - 1;
		}
		gotoxy(22,32);printf("Letters that can be used");
		a = 15;
		for(k = 0; k < 7; k++){
			gotoxy(a, 34);	printf("[ %c ]", kata[k]);
			a = a + 6;
		}
	}else{
		for(l = 0; l < banyak ; l++){
			kata[l]=Rakhuruf[temp[l]].huruf;
			Rakhuruf[temp[l]].banyak = Rakhuruf[temp[l]].banyak - 1;
		}
		gotoxy(20,32);printf("Huruf yang bisa dipakai");
		a = 15;
		for(k = 0; k < banyak; k++){
			gotoxy(a, 33);	printf("[ %c ]", kata[k]);
			a = a + 6;
		}
	}
	hrftersedia();
}

// Fungsi untuk menginputkan bentuk kata yang ingin dibuat user lalu mengembalikkan nilainya
int bentuk() 
{
	clsperintah();
	int i, a, Pilihan;
	char Input;
	gotoxy(70,16);printf("Press Any Key to Continue");
	gotoxy(70,17);printf("Press ! To Random Letter");
	gotoxy(70,18); printf("Press ? To See The Number of Each Letter");
	Input = getch();
	fflush(stdin);
	a=14;
	for(i = 0; i < 3; i++){
		gotoxy(70,a);printf("                                                  ");	
		a++;
	}
	if(Input == '!' || Input =='?'){
	Perintah(Input);
	}
	gotoxy(65,22);printf("Select the form of the word you want to make\n");
	gotoxy(65,23);printf("1. Vertikal");
	gotoxy(65,24);printf("2. Horizontal");
	gotoxy(65,25);printf("Enter Your Choice: ");
	gotoxy(85,25);scanf("%d", &Pilihan);
	if(Pilihan != 1 && Pilihan != 2){
		printf("%c", bell);
		gotoxy(65,20);	printf("YOUR INPUT IS NOT CORRECT!!!");
		bentuk();
	}
	return Pilihan;
}

// Prosedur untuk mengkondisikan perintah yang mungkin terjadi
void Perintah(char Input) 
{
	int i, y,j,sama;
	char acak;
	if(Input == '?'){
		y = 11;
		for(i = 0; i < 27; i=i+3){
		gotoxy(124,y);printf("%c: %d   %c: %d   %c: %d", Rakhuruf[i].huruf, Rakhuruf[i].banyak, Rakhuruf[i+1].huruf, Rakhuruf[i+1].banyak, Rakhuruf[i+2].huruf, Rakhuruf[i+2].banyak);
		Sleep(200);
		y++;
		}
		gotoxy(124,10);printf("Press Any Key To Back");
		getch();
		gotoxy(124,10);printf("                                  ");
		y = 11;
			for(i = 0; i < 10; i++){
			gotoxy(124,y);printf("                                                 ");
			y++;
			}
			bentuk();
	}else if(Input == '!' ){
		for(i = 0; i < 7; i++){
			sama = 0;
			for(j = 0; j < 27 && sama == 0; j++){
				if(kata[i] == Rakhuruf[j].huruf){
					Rakhuruf[j].banyak++;
					sama = 1;
				}
			}
		}
		Acakhuruf();
		peek--;
		if(peek > 0){
			gotoxy(25,35);printf("Random Letter Chance %dx ", peek);
			Sleep(1000);
			gotoxy(25,35);printf("                                      ");
			bentuk();
		}else if(peek <= 0){
			gotoxy(25,35);printf("Random Chance Runs Out ");
			Sleep(1000);
			gotoxy(25,35);printf("                                      ");
		}
	}else if(Input == '#'){
		if(giliran == 0){
			one.menyerah = 1;
		}else{
			two.menyerah = 1;
		}
	}
}	

// Fungsi untuk menginputkan posisi baris huruf pertama lalu mengembalikkan nilainya
int chooseline() 
{
	int baris;
		if(game == 1){
			baris = 6;
		}else{
			gotoxy(65,22); printf("Enter the Position for The First Letter ");
			gotoxy(65,23);		printf("Box Row Position : ");
			gotoxy(84,23);		scanf("%d",&baris);
		}
		return baris;
}

// Fungsi untuk menginputkan posisi kolom huruf pertama lalu mengembalikkan nilainya
int chooseclm()
{
	int kolom;
		if(game == 1){
			kolom = 6;
		}else{
			gotoxy(65,24);		printf("Box Column Position : ");
			gotoxy(87,24);		scanf("%d",&kolom);
		}
	return kolom;
}

// Fungsi untuk Menentukan banyak huruf yang akan digunakan
int UseLetter()
{
	int bykhuruf;
	gotoxy(65,25);		printf("Enter The Number Of Letters That Will Form The Word: ");
	gotoxy(118,25);		scanf("%d", &bykhuruf);
	return bykhuruf;
}

// Fungsi untuk menentukan valid tidaknya posisi
int IsvalidPosition(int baris, int kolom, int bykhuruf, int BentukKata)
{
int i, j, tes1, tes2, panjang, valid;
	if (BentukKata == 1){ //Vertikal
		i = baris;
		j = kolom;
		if(Board[i][j].Letter.huruf != ' '){
			valid = 0;
			return valid;
		}
		i = baris;
		j = kolom;
		panjang = baris + bykhuruf;
		tes1 = 0;
		tes2 = 0;
		while(i < panjang && tes1 == 0 ){
			if(Board[i][j-1].Letter.huruf != ' '|| Board[i][j+1].Letter.huruf != ' ' ){
				tes1 = 1;;
			}
			i++;
		}
		i = baris + 1;
		j = kolom;
			while(i <= panjang && tes2 == 0){
				if(Board[i][j].Letter.huruf !=' '){
					tes2 = 1;
				}
				i++;
			}
		i = baris;
		j = kolom;
			if (tes1 == 1 || Board[i-1][j].Letter.huruf != ' '|| tes2 == 1 || Board[panjang][j].Letter.huruf!= ' '){
				valid = 1;
			}else{
				valid = 2;
			}
	}else{ //Horizontal
		i = baris;
		j = kolom;
		if(Board[i][j].Letter.huruf != ' '){
			valid = 0;
			return valid;
		}
		i = baris;
		j = kolom;
		panjang = kolom + bykhuruf;
		tes1 = 0;
		tes2 = 0;
			while(j < panjang && tes1 == 0 ){
				if(Board[i-1][j].Letter.huruf != ' '|| Board[i+1][j].Letter.huruf != ' '){
					tes1 = 1;
				}
				j++;
			}
		i = baris;
		j = kolom + 1;
			while(j <= panjang && tes2 == 0){
				if(Board[i][j].Letter.huruf !=' '){
					tes2 = 1;
				}
				j++;
			}
		i = baris;
		j = kolom;
			if (tes1 == 1 || Board[i][j-1].Letter.huruf != ' ' || tes2 == 1 || Board[i][j+1].Letter.huruf!=' '){
				valid = 1;
			}else{
				valid = 2;
			}
	}
	return valid;
}

// Fungsi untuk input kata secara vertikal dan mengembalikkan poin yang diperoleh 
int Vertikal(int baris, int kolom, int bykhuruf, int BentukKata)
{
	clsperintah();
	int a, b, c, i, j, k, l, m, n, banyak, beda, panjang, jumlah, poin, sama, total, count,barishasil, cek;
	int sec;
	int duration, acc = 0;
    char Input;
   	char temp[20]={0};
	char simpan[20]={0};
	char hasil[20]={0};
	char use[7]={0};
	jumlah = bykhuruf;
	i = baris;
	j = kolom;
	banyak = baris + bykhuruf;	
	l = 0;
	m = 0;
	c = 24;
		fflush(stdin);
	switch(level){
		case 1: sec = 30;break;
		case 2: sec = 20;break;
		case 3: sec = 10;break;
	}
	if (game != 1){
		gotoxy (65,20);printf("Enter The Letters Before The Time Runs Out !!!");
		gotoxy (72,21);printf("Enter [#] If You Want to Give Up");
	//	Sleep(2000);
	//	gotoxy (65,18);printf("                                                                   ");
		while (!_kbhit()) {
     	   duration = (clock()) / CLOCKS_PER_SEC;
       		if (duration >= acc) {
        		gotoxy(30,3);	printf("%d", acc); 
        		Sleep(1000);
       			gotoxy(30,3); printf("     ");
           		if (acc >= sec) break;
           			acc += 1;
       		}
		}  
		if (acc >= sec){
			poin = 0;
			printf("%c",bell);
			gotoxy(65,20);printf("TIME IS OVER");
			BackAllLetter();
			return poin;
		}
		while(jumlah > 0){
			if(Board[i][j].Letter.huruf != ' ' && i != baris){
				temp[l]= Board[i][j].Letter.huruf;
				i++;
				l++;
				banyak++;
			}else{
		//		gotoxy (72,21);printf("Enter [#] If You Want to Give Up");
				gotoxy(65,c);scanf("%c", &Input);
				fflush(stdin);
				c++;
	//			gotoxy (72,21);printf("                                           ");
				if(Input == '#'){
					Perintah(Input);
					BackAllLetter();
					poin = 0;
					return poin;
				}
				sama = 0;
				for (a =  0; a < 7 && sama == 0; a++){
					if(toupper(Input) == kata[a] ){
						sama = 1;
					}
				}
				b = m;
				beda = 1;
				while(b > 0){
					if(Input == use[b-1]){
						beda = 0;
						sama = 0;
					}
					b--;
				}
				if(beda == 1 && sama == 1){
					if(Iswordvalid(i, j, BentukKata, Input) == 1){
						temp[l]= Input;
						use[m]= Input;
						sama = 1;
						banyak++;
						l++;
						i++;
						m++;
						jumlah--;
					}else{
						BackAllLetter();
						poin = PoinSalah();
						return poin;
							}
				}else if(sama == 0){
					printf("%c", bell);
					gotoxy(75,20);printf("THERE IS NOT THAT LETTER !!!");	
					Sleep(2000);
					gotoxy (75,20);printf("                                                                   ");
				}
			}	
		}
		i = baris;
		j = kolom;
		panjang = baris+strlen(temp)-1;	
		if(Board[panjang+1][j].Letter.huruf != ' ' && Board[i-1][j].Letter.huruf !=' '){
			k = 0;
			n = 1;
			while(Board[i-n][j].Letter.huruf !=' '){
				simpan[k] = Board[i-n][j].Letter.huruf;
				k++;
				barishasil = i - n;
				n++;
			}
			total = strlen(simpan);
			k = 0;
			for(total -1; total > 0; total --){
   				hasil[k]= simpan[total-1];
   				k++;
				}
			strcat(hasil, temp);
			count = strlen(hasil); 
			n = 1;
			i = baris;
			j = kolom;
			panjang = baris+strlen(temp)-1;	
			while(Board[panjang+n][j].Letter.huruf != ' '){
				hasil[count] = Board[panjang+n][j].Letter.huruf;
				n++;
				count++;
			}
			gotoxy(75,20);printf("Type [>] to Submit  %s ", strupr(hasil));
			Input = getch();
			gotoxy(75,20);printf("                                        ");
			if(Input == '>'){
				if(CekKamus(hasil)==1){
					cek = 1;
					poin = skor(hasil,barishasil,kolom,bykhuruf,BentukKata);
					KamusBenar(barishasil,kolom,hasil,bykhuruf,BentukKata);
					game++;
				}else{
					cek = 0;
					KamusSalah();
					poin = PoinSalah();
				}
			}
		}else if(Board[i-1][j].Letter.huruf !=' '){
			n = 1;
			k = 0;
			while(Board[i-n][j].Letter.huruf !=' '){
				simpan[k] = Board[i-n][j].Letter.huruf;
				k++;
				barishasil = i - n;
				n++;
			}
			total = strlen(simpan);
			k = 0;
			for(total -1; total > 0; total --){
   				hasil[k]= simpan[total-1];
   				k++;
			}
			strcat(hasil, temp);
			gotoxy(75,20);printf("Type [>] to Submit  %s ", strupr(hasil));
			Input = getch();
			gotoxy(75,20);printf("                                                ");
			if(Input == '>'){
				if(CekKamus(hasil)==1){
					cek = 1;
					poin = skor(hasil,barishasil,kolom,bykhuruf,BentukKata);
					KamusBenar(barishasil,kolom,hasil,bykhuruf,BentukKata);
					game++;
				}else{
					cek = 0;
					KamusSalah();
					poin = PoinSalah();
				}
			}
		}else if(Board[panjang+1][j].Letter.huruf != ' '){
			n = 1;
			while(Board[panjang + n][j].Letter.huruf !=' '){
				temp[l] = Board[panjang+n][j].Letter.huruf;
				n++;
				l++;
			}
			gotoxy(75,20);printf("Type [>] to Submit  %s ", strupr(temp));
			Input = getch();
			gotoxy(75,20);printf("                                             ");
			if(Input == '>'){
				if(CekKamus(temp)==1){
					cek = 1;
					poin = skor(temp,baris,kolom,bykhuruf,BentukKata);
					KamusBenar(baris,kolom,temp,bykhuruf,BentukKata);
					game++;
				}else{
					cek = 0;
					KamusSalah();
					poin = PoinSalah();
				}
			}
		}else{
			gotoxy(75,20);printf("Type [>] to Submit  %s ", strupr(temp));
			Input = getch();
			gotoxy(75,20);printf("                                             ");
			fflush(stdin);
			if(Input == '>'){
				if(CekKamus(temp)==1){
					cek = 1;
					poin = skor(temp,baris,kolom,bykhuruf,BentukKata);
					KamusBenar(baris,kolom,temp,bykhuruf,BentukKata);
					game++;
				}else{
					cek = 0;
					KamusSalah();
					poin = PoinSalah();
				}
			}	
		}
	}else{
		i = baris;
		j = kolom;
		l = 0;
		m = 0;
		gotoxy (65,22);printf("Enter The Letters Before The Time Runs Out !!!");
		gotoxy (72,23);printf("Enter [#] If You Want to Give Up");
	//	Sleep(2000);
	//	gotoxy (65,21);printf("                                                                   ");
		while (!_kbhit()) {
   		    duration = (clock()) / CLOCKS_PER_SEC;
       			if (duration >= acc) {
        			gotoxy(30,3);	printf("%d", acc); 
        			Sleep(1000);
       				gotoxy(30,3); printf("     ");
           				if (acc >= sec) break;
            				acc += 1;
       					}
		}  
		if (acc >= sec){
			poin = 0;
			gotoxy(65,22);printf("TIME IS OVER");
			printf("%c",bell);
			BackAllLetter();
			return poin;
		}
		while(jumlah > 0){
		//	gotoxy (72,21);printf("Enter [#] If You Want to Give Up");
			gotoxy(65,c);scanf("%c", &Input);
			c++;
			fflush(stdin);
		//	gotoxy (72,21);printf("                                          ");
			if(Input == '#'){
				Perintah(Input);
				BackAllLetter();
				poin = 0;
				return poin;
			}
			sama = 0;
			for (a =  0; a < 7 && sama == 0; a++){
				if(toupper(Input) == kata[a] ){
					sama = 1;
				}
			}
			beda = 1;
			b = m;
			while(b > 0 ){
				if(Input == use[b-1]){
					beda = 0;
					sama = 0;
				}
				b--;
			}
			if(beda == 1 && sama == 1){
				temp[l]= Input;
				use[m]= Input;
				l++;
				m++;
				jumlah--;
			}
			if(sama == 0){
				gotoxy(75,20);printf("THERE IS NOT THAT LETTER");
				Sleep(2000);
				gotoxy(75,200);printf("                                 ");	
			}	
		}      
		gotoxy(75,20);printf("Type [>] to Submit  %s ", strupr(temp));
		Input = getch();
		fflush(stdin);
		gotoxy(75,20);printf("                                          ");
		if(Input == '>'){
			if(CekKamus(temp)==1){
				cek = 1;
				poin = skor(temp,baris,kolom,bykhuruf,BentukKata);
				KamusBenar(baris,kolom,temp,bykhuruf,BentukKata);
				game++;
			}else{
				cek = 0;
				KamusSalah();
				poin = PoinSalah();
			}
		}
	}
	if(cek == 1){
		BackLetterNotUse(use);
	}else{
		BackAllLetter();
	}
	return poin;
}

// Fungsi untuk input kata secara Horizontal dan mengembalikkan poin yang diperoleh 
int Horizontal(int baris, int kolom, int bykhuruf, int BentukKata)
{
	clsperintah();
	int a, b, c, i, j, k, l, m, n, banyak, beda, panjang, jumlah, poin, sama, total, count, kolomhasil, cek;
    int duration, acc = 0;
    int sec;
    char Input;
   	char temp[20]={0};
	char simpan[20]={0};
	char hasil[20]={0};
	char use[7]={0};
	jumlah = bykhuruf;
	i = baris;
	j = kolom;
	banyak = kolom + bykhuruf;	
	l = 0;
	m = 0;
	c = 65;
		switch(level){
		case 1: sec = 30;break;
		case 2: sec = 20;break;
		case 3: sec = 10;break;
	}
		fflush(stdin);
	if (game != 1){
		gotoxy (65,22);printf("Enter The Letters Before The Time Runs Out !!!");
		gotoxy (72,22);printf("Enter [#] If You Want to Give Up");
	//	Sleep(200);
	//	gotoxy (65,18);printf("                                                                   ");
		while (!_kbhit()) {
   		    duration = (clock()) / CLOCKS_PER_SEC;
       			if (duration >= acc) {
        			gotoxy(30,3);	printf("%d", acc); 
        			Sleep(1000);
       				gotoxy(30,3); printf("     ");
           				if (acc >= sec) break;
            				acc += 1;
       					}
		}  
		if (acc >= sec){
			poin = 0;
			gotoxy(65,20);printf("TIME IS OVER");
			printf("%c",bell);
			BackAllLetter();
			return poin;
		}
		while(jumlah > 0){
			if(Board[i][j].Letter.huruf != ' ' && j != kolom){
				temp[l]= Board[i][j].Letter.huruf;
				j++;
				l++;
				banyak++;
			}else{
				gotoxy(c,24);scanf("%c", &Input);
			//	gotoxy (75,21);printf("                                     ");
				fflush(stdin);
				c++;
				if(Input == '#'){
					Perintah(Input);
					BackAllLetter();
					poin = 0;
					return poin;	
				}
				sama = 0;
				for (a =  0; a < 7 && sama == 0; a++){
					if(toupper(Input) == kata[a] ){
						sama = 1;
					}
				}
				b = m;
				beda = 1;
				while(b > 0){
					if(Input == use[b-1]){
						beda = 0;
						sama = 0;
					}
					b--;
				}
				if(sama == 1 && beda == 1){
					if(Iswordvalid(i, j, BentukKata, Input) == 1){
				    	temp[l]= Input;
						use[m]= Input;
						sama = 1;
						banyak++;
						l++;
						j++;
						m++;
						jumlah--;
					}else{
						poin = PoinSalah();
						BackAllLetter();
						return poin;
					}         
				}else if(sama == 0){
					printf("%c", bell);
					gotoxy(75,20);printf("There Is No That Letter");
					Sleep(2000);
					gotoxy(75,20);printf("                              ");	
				}
			}	
		}
		i = baris;
		j = kolom;
		panjang = kolom+strlen(temp)-1;	
		if(Board[i][panjang+1].Letter.huruf != ' ' && Board[i][j-1].Letter.huruf !=' '){
			k = 0;
			n = 1;
			while(Board[i][j-n].Letter.huruf !=' '){
				simpan[k] = Board[i][j-n].Letter.huruf;
				k++;
				kolomhasil = j - n;
				n++;
			}
			total = strlen(simpan);
			k = 0;
			for(total-1; total > 0; total --){
   				hasil[k]= simpan[total-1];
   				k++;
			}
			strcat(hasil, temp);
			count = strlen(hasil); 
			n = 1;
			i = baris;
			j = kolom;
			panjang = kolom+strlen(temp)-1;	
			while(Board[i][panjang+n].Letter.huruf != ' '){
				hasil[count] = Board[i][panjang+n].Letter.huruf;
				n++;
				count++;
			}
			gotoxy(75,20);printf("Type [>] to Submit  %s ", strupr(hasil));
			Input = getch();
			gotoxy(75,20);printf("                                               ");
			if(Input == '>'){
				if(CekKamus(hasil)==1){
					cek = 1;
					poin = skor(hasil,baris,kolomhasil,bykhuruf,BentukKata);
					KamusBenar(baris,kolomhasil,hasil,bykhuruf,BentukKata);
					game++;
				}else{
					cek = 0;
					KamusSalah();
					if(level == 3){
						poin = -5;
					}else{
						poin = 0;
					}
				} 
			}
		}else if(Board[i][j-1].Letter.huruf !=' '){
			n = 1;
			k = 0;
			while(Board[i][j-n].Letter.huruf !=' '){
				simpan[k] = Board[i][j-n].Letter.huruf;
				k++;
				kolomhasil = j-n;
				n++;
			}
			total = strlen(simpan);
			k = 0;
   			for(total -1; total > 0; total --){
   				hasil[k]= simpan[total-1];
   				k++;
			}
			strcat(hasil, temp);
			gotoxy(75,20);printf("Type [>] to Submit  %s ", strupr(hasil));
			Input = getch();
			gotoxy(75,20);printf("                                             ");
			if(Input == '>'){
				if(CekKamus(hasil)==1){
					cek = 1;
					poin = skor(hasil,baris,kolomhasil,bykhuruf,BentukKata);
					KamusBenar(baris,kolomhasil,hasil,bykhuruf,BentukKata);
					game++;
				}else{
					cek = 0;
					KamusSalah();
					poin = PoinSalah();	
				}   
			}
		}else if(Board[i][panjang+1].Letter.huruf != ' '){
			n = 1;
			while(Board[i][panjang+n].Letter.huruf !=' '){
				temp[l] = Board[i][panjang+n].Letter.huruf;
				n++;
				l++;
			}
			gotoxy(75,20);printf("Type [>] to Submit  %s ", strupr(temp));
			Input = getch();
			gotoxy(75,20);printf("                                             ");
			if(Input == '>'){ 
				if(CekKamus(temp)==1){
					cek = 1;
					poin = skor(temp,baris,kolom,bykhuruf,BentukKata);
					KamusBenar(baris,kolom,temp,bykhuruf,BentukKata);
					game++;
				}else{
					cek = 0;
					KamusSalah();
					poin = PoinSalah();
				}  
			}
		}else{
				gotoxy(75,20);printf("Type [>] to Submit  %s ", strupr(temp));
				Input = getch();
				fflush(stdin);
				gotoxy(75,20);printf("                                            ");
				if(Input == '>'){
					if(CekKamus(temp)==1){
						cek = 1;
						poin = skor(temp,baris,kolom,bykhuruf,BentukKata);
						KamusBenar(baris,kolom,temp,bykhuruf,BentukKata);
						game++;
					}else{
						cek = 0;
						KamusSalah();
						poin = PoinSalah();
					}  
				}	
			}
	}else{
		i = baris;
		j = kolom;
		l = 0;
		m = 0;
		c = 65;
		gotoxy (65,22);printf("Enter the letters before the time runs out !!!");
		gotoxy (72,23);printf("Enter [#] If You Want to Give Up");
		//Sleep(200);
	//	gotoxy (65,21);printf("                                                                   ");
		while (!_kbhit()) {
    	    duration = (clock()) / CLOCKS_PER_SEC;
       		if (duration >= acc) {
        	gotoxy(30,3);	printf("%d", acc); 
        	Sleep(1000);
       		gotoxy(30,3); printf("     ");
           		if (acc >= sec) break;
            		acc += 1;
       		}
	   }  
	    if (acc >= sec){
			poin = 0;
			gotoxy(70,18);printf("TIME IS OVER");
			printf("%c",bell);
			BackAllLetter();
			return poin;
		}
		while(jumlah > 0){
		//	gotoxy (75,21);printf("Enter [#] If You Want to Give Up");
			gotoxy(c,24);scanf("%c", &Input);
			fflush(stdin);
	//		gotoxy (75,21);printf("                                                ");
			c++;
				//	x = 10 + j*5;
				//	y = 10 + i*2;
			if(Input == '#'){
				Perintah(Input);
				BackAllLetter();
				poin = 0;
				return poin;
			}
			sama = 0;
			for (a =  0; a < 7 && sama == 0; a++){
				if(toupper(Input) == kata[a] ){
					sama = 1;
				}
			}
			beda = 1;
			b = m;
			while(b > 0 ){
				if(Input == use[b-1]){
					beda = 0;
					sama = 0;
				}
				b--;
			}
			if(sama == 1 && beda == 1){
				temp[l]= Input;
				use[m]= Input;
				l++;
				m++;
				jumlah--;
			}else if(sama == 0){
				printf("%c", bell);
				gotoxy(75,20);printf("There Is No That Letter");
				Sleep(2000);
				gotoxy(75,20);printf("                                      ");	
			}	
		}     
		gotoxy(75,20);printf("type [>] to submit  %s ", temp);
		Input = getch();
		fflush(stdin);
		gotoxy(75,20);printf("                                                ");
		if(Input == '>'){
			if(CekKamus(temp)==1){
				cek = 1;
				poin = skor(temp,baris,kolom,bykhuruf,BentukKata);
				KamusBenar(baris,kolom,temp,bykhuruf,BentukKata);
				game++;
			}else{
				cek = 0;
				KamusSalah();
				poin = PoinSalah();
			}  
		}
	}
	if(cek == 1){
		BackLetterNotUse(use);
	}else{
		BackAllLetter();
	}
	return poin;
}

int PoinSalah(){
	int poin;
	switch(level){
		case 1: poin = 0; break;
		case 2: poin = -5; break;
		case 3: poin = -10; break;
	}
	return poin;
}

// Fungsi untuk memeriksa kata yang tercipta dari huruf yang berdekatan dengan Input
int Iswordvalid(int baris, int kolom, int BentukKata, char Input )
{
	int i,j,l,n,total,valid;
	int up,down,left,right, doubleV, doubleH;
	char atas[20]={0};
	char bawah[20]={0};
	char kanan[20]={0};
	char kiri[20]={0};
	char temp[20]={0};
	j = kolom;
	up = 1;
	down = 1;
	left = 1;
	right = 1;
	doubleV = 1;
	doubleH = 1;
	i = baris;
	j = kolom;
	if(BentukKata == 2){  	
		if(	Board[i+1][j].Letter.huruf!=' ' && Board[i-1][j].Letter.huruf!=' '){
			l = 0;
			bawah[l]=Input;
			n = 1;
			while(Board[i+n][j].Letter.huruf != ' '){
				l++;
				bawah[l]= Board[i+n][j].Letter.huruf;
				n++;
			}
			l = 0;
			n = 1;
			while(Board[i-n][j].Letter.huruf != ' '){
				temp[l]= Board[i-n][j].Letter.huruf;
				n++;
				l++;
			}
			total = strlen(temp);
			l = 0;
			for (total - 1; total > 0; total--){
   				atas[l] = temp[total-1];
   				l++;
			}
			strcat(atas,bawah);
			if (CekKamus(atas)!=1){
				printf("%c", bell);
				gotoxy(70, 20);printf("THE WORD %s IS NOT IN THE DICTIONARY ", strupr(atas));
				Sleep(2000);
				doubleH = 0;
				gotoxy(70, 20); printf("                                                     ");
			}
		}else if(Board[i+1][j].Letter.huruf!=' '){
			l = 0;
			bawah[l]=Input;
			n = 1;
			while(Board[i+n][j].Letter.huruf != ' '){
				l++;
				bawah[l]= Board[i+n][j].Letter.huruf;
				n++;
			}
			if (CekKamus(bawah)!=1){
				printf("%c", bell);
				gotoxy(70, 20);printf("THE WORD %s IS NOT IN THE DICTIONARY ", strupr(bawah));
				Sleep(2000);
				down = 0;
				gotoxy(70, 20); printf("                                               ");
			}
		}else if(Board[i-1][j].Letter.huruf!=' '){
			l = 0;
			temp[l]=Input;
			n = 1;
			while(Board[i-n][j].Letter.huruf != ' '){
				l++;
				temp[l]= Board[i-n][j].Letter.huruf;
				n++;
			}
			total = strlen(temp);
			l = 0;
			for (total - 1; total > 0; total--){
   				atas[l] = temp[total-1];
   				l++;
			}
			if (CekKamus(atas)!=1){
				printf("%c", bell);
				gotoxy(70, 20);printf("THE WORD %s IS NOT IN THE DICTIONARY ", strupr(atas));
				Sleep(2000);
				up = 0;
				gotoxy(70, 20); printf("                                                 ");
			}
		}
		if(up == 0 || down == 0 || doubleH == 0){
			valid = 0;
		}else{
			valid = 1;
		}
		if(valid == 0){
				BackAllLetter();
		}
	}else{
		if(Board[i][j+1].Letter.huruf!=' ' && Board[i][j-1].Letter.huruf!=' ' ){
			l = 0;
			kanan[l]=Input;
			n = 1;
			while(Board[i][j+n].Letter.huruf != ' '){
				l++;
				kanan[l]= Board[i][j+n].Letter.huruf;
				n++;
			}
			n = 1;
			l = 0;
			while(Board[i][j-n].Letter.huruf != ' '){
				temp[l]= Board[i][j-n].Letter.huruf;
				n++;
				l++;
			}
				total = strlen(temp);
				l = 0;
				for (total-1; total > 0; total--){
   					kiri[l] = temp[total-1];
   					l++;
				}
				strcat(kiri,kanan);
				if (CekKamus(kiri)!=1){
					printf("%c", bell);
					gotoxy(70, 20);printf("THE WORD %s IS NOT IN THE DICTIONARY ", strupr(kiri));
					Sleep(2000);
					doubleV = 0;
					gotoxy(70, 20); printf("                                                   ");
				}
		}else if(Board[i][j+1].Letter.huruf!=' '){
		l = 0;
		kanan[l]=Input;
		n = 1;
			while(Board[i][j+n].Letter.huruf != ' '){
				l++;
				kanan[l]= Board[i][j+n].Letter.huruf;
				n++;
			}
			if (CekKamus(kanan)!=1){
				printf("%c", bell);
				gotoxy(70, 20);printf("THE WORD %s IS NOT IN THE DICTIONARY ", strupr(kanan));
				Sleep(2000);
				right = 0;
				gotoxy(70, 20); printf("                                                ");
			}
		}else if(Board[i][j-1].Letter.huruf!=' '){
		//	temp[20]={0};
			l = 0;
			temp[l]=Input;
			n = 1;
				while(Board[i][j-n].Letter.huruf != ' '){
					l++;
					temp[l]= Board[i][j-n].Letter.huruf;
					n++;
				}
				total = strlen(temp);
				l = 0;
				for (total-1; total > 0; total--){
   					kiri[l] = temp[total-1];
   					l++;
				}
				if (CekKamus(kiri)!=1){
					printf("%c", bell);
					gotoxy(70, 20);printf("THE WORD %s IS NOT IN THE DICTIONARY ", strupr(kiri));
					Sleep(2000);
					left = 0;
					gotoxy(70, 20); printf("                                                     ");
				}
			}
		if(right == 0 || left == 0 || doubleV == 0){
			valid = 0;
		}else{
			valid = 1;
		}
		if(valid == 0){
			BackAllLetter();
		}
	}
return valid;
}

// Fungsi untuk mengecek kesesuaian kata dengan kamus
int CekKamus(char input[])
{
	char periksa[20];
	strcpy(periksa,strlwr(input));	
	FILE *in, *out;
	char isi[30];
	int ada,panjang1, panjang2;
    ada = 0;
    in = fopen("kamus2.txt","r");
    if(in == NULL){
    	gotoxy(70,20);printf("File Can't Be Read!!!");
    }else{
    	out= fopen("teks.txt", "w");
    	while(!feof(in) && ada == 0){
    		fscanf(in,"%s",&isi);
    		panjang1 = strlen(isi);
    		panjang2 = strlen(periksa);
    		if(panjang1 == panjang2){
    			if(strcmp(periksa,isi)== 0){
    				ada = 1;
				}
    			
			}
		}
	}
	fclose(in);
	return ada;
}

// Prosedur untuk menampilkan kata pada papan jika kata tersebut ada dalam kamus
void KamusBenar(int baris, int kolom, char hasil[], int bykhuruf, int BentukKata)
{
int i, j,l,banyak,x,y;
char letter[20];
strcpy(letter,hasil);	
	if(BentukKata == 1){
		i = baris;
		j = kolom;
		l = 0;
		banyak = strlen(letter);
		while(banyak > 0){
				x = 5 + j*5;
				y = 8 + i*2;
			if(Board[i][j].Letter.huruf == ' '){
				Board[i][j].Letter.huruf = letter[l];
				gotoxy(x,y);printf("%c", toupper(Board[i][j].Letter.huruf));
			}
				i++;
				l++;
				banyak--;
		}
	}else{
		i = baris;
		j = kolom;
		l = 0;
		banyak = strlen(letter);
		while(banyak > 0){
				x = 5 + j*5;
				y = 8 + i*2;
			if(Board[i][j].Letter.huruf == ' '){
				Board[i][j].Letter.huruf = letter[l];
				gotoxy(x,y);printf("%c", toupper(Board[i][j].Letter.huruf));
			}
				l++;
				j++;
				banyak--;
		}
	}
}

// Prosedur untuk menampilkan pemberitauan kalau kata tidaka ada dalam kamus
void KamusSalah()
{
	printf("%c", bell);	
	gotoxy(65,20);printf("SO SAD IT'S' NOT IN THE DICTIONARY ");
	Sleep(3000);
	gotoxy(65,20);printf("                                       ");					
}

// Fungsi untuk menghitung poin dan  mengembalikkan poin yang diperoleh 
int skor(char temp[], int baris, int kolom, int bykhuruf, int BentukKata)
{
	int i,j,k,l,jumlah, panjang, sama, total;
	char simpan[20];
	strcpy(simpan,strupr(temp));
	jumlah = 0;
	panjang = 0;
		k = baris;
		l = kolom;
		panjang = strlen(simpan);
		if(BentukKata == 1 && game!= 1){
		total = baris+strlen(simpan);
		for(i = 0; i < panjang; i++ ){
			sama = 0;
			for(j = 0; j < 27 && sama == 0; j++){
				if(temp[i] == Rakhuruf[j].huruf){
					sama == 1;
					if(Board[k][l].DW == 1){
					Rakhuruf[j].bobot = Rakhuruf[j].bobot*2;
				}else if (Board[k][l].TW == 1){
					Rakhuruf[j].bobot = Rakhuruf[j].bobot*3;
				}
				jumlah = jumlah + Rakhuruf[j].bobot;
				k++;
			}
		}
	}
		for(k = baris; k < total; k++ ){	
			if(Board[k][l].DL == 1 || Board[k][l].bintang == 1){
					jumlah = jumlah * 2;
				}else if (Board[k][l].TL == 1){
					jumlah = jumlah * 3;
				}
			
			}
		}else if(BentukKata == 2 && game != 1){
				total = kolom+strlen(simpan);			//Horizontal
				k = baris;
				l = kolom;
				panjang = strlen(temp);
				for(i = 0; i < panjang; i++ ){
					sama = 0;
					for(j = 0; j < 27 && sama == 0; j++){
						if(temp[i] == Rakhuruf[j].huruf){
							sama = 1;
							if(Board[k][l].DW == 1){
								Rakhuruf[j].bobot = Rakhuruf[j].bobot*2;
							}else if (Board[k][l].TW == 1){
								Rakhuruf[j].bobot = Rakhuruf[j].bobot*3;
							}
							jumlah = jumlah + Rakhuruf[j].bobot;
							l++;
						}
					}
				}
				for(l = kolom; l < total; l++ ){	
					if(Board[k][l].DL == 1 || Board[k][l].bintang == 1){
					jumlah = jumlah * 2;
				}else if (Board[k][l].TL == 1){
					jumlah = jumlah * 3;
				}
			}
		}else if(game == 1){
				for(i = 0; i < panjang; i++ ){
					sama = 0;
					for(j = 0; j < 27 && sama== 0; j++){
						if(temp[i] == Rakhuruf[j].huruf){
							sama = 1;
							if(Board[k][l].DW == 1){
								Rakhuruf[j].bobot = Rakhuruf[j].bobot*2;
							}else if (Board[k][l].TW == 1){
								Rakhuruf[j].bobot = Rakhuruf[j].bobot*3;
							}
							jumlah = jumlah + 	Rakhuruf[j].bobot;
							l++;
						}
					}
				}
				jumlah = jumlah * 2;
			}
	return jumlah;
}
		
// Prosedur untuk mengembalikkan huruf yang dipakai
void BackLetterNotUse(char temp[])
{
int jumlah, k,l, a, banyak;
	jumlah = strlen(temp);
	for(k = 0; k < 7; k++){
		banyak = 0;
		for(a = 0; a < jumlah ; a++){
			if(kata[k]!= temp[a]){
				banyak++;
			}
		}
		if(banyak == jumlah){
			for(l = 0; l<27;l++){
				if(Rakhuruf[l].huruf==kata[k]){
					Rakhuruf[l].banyak = Rakhuruf[l].banyak + 1;
						break;
				}
			}
		}
	}
	hrftersedia();	
}

//Prosedur Mengembalikkan kata jika kata salah
void BackAllLetter()
{
int i,j;
	for(i = 0; i< 7; i++){
		for(j = 0; j<27; j++){
			if(Rakhuruf[j].huruf==kata[i]){
				Rakhuruf[j].banyak = Rakhuruf[j].banyak + 1;
				break;
			}
		}
	}
	hrftersedia();	
}


void playerGame()
{
	KondisiPapan();
	penampilanPermainan();
	int BentukKata, baris, kolom, bykhuruf;
	int p =-1;
	int Poin;
	one.skor = 0;
	two.skor = 0;
	one.menyerah = 0;
	two.menyerah = 0;
	do{
	giliran = (p + 1) % 2;
		if(giliran == 0){
		//	p++;
			gotoxy(82,14);	printf("                              ");
			gotoxy(82,14);	printf("TURN FOR %s",one.nama);
			switch (level){
				case 1: peek = 5; break;
				case 2: peek = 4; break;
				case 3: peek = 3; break;
			}
			Poin = 0;
			clsperintah();
			Acakhuruf();
			BentukKata = bentuk();
			clsperintah();
			baris = chooseline();
			kolom = chooseclm();
			bykhuruf = UseLetter();
			if(game > 1 ){
				if(BentukKata == 1){
					if(IsvalidPosition(baris,kolom, bykhuruf, BentukKata) == 1){
						Poin = Vertikal(baris,kolom,bykhuruf,BentukKata);
							p++;
						if(two.menyerah == 1){
							p--;
						}
					}else if (IsvalidPosition(baris,kolom, bykhuruf, BentukKata) == 0){
						printf("%c", bell);
						gotoxy(70,20);printf("Find an Empty Box");
						Sleep(1000);
						gotoxy(70,20);printf("                      ");	
						BackAllLetter();
					//	giliran--;
					//	Poin = 0;
					}else{
						printf("%c", bell);
						gotoxy(70,20);printf("Letters Must be Connected");
						Sleep(1000);
						gotoxy(70,20);printf("                            ");
						BackAllLetter();
					//	giliran--;
					//	Poin = 0;
					}
			}else{
				if(IsvalidPosition(baris,kolom, bykhuruf, BentukKata) == 1){
					Poin = Horizontal(baris,kolom,bykhuruf,BentukKata);
					p++;
					if(two.menyerah == 1){
						p--;
					}
				}else if (IsvalidPosition(baris,kolom, bykhuruf, BentukKata) == 0){
					printf("%c", bell);
					gotoxy(70,20);printf("Find an Empty Box");
					Sleep(1000);
					gotoxy(70,20);printf("                         ");	
					BackAllLetter();
				//	giliran--;
				}else{
					printf("%c", bell);
					gotoxy(70,20);printf("Letters Must be Connected");
					Sleep(1000);
					gotoxy(70,20);printf("                              ");
						BackAllLetter();
					}
				}
		}else{
			p++;
				if(BentukKata == 1){
					Poin = Vertikal(baris,kolom,bykhuruf,BentukKata);
				}else{
					Poin = Horizontal(baris,kolom,bykhuruf,BentukKata);
				}
		}
		one.skor = one.skor + Poin;
		gotoxy(8,6); printf("Score: %d",one.skor );
		GameOver();
	}else{
	//	giliran++;
		gotoxy(82,14);	printf("                    ");
		gotoxy(82,14);	printf("TURN FOR %s",two.nama);
		switch (level){
			case 1: peek = 5; break;
			case 2: peek = 4; break;
			case 3: peek = 3; break;
		}
		Poin = 0;
		clsperintah();
		Acakhuruf();
		BentukKata = bentuk();
		clsperintah();
		baris = chooseline();
		kolom = chooseclm();
		bykhuruf = UseLetter();
		if(game > 1 ){
			if(BentukKata == 1){
				if(IsvalidPosition(baris,kolom, bykhuruf, BentukKata) == 1){
					Poin = Vertikal(baris,kolom,bykhuruf,BentukKata);
					p++;
					if(two.menyerah == 1){
						p--;
					}
				}else if (IsvalidPosition(baris,kolom, bykhuruf, BentukKata) == 0){
					printf("%c", bell);
					gotoxy(70,20);printf("Find an Empty Box");
					Sleep(1000);
					gotoxy(70,20);printf("                      ");	
					BackAllLetter();
				}else{
					printf("%c", bell);
					gotoxy(70,20);printf("Letters Must be Connected");
					Sleep(1000);
					gotoxy(70,20);printf("                             ");
					BackAllLetter();
					}
			}else{
				if(IsvalidPosition(baris,kolom, bykhuruf, BentukKata) == 1){
					Poin = Horizontal(baris,kolom,bykhuruf,BentukKata);
					p++;
					if(one.menyerah == 1){
						p--;
					}
				}else if (IsvalidPosition(baris,kolom, bykhuruf, BentukKata) == 0){
					printf("%c", bell);
					gotoxy(70,20);printf("Find an Empty Box");
					Sleep(1000);
					gotoxy(70,20);printf("                      ");	
				}else{
					printf("%c", bell);
					gotoxy(70,20);printf("Letters Must be Connected");
					Sleep(1000);
					gotoxy(70,20);printf("                             ");
					BackAllLetter();
					}
				}
		}else{
			p++;
				if(BentukKata == 1){
					Poin = Vertikal(baris,kolom,bykhuruf,BentukKata);
				}else{
					Poin = Horizontal(baris,kolom,bykhuruf,BentukKata);
				}
		}
		two.skor = two.skor + Poin;
		gotoxy(45,6); printf("Score: %d",two.skor );
		GameOver();
	}
	}while(game > 0);
	writeData();
	showWin();
}



void clsperintah()
{
  for (int i = 0; i < 23; i++)
  {
    gotoxy(65, 13+i);
    printf("                                                                                     ");
  }
}

/*____________________________________________ Game Berakhir ____________________________________________ */

int checkWin(){
	int pemenang;
	if(one.skor > two.skor){
		pemenang = 1;
	}else{
		pemenang = 2;
	}
	return pemenang;
}

void GameOver(){
int i, j;
	for (i = 0; i < 27; i++){
		if(jmlhrf == 0){
			game = 0;
		}
	}
	if(one.menyerah == 1 && two.menyerah == 1){
		game = 0;
	}
}

void showWin(){
	system("cls");
	if(checkWin()==1){
		printf("%s\n", one.nama);
		printf(" SELAMAT ANDA MENANG \n");
		printf(" jangan sombong ya ! \n");
		printf(" Tekan enter untuk ke menu utama ");getch();
	}else{
		printf("%s\n", two.nama);
		printf(" SELAMAT ANDA MENANG \n");
		printf(" jangan sombong ya ! \n");
		printf(" Tekan enter untuk ke menu utama ");getch();
	}
}

void writeData(){
	/* Memindahkan data pemain ke data highscore */
	if(checkWin() ==1){
		strcpy(data.name,one.nama);
		data.skor = one.skor ;
	}else{
		strcpy(data.name,two.nama);
		data.skor = two.skor ;
	}
	FILE *fp ;
	/* Tulis data ke dalam file */
	switch(level){
		case 1:
			fp = fopen(HIGHSCORE_1, "ab");
			fwrite(&data, sizeof(HighscoreData), 1, fp);
			fclose(fp);
		break;
		case 2:
			fp = fopen(HIGHSCORE_2, "ab");
			fwrite(&data, sizeof(HighscoreData), 1, fp);
			fclose(fp);
		break;
		case 3:
			fp = fopen(HIGHSCORE_3, "ab");
			fwrite(&data, sizeof(HighscoreData), 1, fp);
			fclose(fp);
		break;
	}
}

int GetData(){
	int N = 0;
	FILE *fp;
	switch(level){
		case 1: 
			fp = fopen(HIGHSCORE_1, "rb");
			while ( fread(&list[N], sizeof(HighscoreData), 1, fp ) == 1 ) N++;
			fclose(fp);
			return N;
		break;
		case 2:
			fp = fopen(HIGHSCORE_2, "rb");
			while ( fread(&list[N], sizeof(HighscoreData), 1, fp ) == 1 ) N++;
			fclose(fp);
			return N;
		break;
		case 3:
			fp = fopen(HIGHSCORE_2, "rb");
			while ( fread(&list[N], sizeof(HighscoreData), 1, fp ) == 1 ) N++;
			fclose(fp);
			return N;
		break;
}
}


void sortHighscore(int N ){
	int i, j ;
	for ( i = 0 ; i < N-1 ; i++ ){
		for ( j = i+1 ; j < N ; j++){
			if(list[j].skor < list[i].skor){
				swap(i,j);
			}
		}
	}
}

void swap(int i, int j){
	temp = list[j] ;
	list[j] = list[i];
	list[i] = temp ;
}

void highscore(){
	int i,N;
	PilihLevel();
	N = GetData();
	system("cls");
	sortHighscore(N);
		for ( i = 0 ; i < N ; i++ ){
			printf("%-20s ",list[i].name);
			printf("\t");
			printf("%d",list[i].skor);
			printf("\t\t");
			printf("\n");
		}
}







/* _____________________________________________ Fungsi Utama ___________________________________________ */
int main(){
	int end;
	system("Color 70");
	end=pilihanmenu();
/*	int i, j, end;
	char ulang;
	loading();
	/*while(end!=1)				//game akan terus berlanjut selama end tidak sama dengan 1
	{
		end=pilihanmenu();
	}
	pilihanmenu();
		int giliran = 0;
	int p;
//	Input = getch();
	//if(Input == '<'|| Input == '!' || Input == '?' || Input == 14 || Input == 15){
		//perintah();
//	}
/*	int sama = 1;
	for( i = 0; i < 11; i++){
		for( j = 0; j < 11; j++){
			if(Board[i][j].Letter.huruf == ' '){
				sama = 0;
			}
		}
	}*/
	
	//while(waktuMain != 0 || Input != 14 || Input != 15 || sama = 1 ){
	//	giliran =  p % 2 + 1;
	//	if(giliran == 1){
	//	gotoxy(65,18);printf("\tTURN FOR %s", one.nama);
	//	Sleep(1000);
//		bentuk();
//	}else{
//		gotoxy(65,18);printf("\tTURN FOR %s", two.nama);
//	Permainan();
//	printf("%d", level);
//getch();
//	return 0;


}

	

