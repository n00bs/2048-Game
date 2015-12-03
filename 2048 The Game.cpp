/*
	CHANGELOG
   
   FIXES
   	-Need to fix chkmoves. [Solved]
      -Need to fix colour issue. [Solved]
   ENHANCEMENTS
      -Beautification required,I guess. [Accomplished to some extent]
      -Fixed the colour function
      -Centralised the board
      -Tweak the theme a little
      -Fixed issue for random number generation even if no merges or
                 movement of non-zero number occurs.
   	-Fixed the logical error in movecount when it increments the value,
      			 despite the user comitting an illegal move
	 -Issue that 8 4 4 0 becomes 0 0 0 16 is now fixed and outcomes with
                 0 0 8 8.All functions i.e moveup() , movedown() , moveleft()
                 and moveright() have been fixed by modification in the
                 current code
     -Resolved the issue faced by all move functions when the number
      			  appears in the form of : 2x 2x x
*/
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

int grid[4][4];
int movecount;
int score = 0, actime = 0, choice = 0;
struct strin
{
	char word[10];
};
strin text[3] = {{"Start"} ,{" Help"},{" Exit"}};
void highlight(int high)
{

	for(int x=0;x<3;x++)
   {
      if(x==high)
      {
         textbackground(11);
   		gotoxy(37,10+x);
      		cprintf(" %-5s ",text[x].word);
      }
      else
      {
      	textbackground(0);
         gotoxy(37,10+x);
         	cprintf(" %-5s ",text[x].word);
      }
   }
}
void board()
{
/*
	Creates the board - is invoked in display function
*/
   //For horizontal lines :-
   for(int i = 0 ; i <= 4 ; i++)
   {
   	gotoxy(20,2+4*i);
      cout << char(197);               //char(197) is used instead of plus sign to produce continuous line
   	for(int x = 1 ; x <= 4 ; x++)
      {
      	for(int j = 1 ; j <= 8 ; j++)
      		cout << char(196);         //char(196) is used instead of hyphen to produce continuous line
         cout << char(197);            //char(197) is used instead of plus sign to produce continuous line
      }
      cout << "\n\n\n\n";
   }
   //For vertical lines :-
	for(int k = 0 ; k < 16 ; k++)
   {
   	gotoxy(20,2+k);
   	if(k % 4 != 0)
   		for(int y = 1 ; y <= 5 ; y++)
      		printf("%-9c", char(179)); //char(179) is used instead of pipe character because it produces a continuous line
      cout << endl;
   }
}

void display()
{
   board();                //To draw the board

	for(int y = 0 ; y < 4 ; y++)
   {
   	gotoxy(20 ,3 + 4*y);
      int c = 0;
      for(int x = 0 ; x < 4 ; x++, c++)
      {

   		if(grid[x][y] != 0)
      	{
         	if(grid[x][y] > 2048)
            {
            	textbackground(14);
               textcolor(4);
               cout << char(179);
               gotoxy(20 + 9*c + 1, 4*y + 3);
               cprintf("        \n");
               gotoxy(20 + 9*c + 1, 4*y + 4);
            	cprintf("%5i   ", grid[x][y]);
               gotoxy(20 + 9*c + 1, 4*y + 5);
               cprintf("        \n");
            }
            else
            {
            	textcolor(15);
            	textbackground(int(log(grid[x][y])/log(2))+1);
               if(grid[x][y] == 128)
               	textbackground(13);
               if(grid[x][y] == 256)
               	textbackground(12);
               /*
               	Makes sure each power of 2 (eg. 2,4,8,16,etc.) gets a unique colour
                  This is because the stuff inside the parenthesis acts like log to
                  the base 2
            	*/
               cout << char(179);
               gotoxy(20 + 9*c + 1, 4*y + 3);
            	cprintf("        \n");
               gotoxy(20 + 9*c + 1, 4*y + 4);
            	cprintf("%5i   ", grid[x][y]);
               gotoxy(20 + 9*c + 1, 4*y + 5);
               cprintf("        \n");
            }

      	}
         else
         {
         	textcolor(0);
            textbackground(0);
            cout << char(179);
            gotoxy(20 + 9*c + 1, 4*y + 3);
         	cprintf("        \n");
            gotoxy(20 + 9*c + 1, 4*y + 4);
            cprintf("%5i   ", grid[x][y]);
            gotoxy(20 + 9*c + 1, 4*y + 5);
            cprintf("        \n");
         }

      }
   }
}
/*
	-Function needs to be edited so that,
   even in a full grid, available moves are checked
   -Added support for full grid check, returns 2 if full grid
   has merges available
*/

int chkmoves()
{
	int p=0;
   for(int x = 0 ; x < 4 && p==0 ; x++)
   {
   	for(int y = 0 ; y < 4 ; y++)
      {
      	if(grid[x][y] == 0)
         	p=1;
      }
   }
   if(p == 1)
   {
   	return p;
   }
   else
   {
   	for(int x = 0 ; x < 3 && p==0 ; x++)
      {
      	for(int y = 0 ; y < 4 ; y++)
         {
         	if(grid[x][y] == grid[x+1][y])
            	p=2;
         }
      }
      for(int y = 0 ; y < 3 && p==0 ; y++)
      {
      	for(int x = 0 ; x < 4 ; x++)
         {
         	if(grid[x][y] == grid[x][y+1])
            	p=2;
         }
      }
   	return p;
   }
}
int genrandomno()
{
   int p= chkmoves();
   /*
   	  chkmoves() returns 1 if moves are present
      and 0 if moves are not present.
     
   */
   do
   {
   	int x = random(4),y = random(4);
      if(grid[x][y] == 0)
      {
      	grid[x][y] = pow(2,1+random(2));// Try changing the value of grid[x][y] to see the different colours!
         p = 2;
      }
   }
   while(p == 1);
   return p;
}
/* Random number ,such as 2 or 4 , are added in the opposite row or column of
movement i.e if I use up arrow , the last row's random position will be replaced
by 2 or 4, not anywhere on the grid!
So our genrandomno() should work on the arrow key the user presses!
*/
void moveup()
{
	/* moveup() is invoked when the user presses the up arrow.
	After all moves are complete , it generates a random number by 
	invoking genrandomno()
	*/ 
	
   int movechk=0;
	for(int x = 0 ; x < 4 ; x++)
   {
      int l=0;
   	for(int y = 1 ; y < 4 ; y++)
      {
      	int ty=y,mer=0;
         while ((grid[x][ty-1] == 0 || grid[x][ty] == grid[x][ty-1]) && ty>0)
         {
         	if(grid[x][ty-1] == 0)
            {
            	grid[x][ty-1] = grid[x][ty];
               if(grid[x][ty])
               	movechk++;
               grid[x][ty] = 0;
            }
            else
            if(grid[x][ty-1] == grid[x][ty] && mer == 0 && 2*l!=grid[x][ty])
            {
            	grid[x][ty-1] = 2*grid[x][ty];
               l=grid[x][ty];
               if(grid[x][ty])
               	movechk++;
               grid[x][ty] = 0;
               mer = 1;
               score+=int(grid[x][ty-1]);
            }
            else
            if(2*l==grid[x][ty])
            {
            	l=grid[x][ty];
            }
            ty--;
         }
      }
   }
   if(movechk)
   {
   	genrandomno();
      movecount++;
   }
}
void movedown()
{
   	/* movedown() is invoked when the user presses the down arrow.
	After all moves are complete , it generates a random number by 
	invoking genrandomno()
	*/ 
   int movechk=0;
	for(int x = 0 ; x < 4 ; x++)
   {
   	int l = 0;
   	for(int y = 2 ; y >= 0 ; y--)
      {
      	int ty=y,mer=0;
         while ((grid[x][ty+1] == 0 || grid[x][ty] == grid[x][ty+1]) && ty<3)
         {
         	if(grid[x][ty+1] == 0)
            {
            	grid[x][ty+1] = grid[x][ty];
               if(grid[x][ty])
               	movechk++;
               grid[x][ty] = 0;
            }
            else
            if(grid[x][ty+1] == grid[x][ty] && mer == 0 && 2*l!=grid[x][ty])
            {
            	grid[x][ty+1] = 2*grid[x][ty];
               l = grid[x][ty];
               if(grid[x][ty])
               	movechk++;
               grid[x][ty] = 0;
               mer = 1;
               score+=int(grid[x][ty+1]);
            }
            else
            if(2*l==grid[x][ty])
            {
            	l=grid[x][ty];
            }
            ty++;
         }
      }
   }
   if(movechk)
   {
   	genrandomno();
      movecount++;
   }
}
void moveleft()                 
{
	/* moveleft() is invoked when the user presses the left arrow.
	After all moves are complete , it generates a random number by 
	invoking genrandomno()
	*/ 
   int movechk=0;
	for(int y = 0 ; y < 4 ; y++)
   {
   	int l = 0;
   	for(int x = 1 ; x < 4 ; x++)
      {
      	int tx=x,mer=0;
         while((grid[tx-1][y] == 0 || grid[tx-1][y] == grid[tx][y]) && tx>0)
         {
         	if(grid[tx-1][y] == 0)
            {
            	grid[tx-1][y] = grid[tx][y];
               if(grid[tx][y])
               	movechk++;
               grid[tx][y] = 0;
            }
            else
            if(grid[tx-1][y] == grid[tx][y] && mer == 0 && 2*l!=grid[tx][y])
            {
            	grid[tx-1][y] = 2*grid[tx][y];
               l = grid[tx][y];
               if(grid[tx][y])
               	movechk++;
               grid[tx][y] = 0;
               mer = 1;
               score+=int(grid[tx-1][y]);
            }
            else
            if(2*l==grid[tx][y])
            {
            	l=grid[tx][y];
            }
            tx--;
         }
      }
   }
   if(movechk)
   {
   	genrandomno();
      movecount++;
   }
}
void moveright()                  
{
	/* moveright() is invoked when the user presses the up arrow.
	After all moves are complete , it generates a random number by 
	invoking genrandomno()
	*/ 
   int movechk=0;
	for(int y = 0 ; y < 4 ; y++)
   {
      int l=0;
   	for(int x = 2 ; x >= 0 ; x--)
      {
      	int tx=x,mer=0;
         while((grid[tx+1][y] == 0 || grid[tx+1][y] == grid[tx][y]) && tx<3)
         {
         	if(grid[tx+1][y] == 0)
            {
            	grid[tx+1][y] = grid[tx][y];
               if(grid[tx][y])
               	movechk++;
               grid[tx][y] = 0;
            }
            else
            if(grid[tx+1][y] == grid[tx][y] && mer == 0 && 2*l!=grid[tx][y])
            {
            	grid[tx+1][y] = 2*grid[tx][y];
               l=grid[tx][y];
               if(grid[tx][y])
               	movechk++;
               grid[tx][y] = 0;
               mer = 1;
               score+=int(grid[tx+1][y]);
            }
            else
            if(2*l==grid[tx][y])
            {
            	l=grid[tx][y];
            }
            tx++;
         }
      }
   }
   if(movechk)
   {
   	genrandomno();
      movecount++;
   }
}
void instructions()
{
	//Just call this instructions() function and it will display everything
	clrscr();
   gotoxy(25,10);
   cout << "The objective of the game is to\n";
   gotoxy(25,11);
   cout << "get the number 2048 using addition\n";
   gotoxy(25,12);
   cout <<"of the number two and its powers.\n";
   gotoxy(25,16);
   cout << "Press 'enter' key to continue . . . ";
   getch();
   clrscr();

   gotoxy(25,10);
   cout << "You will have a grid of 16 tiles.\n";
   gotoxy(25,11);
   cout << "Two tiles will appear, either a\n";
   gotoxy(25,12);
   cout << "two or a four.\n";
   gotoxy(25,16);
   cout << "Press 'enter' key to continue . . . ";
   getch();
   clrscr();

   gotoxy(25,10);
   cout << "Press the arrow keys to move\n";
   gotoxy(25,11);
   cout << "either up, down, left or right\n";
   gotoxy(25,12);
   cout << "in order to merge two equal tiles.\n";
   gotoxy(25,16);
   cout << "Press 'enter' key to continue . . . ";
   getch();
   clrscr();

   gotoxy(25,10);
   cout << "When two equal tiles merge, they\n";
   gotoxy(25,11);
   cout << "will add up to form a new tile.\n";
   gotoxy(25,16);
   cout << "Press 'enter' key to continue . . . ";
   getch();
   clrscr();

   gotoxy(25,10);
   cout << "Everytime a move is made, a new tile\n";
   gotoxy(25,11);
   cout << "will appear, a two or a four tile, at\n";
   gotoxy(25,12);
   cout << "a random position.\n";
   gotoxy(25,16);
   cout << "Press 'enter' key to continue . . . ";
   getch();
   clrscr();

   gotoxy(25,10);
   cout << "When no more moves are possible,\n";
   gotoxy(25,11);
   cout << "the game is over.\n";
   gotoxy(25,16);
	system("pause");
   getch();
   clrscr();
}
void game()
//compiling everything
{
	movecount = 0;
   genrandomno();
   genrandomno();
   int k, start = time(NULL);
   display();
   while(chkmoves())
   {
      gotoxy(26,23);
      	cout << "Press arrow keys to move";
   	gotoxy(18,24);
      cout << "  Press any other key to pause the game     ";
      int p = getch();
      if(p != 0)
      {
      	gotoxy(19,24);
         cout << "GAME PAUSED, press any other key to unpause";
      }
      k = getch();
   	if(k == 72)
   	{
   		moveup();
         display();
   	}
      else
      if(k == 80)
      {
      	movedown();
         display();
      }
      else
      if(k == 75)
      {
      	moveleft();
         display();
      }
      else
      if(k == 77)
      {
      	moveright();
         display();
      }
      int end = time(NULL);
      gotoxy(65,7);
      printf("Move(s) : %-i",movecount);
		gotoxy(65,8);
      printf("Score : %-5i ",score);
      gotoxy(27,21);
      printf("Time Elapsed : %-i sec(s)",(end-start));
   }
   display();
   gotoxy(65,10);
   cout<<"GAME OVER!";
   getch();
   textbackground(0);
   clrscr();
   gotoxy(35,10);
   	cout << "GAME OVER!";
   gotoxy(29,13);
   	cout << "Avg. Score/Move : "<<(double(score)/double(movecount));   
   gotoxy(25,16);
   	system("pause");
   getch();
   score = 0;
   for(int x=0;x<4;x++)
   	for(int y=0;y<4;y++)
      	grid[x][y]=0;
   clrscr();
}   
void startup()
{
	int curs=0;
   textcolor(4);
   gotoxy(21,15);
   cout << "Press the up and down arrow keys to navigate\n";
   gotoxy(27,16);
   cout << "And the 'enter' key to select\n";
   gotoxy(30,18);
   cprintf("Stuck? Press 'esc' key!");
   textcolor(7);
   while(choice!=2)
   {
      gotoxy(39,1);
   		cout<<"2048"<<endl;
   	gotoxy(39,7);
   		cout<<"MENU";
   	highlight(curs);
      int k1 = getch();
      int k2 = k1!=13? getch() : 13;
   	if(k2 == 72)
      {
         if(curs == 0)
         	curs = -2;
         else
      		curs--;
      }
      else
      if(k2 == 80)
      	curs++;
      curs=abs(curs%3);
      highlight(curs);
      if(k2 == 13)
      {
      	choice=curs;
         switch(choice)
         {
         	case 0 :
               clrscr();
               gotoxy(37,1);
               	cout<<"2048";
            	game();
               startup();
               break;
            case 1 : instructions();startup();break;

         }
      }
   }
}
void main()
{
   randomize();
   startup();
}
