#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct node_t node_t;
struct node_t {
  int val;
  node_t *left, *right;
};

node_t *newnode(int val);
node_t *insert(node_t *p, int val);
int lookup(node_t *p, int target);
void setup(void);
void mainloop(void);
void getnum(void);
void print_tree(node_t *p);
void print_err(const char *m);

node_t *bt = NULL;

void clear_err(void);
int main (int argc, char **argv)
{
  setup();
  mainloop();
  endwin();
  return 0;
}

node_t *newnode(int val)
{
  node_t *newp = malloc(sizeof(node_t));
  newp->val = val;
  newp->left = NULL;
  newp->right = NULL;
  return newp;
}
node_t *insert(node_t *p, int val)
{
  if (p == NULL)
    return newnode(val);
  else if (val < p->val)
    p->left = insert(p->left, val);
  else
    p->right = insert(p->right, val);
  return p;
}
int lookup(node_t *p, int target)
{
  if (p == NULL)
    return 0;
  else if (p->val == target)
    return 1;
  else if (target < p->val)
    return lookup(p->left, target);
  else
    return lookup(p->right, target);
}
void mainloop(void)
{
  char c;
  while((c = getch()) != 'q') {
    switch(c) {
      case 'a':
        getnum();
        break;
      case 'p':
        move(1, 1);
        hline(' ', COLS - 2);
        print_tree(bt);
        refresh();
        break;
    }
  }
}
void getnum(void)
{
  int i = 0;
  char c;

  mvaddstr(1, 1, "Enter an int value: ");
  hline(' ', 20);
  refresh();
  while((c = getch()) != '\n') {
    if (c == 'q')
      exit(0);
    if (!isdigit(c)) {
      print_err("Must be a number.");
      return getnum();
    } else {
      i *= 10;
      i += c - '0';
    }
  }
  clear_err();
  mvprintw(1, 1, "Input accepted. <%d>", i);
  bt = insert(bt, i);
  hline(' ', 20);
}
void print_tree(node_t *p)
{
  if (p == NULL)
    return;
  printw("%d, ", p->val);
  print_tree(p->left);
  print_tree(p->right);
}
void print_err(const char *m)
{
  attron(A_REVERSE);
  mvaddstr(LINES - 2, COLS - (strlen(m) + 2), m);
  attroff(A_REVERSE);
}
void clear_err(void)
{
  move(LINES - 2, COLS / 2);
  hline(' ', (COLS / 2) - 2);
}
void setup(void)
{
  initscr();
  cbreak();
  start_color();
  keypad(stdscr, TRUE);
  box(stdscr, 0, 0);
  move(LINES - 3, 1);
  hline(ACS_HLINE, COLS - 2);
  move(LINES - 2, 1);
  addstr(" | ");
  attron(A_REVERSE);
  addstr("a");
  attroff(A_REVERSE);
  addstr("dd node | ");
  attron(A_REVERSE);
  addstr("q");
  attroff(A_REVERSE);
  addstr("uit | ");
  attron(A_REVERSE);
  addstr("p");
  attroff(A_REVERSE);
  addstr("rint tree | ");
  move(1, 1);
  atexit((void (*)(void))&endwin);
  refresh();
}
