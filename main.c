#include <ncurses.h>
#include <stdlib.h>
#include <time.h>



int init(char* range);
void deinit();
void writeline(int charrange);


int main(int argc, char* argv[])
{

	srand(time(NULL));
	int range, usrinput;
	if(argv[1] != NULL)//allows user customisable range
	{
	range = init(argv[1]);

	}
	else
	{
	range = init("128");
	}
	while(1==1)
	{
		attron(COLOR_PAIR(1) | A_BOLD | A_UNDERLINE);
		usrinput = getch();
		mvprintw(0, 40, "Matrix Demo by Gigaraptor");
		attroff(A_BOLD | A_UNDERLINE);
		if(usrinput == 8 || usrinput == 27)
		{
			deinit();
		}
		writeline(range);

	}

	deinit();






}

int init(char *charrange)
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	start_color();
	int x,y;
	init_pair(1,COLOR_GREEN, COLOR_BLACK);
	init_pair(2,COLOR_WHITE, COLOR_BLACK);
	int rangeval = atol(charrange);
	if(rangeval > 128 || rangeval < 10)
	{
		return 128;
	}
	else
	{
		return rangeval;

	}




}
void deinit()
{
	endwin();
	exit(0);



}
void writeline(int charrange)
{
	struct timespec start, end;
	start.tv_sec = 0;

	int strlength, display, counter,basex, basey, waiter;
	strlength = rand() % 80 + 20;
	basex = rand() % COLS + 1;
	basey = rand() % LINES + 1;

	for(counter=0;counter<strlength;counter++)
	{
		waiter = getch();
		if( waiter == 27)
		{
			deinit();
		}
		start.tv_nsec = 15000000 + 1500000;
		attroff(COLOR_PAIR(1));
		display = rand() % charrange + 33;
		attron(A_BOLD | COLOR_PAIR(2));
		mvaddch(basey, basex, display);
		refresh();
		if(nanosleep(&start, &end) < 0)
		{
			deinit();
		}

		attroff(A_BOLD);
		attron(COLOR_PAIR(1));
		mvaddch(basey, basex, display);
		basey += 1;
		waiter = 0;
		if(basey > 79)
		{

			break;
		}
	}



}

