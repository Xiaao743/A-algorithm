#include<iostream>
#include<utility> //for using pair<int,int> in order to find location of blank space in a 3x3 matrix.
using namespace std;

//A matrix that can store all the postition that we previously caluclated to avoid infinite loop.
int all_positions[50][3][3];
int visit_count;
//Declaring the rows and columns globally.
int r,c;

//copy a matrix to another matrix.
void copypaste(int mat_copy[3][3],int mat_paste[3][3])
{
    for(r=0;r<3;r++)
    {
        for(c=0;c<3;c++)
        {
            mat_paste[r][c]=mat_copy[r][c];
        }
    }
}

// function to print matrix after every move
void printMatrix(int mat[3][3])
{
    for(r=0;r<3;r++)
    {
        for(c=0;c<3;c++)
        {
            if(mat[r][c] == -1) cout << "_ ";
            else cout << mat[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "----------\n";
}

//finding where balnk space is in this case '-1';
pair<int,int> blank_space(int mat[3][3])
{
    pair<int,int>space={-1,-1};
    for(r=0;r<3;r++)
    {
        for(c=0;c<3;c++)
        {
            if(mat[r][c]==-1)
                space={r,c};

        }
    }
    return space;
}
//Handling the User input
void userinput(int mat[3][3])
{
    for(r=0;r<3;r++)
    {
        for(c=0;c<3;c++)
        {
            cout<<"Enter the numbers for row "<<r+1<<" and column "<<c+1<<" : ";
            cin>>mat[r][c];
        }
    }
}
//Calculate Huristic value
int huristic(int mat[3][3],int goal_mat[3][3])
{
    int h=0; //variable to hold heuristic value and return it when ever we invoke this function
    for(r=0;r<3;r++)
    {
        for(c=0;c<3;c++)
        {
            if(mat[r][c]!=goal_mat[r][c])
                h++;
        }
    }
    return h;
}
bool up(int best_mat[3][3],int final_mat[3][3])
{
    int row,col,temp;
    pair<int,int>space=blank_space(best_mat);
    row=space.first;
    col=space.second;
    if(row>0) //only move up when row is at 2 or 3;
    {
        copypaste(best_mat,final_mat);
        temp=final_mat[row-1][col];
        final_mat[row-1][col]=final_mat[row][col];
        final_mat[row][col]=temp;
        return true;
    }
    return false;
}
bool down(int best_mat[3][3],int final_mat[3][3])
{
    int temp,row,col;
    pair<int,int>space=blank_space(best_mat);
    row=space.first;
    col=space.second;
    if(row<2) //only move down when row is at 1 or 2;
    {
        copypaste(best_mat,final_mat);
        temp=final_mat[row+1][col];
        final_mat[row+1][col]=final_mat[row][col];
        final_mat[row][col]=temp;
        return true;
    }
    return false;
}
bool right(int best_mat[3][3],int final_mat[3][3])
{
    int temp,row,col;
    pair<int,int>space=blank_space(best_mat);
    row=space.first;
    col=space.second;
    if(col<2) //only move right when column is at 1 or 2;
    {
        copypaste(best_mat,final_mat);
        temp=final_mat[row][col+1];
        final_mat[row][col+1]=final_mat[row][col];
        final_mat[row][col]=temp;
        return true;
    }
    return false;
}
bool left(int best_mat[3][3],int final_mat[3][3])
{
    int temp,row,col;
    pair<int,int>space=blank_space(best_mat);
    row=space.first;
    col=space.second;
    if(col>0) //only move left when column is at 2 or 3;
    {
        copypaste(best_mat,final_mat);
        temp=final_mat[row][col-1];
        final_mat[row][col-1]=final_mat[row][col];
        final_mat[row][col]=temp;
        return true;
    }
    return false;
}
//checking if the positon we are calculating exist in previous positions or not.
bool check_positon(int mat[3][3])
{
    for(int i=0;i<visit_count;i++)
    {
        if(huristic(mat,all_positions[i])==0)
            return true; //Match found
    }
    return false; //no match found
}
//main funtion for algorithm.
int A_star(int initial_mat[3][3],int goal_mat[3][3])
{
    int mat_up[3][3],mat_down[3][3],mat_right[3][3],mat_left[3][3]; //calculate all the possible ways the matrix can move i.e up,down,right,left;
    int best_mat[3][3];
    copypaste(initial_mat,best_mat); //best_mat had garbage value in it so we copypaste initial matrix into it to avoid any bug.
    int depth=0;
    int best_x;

    // print initial state
    cout << "\nStep " << depth << ":\n";
    printMatrix(best_mat);

    while(huristic(initial_mat,goal_mat)!=0)
    {
        int x_up=999,x_down=999,x_left=999,x_right=999;
    //invoking the up,down,right and left function to store the candidate matrix appropriately
        if(up(initial_mat,mat_up)==true)
            x_up=depth+huristic(mat_up,goal_mat);
        if(down(initial_mat,mat_down))
            x_down=depth+huristic(mat_down,goal_mat);
        if(right(initial_mat,mat_right))
            x_right=depth+huristic(mat_right,goal_mat);
        if(left(initial_mat,mat_left))
            x_left=depth+huristic(mat_left,goal_mat);

     //checking which one has the lowest value for x(the lower the value of x the closer we are to our goal state)
        if(x_up<x_down && x_up<x_right && x_up<x_left && check_positon(mat_up)==false)
            copypaste(mat_up,best_mat);
        else if(x_down<x_up && x_down<x_right && x_down<x_left && check_positon(mat_down)==false)
            copypaste(mat_down,best_mat);
        else if(x_right<x_up && x_right<x_down && x_right<x_left && check_positon(mat_right)==false)
            copypaste(mat_right,best_mat);
        else if(x_left<x_up && x_left<x_down && x_left<x_right && check_positon(mat_left)==false)
            copypaste(mat_left,best_mat);

        copypaste(best_mat,initial_mat); //initial state will the best match after every iteration to avoid looping the same initial_state forever.
        copypaste(best_mat,all_positions[visit_count]);
        visit_count++;
        best_x=depth+huristic(best_mat,goal_mat);
        depth++;

        // print best_mat after every move
        cout << "Step " << depth << ":\n";
        printMatrix(best_mat);
    }
    return depth;
}
//main funtion for calling the astar algo().
int main()
{
    int initial_state[3][3],goal_state[3][3];

    cout<<"----- A* Search Algorithm ----- \n";

    cout<<"Initial Matrix: \n";
    userinput(initial_state);

    cout<<"\nFinal Matrix: \n";
    userinput(goal_state);

    // Store first position
    copypaste(initial_state,all_positions[visit_count]);
    visit_count++;

    // Calling A* Algorithm
    int result = A_star(initial_state, goal_state);

    cout << "\nGoal State Reached!" << endl;
    cout << "Cost = " << result << endl;

    return 0;
}
