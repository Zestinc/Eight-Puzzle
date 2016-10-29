#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#define PUZZLESIZE 15
using namespace std;

class PuzzleState {
public:
    vector<int> state;
    vector<vector<int>> path;
    bool empty() {
        return state.empty();
    }
};

class EightPuzzle {
private:
    const int puzzleSize = PUZZLESIZE;
    map<vector<int>, bool> flag;
    int rowSize;
public:
    EightPuzzle() {
        rowSize = (int) sqrt(puzzleSize + 1);
    }
    bool goal(vector<int> state) {
        for (int i = 0; i < puzzleSize; i++) {
            if (i+1 != state[i])
                return false;
        }
        return true;
    }

    int findBlank(vector<int> state) {
        for (int i = 0; i < state.size(); i++) {
            if (!state[i])
                return i;
        }
        cout << "error when finding blank\n";
        return -1;
    }

    PuzzleState goUp(PuzzleState state) {
        vector<int> currentState = state.state;
        int blankPosition = findBlank(currentState);
        if (blankPosition < rowSize) {
            return PuzzleState();
        }

        int above = blankPosition - rowSize;
        swap(currentState[blankPosition], currentState[above]);

        state.state = currentState;
        state.path.push_back(state.state);
        return state;
    }

    PuzzleState goDown(PuzzleState state) {
        vector<int> currentState = state.state;
        int blankPosition = findBlank(currentState);
        if (blankPosition > puzzleSize - rowSize) {
            return PuzzleState();
        }

        int down = blankPosition + rowSize;
        swap(currentState[blankPosition], currentState[down]);

        state.state = currentState;
        state.path.push_back(state.state);
        return state;
    }

    PuzzleState goLeft(PuzzleState state) {
        vector<int> currentState = state.state;
        int blankPosition = findBlank(currentState);
        if (blankPosition % rowSize == 0) {
            return PuzzleState();
        }

        int left = blankPosition - 1;
        swap(currentState[blankPosition], currentState[left]);

        state.state = currentState;
        state.path.push_back(state.state);
        return state;
    }

    PuzzleState goRight(PuzzleState state) {
        vector<int> currentState = state.state;
        int blankPosition = findBlank(currentState);
        if ((blankPosition + 1) % rowSize == 0) {
            return PuzzleState();
        }

        int right = blankPosition + 1;
        swap(currentState[blankPosition], currentState[right]);

        state.state = currentState;
        state.path.push_back(state.state);
        return state;
    }

    PuzzleState bfs(PuzzleState state) {

        queue<PuzzleState> mQueue;
        mQueue.push(state);

        while (!mQueue.empty()) {
            PuzzleState currentState = mQueue.front();
            mQueue.pop();

            if (flag.count(currentState.state))
                continue;

            flag[currentState.state] = true;

            if (goal(currentState.state)) {
                cout << "get goal state" << endl;
                return currentState;
            }

            PuzzleState leftState = goLeft(currentState);
            PuzzleState rightState = goRight(currentState);
            PuzzleState upState = goUp(currentState);
            PuzzleState downState = goDown(currentState);

            if (!leftState.empty())
                mQueue.push(leftState);
            if (!rightState.empty())
                mQueue.push(rightState);
            if (!upState.empty())
                mQueue.push(upState);
            if (!downState.empty())
                mQueue.push(downState);
        }

        return PuzzleState();
    }

    void showPath(PuzzleState p) {
        auto path = p.path;
        for (auto state : path) {
            for (int i = 0; i < puzzleSize + 1; ++i) {
                if (i % rowSize == 0) {
                    cout << endl;
                }
                cout << state[i] << " ";
            }
            cout << endl;
        }
    }
};



int main() {

    vector<int> init(PUZZLESIZE + 1);
    for (int i = 0; i < PUZZLESIZE + 1; ++i) {
        cin >> init[i];
    }
    EightPuzzle eightPuzzle;
    PuzzleState puzzleState;
    puzzleState.state = init;
    puzzleState.path.push_back(init);
    puzzleState = eightPuzzle.bfs(puzzleState);
    if (!puzzleState.empty())
        eightPuzzle.showPath(puzzleState);
}

/***
1 2 3 4 8 0 7 6 5
1 0 2 3 4 5 6 7 8

1 2 3 4
5 6 7 8
9 10 11 12
13 14 0 15

0 2 3 4
1 6 7 8
5 10 11 12
9 13 14 15
 ***/