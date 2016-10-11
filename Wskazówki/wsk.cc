#include <iostream>
#include <utility>

#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3

int direction(int dir, char c) {
    if(c == 'U') {
        dir = (dir + 2);
    } else if(c == 'R') {
        dir = (dir + 1);
    } else if(c == 'L') {
        dir = (dir - 1);
    }

    if(dir < 0)
        dir += 4;
    if(dir >= 4)
        dir -= 4;

    return dir;      
}

void move(long &x, long &y, int &dir, char c, int d) {
    int v_d = dir;
    dir = direction(v_d, c);

    if(dir == UP)
        y += d;
    else if(dir == DOWN)
        y -= d;
    else if(dir == LEFT)
        x -= d;
    else if(dir == RIGHT)
        x += d;
}

void move_v(long &x, long &y, int &dir, long v_x, long v_y, int v_dir) {
    if(dir == UP) {
        x += v_x;
        y += v_y;
    } else if(dir == RIGHT) {
        y -= v_x;
        x += v_y;
    } else if(dir == DOWN) {
        x -= v_x;
        y -= v_y;
    } else if(dir == LEFT) {
        y += v_x;
        x -= v_y;
    }

    dir = (dir + v_dir);
    
    if(dir >= 4)
        dir -= 4;
    if(dir < 0)
        dir += 4;
}

struct node {
    long height;
    char c;
    int d;
    long el;
    long v_x;
    long v_y;
    int v_dir;
    node *left;
    node *right;
    node(char c, int d) {
        height = 0;
        left = NULL; 
        right = NULL; 
        this->c = c;
        this->d = d;
        v_x = 0;
        v_y = 0;
        v_dir = UP;
        move(v_x, v_y, v_dir, c, d);
        el = 1;
    }
};

long height(node *p) {
    return p ? p->height : -1;
}

long bfactor(node *p) {
    return height(p->right) - height(p->left);
}

long elements(node *p) {
    return p ? p->el : 0;
}

void fix(node *p) {
    long hl = height(p->left);
    long hr = height(p->right);
    p->height = (hl>hr ? hl : hr) + 1;
    p->v_x = 0;
    p->v_y = 0;
    p->v_dir = UP;

    if(p->left) {
        move_v(p->v_x, p->v_y, p->v_dir, (p->left)->v_x, (p->left)->v_y, (p->left)->v_dir);
    }

    move(p->v_x, p->v_y, p->v_dir, p->c, p->d);
    if(p->right)
        move_v(p->v_x, p->v_y, p->v_dir, (p->right)->v_x, (p->right)->v_y, (p->right)->v_dir);

    long el_l = elements(p->left);
    long el_r = elements(p->right);
    p->el = el_l + el_r + 1;
}

node *rotateright(node *p) // the right rotation round p
{
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fix(p);
    fix(q);
    return q;
}

node *rotateleft(node *q) // the left rotation round q
{
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fix(q);
    fix(p);
    return p;
}

node *balance(node *p) // p node balance
{
    fix(p);
    if( bfactor(p) == 2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // no balance needed
}



node *insert(node *p, long k, char c, int d, long x, long y, int dir) {
    if( !p ) {
        node *new_p = new node(c, d);
        move(x, y, dir, c, d);
        std::cout << x << " " << y << "\n";
        return balance(new_p);
    }

    if( elements(p->left) + 1 >= k) {    
        p->left = insert(p->left, k, c, d, x, y, dir);
    } else {
        if(p->left) {
            move_v(x, y, dir, (p->left)->v_x, (p->left)->v_y, (p->left)->v_dir);
        }
        move(x, y, dir, p->c, p->d);
        p->right = insert(p->right, k - elements(p->left) - 1, c, d, x, y, dir);
    }

    return balance(p);
}

int main() {
    long n;

    std::cin >> n;

    node *p = NULL;
    for(long i = 0; i < n; i++) {
        long k;
        char c;
        int d;
        std::cin >> k;
        std::cin >> c;
        std::cin >> d;
        long x = 0;
        long y = 0;
        p = insert(p, k, c, d, x, y, UP);
    }

    return 0;
}