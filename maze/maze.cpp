#include <iostream>
#include <stack>
#include <cstring>
#include <random>
#include <algorithm>
using namespace std;
class Maze {
    public:

        Maze(int width, int height) {
            mazeWidth = width;
            mazeHeight = height;
            visitedCells = 0;
            maze = new int[mazeWidth * mazeHeight];
            memset(maze, 0, mazeWidth * mazeHeight * sizeof(int));
        }

        bool make(){
            m_stack.push(make_pair(0,0));
            maze[0] = CELL_VISITED;
            visitedCells = 1;
            random_device rd;
            mt19937 g(rd());

            while(!m_stack.empty()) {

                pair<int,int> current = m_stack.top();

                int current_x = current.first;
                int current_y = current.second;

                vector<int> neighbours;
                //North
                if(current_y > 0 && (maze[(current_y - 1) * mazeWidth + current_x] & CELL_VISITED) == 0)
                    neighbours.push_back(0);
                //South
                if(current_y < (mazeHeight - 1) && (maze[(current_y + 1) * mazeWidth + current_x] & CELL_VISITED) == 0)
                    neighbours.push_back(1);
                //West
                if(current_x > 0 && (maze[current_y * mazeWidth + (current_x - 1)] & CELL_VISITED) == 0)
                    neighbours.push_back(2);
                //East
                if(current_x < (mazeWidth - 1) && (maze[current_y * mazeWidth + (current_x + 1)] & CELL_VISITED) == 0)
                    neighbours.push_back(3);

                if(!neighbours.empty()) {
                    shuffle(neighbours.begin(), neighbours.end(), g);
                    int nextDir = neighbours[0];

                    int next_x = current_x;
                    int next_y = current_y;

                    switch(nextDir) {
                        case 0:
                                next_y--;
                                maze[current_y * mazeWidth + current_x] |= CELL_PATH_N;
                                maze[next_y * mazeWidth + next_x] |= CELL_PATH_S;
                        break;
                        case 1:
                                next_y++;
                                maze[current_y * mazeWidth + current_x] |= CELL_PATH_S;
                                maze[next_y * mazeWidth + next_x] |= CELL_PATH_N;
                        break;
                        case 2:
                                next_x--;
                                maze[current_y * mazeWidth + current_x] |= CELL_PATH_W;
                                maze[next_y * mazeWidth + next_x] |= CELL_PATH_E;
                        break;
                        case 3:
                                next_x++;
                                maze[current_y * mazeWidth + current_x] |= CELL_PATH_E;
                                maze[next_y * mazeWidth + next_x] |= CELL_PATH_W;
                        break;
                    }

                    m_stack.push(make_pair(next_x,next_y));
                    maze[next_y * mazeWidth + next_x] |= CELL_VISITED;
                    visitedCells++;
                }

                else {
                    m_stack.pop();
                }
            }
            //entry_exit
            maze[(rand() % mazeHeight) * mazeWidth] |= CELL_PATH_W;
            maze[(rand() % mazeHeight) * mazeWidth + (mazeWidth - 1)] |= CELL_PATH_E;
            return true;
        }

        


        void display() {
                for (int y = 0; y < mazeHeight; ++y) {
                    for (int x = 0; x < mazeWidth; ++x) {
                        cout << "+";
                        if ((maze[y * mazeWidth + x] & CELL_PATH_N) == 0) {
                            cout << "---";
                        } else {
                            cout << "   ";
                        }
                    }
                    cout << "+" << endl;

                    for (int x = 0; x < mazeWidth; ++x) {
                        if ((maze[y * mazeWidth + x] & CELL_PATH_W) == 0) {
                            cout << "|";
                        } else {
                            cout << " ";
                        }
                        cout << "   ";
                    }
            
                    if ((maze[y * mazeWidth + (mazeWidth - 1)] & CELL_PATH_E) == 0) {
                        cout << "|";
                    } else {
                        cout << " ";
                    }
                    cout << endl;
                }

                for (int x = 0; x < mazeWidth; ++x) {
                    cout << "+---";
                }
                cout << "+" << endl;
            }

    private:
        int mazeWidth;
        int mazeHeight;
        int* maze;
        int visitedCells;
        stack <pair<int,int>> m_stack;
    enum{
        CELL_PATH_N = 0x01,
        CELL_PATH_E = 0x02,
        CELL_PATH_S = 0x04,
        CELL_PATH_W = 0x08,
        CELL_VISITED = 0x10,
        };
    

};

int main(){

    int width;
    int height;

    cin >> width >> height;

    Maze myMaze(width, height);
    myMaze.make();
    myMaze.display();
    return 0;
}