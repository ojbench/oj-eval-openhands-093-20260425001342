#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int N = 10;
    vector<vector<int>> a(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!(cin >> a[i][j])) return 0;
        }
    }

    int sx = -1, sy = -1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (a[i][j] == 4) { sx = i; sy = j; a[i][j] = 1; }
        }
    }
    if (sx == -1) return 0; // invalid input guard

    // Directions: 0=up,1=right,2=down,3=left
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    auto inb = [&](int x, int y){ return x>=0 && x<N && y>=0 && y<N; };
    auto is_wall = [&](int x, int y){ return !inb(x,y) || a[x][y] == 0; };

    long long score = 0;
    int x = sx, y = sy;
    int dir = 0; // start facing up

    // visited states: position and direction only, since movement depends only on walls
    static bool vis[10][10][4];
    memset(vis, 0, sizeof(vis));
    vis[x][y][dir] = true;

    while (true) {
        int cand[4] = {(dir+1)%4, dir, (dir+3)%4, (dir+2)%4};
        bool moved = false;
        for (int k = 0; k < 4; ++k) {
            int nd = cand[k];
            int nx = x + dx[nd];
            int ny = y + dy[nd];
            if (!is_wall(nx, ny)) {
                dir = nd;
                x = nx; y = ny;
                moved = true;
                break;
            }
        }
        if (!moved) {
            cout << "Silly Pacman";
            return 0;
        }

        if (a[x][y] == 3) {
            score -= 500;
            cout << score;
            return 0;
        }
        if (a[x][y] == 2) {
            score += 2;
            a[x][y] = 1; // eat the dot
        }

        if (vis[x][y][dir]) {
            cout << "Silly Pacman";
            return 0;
        }
        vis[x][y][dir] = true;
    }
}
