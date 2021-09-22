/*
Problem Description

Given an N x M matrix A of non-negative integers representing the height of each unit cell in a continent, the "Blue lake" touches the left and top edges of the matrix and the "Red lake" touches the right and bottom edges.

Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

Find the number of cells from where water can flow to both the Blue and Red lake.

Output Format
Return an integer denoting the number of cells from where water can flow to both the Blue and Red lake.



*/

#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;

void dfs(int i, int j, vector<vector<int> > &A,vector<vector<int> > &ans, int MAX)
{
    int n = A.size();
    int m = A[0].size();
    
    // boundary condition we are going out of the matrix so return
    if(i<0||i>=n||j<0||j>=m)
    {
        return ;
    }
    // if it is already explored and got an positive result no need to explore return
    else if(ans[i][j]==1)
    {
        return ;
    }
    // if the previous cell has greater value then return 
    else if(MAX > A[i][j])
    {
        return ;
    }
    // assign the cell vlaue as 1 and keep exploring in all direction
    ans[i][j]=1;
    dfs(i-1,j,A,ans,A[i][j]);
    dfs(i+1,j,A,ans,A[i][j]);
    dfs(i,j-1,A,ans,A[i][j]);
    dfs(i,j+1,A,ans,A[i][j]);
}


int main()
{
    vector<vector<int> > A = 
    {{1,2,2,3,5},
     {3,2,3,4,4},
     {2,4,5,3,1},
     {6,7,1,4,5},
     {5,1,1,2,4}};

    int n =A.size();
    int m = A[0].size();
    if(n==1&&m==1)
    {
        return  1;
    }
    
    /* these two vector store result of each cell if a cell in red has value 1 it means water can flow from this cell to the red ocean
    	 and if it has value 0 means water can not flow to the red ocean from this cell.
    	 same for the blue vector
	*/
    vector<vector<int> > red(n,vector<int>(m,0));
    vector<vector<int> > blue(n,vector<int>(m,0));
	/*
	 if we can reach to the left or the top from any cell which means water can flow to the
	 	blue ocean from that cell similarly
	 	if we can reach to the bottom or the right from any cell which means water can flow to the
	 	red ocean from that cell
	*/
    for(int i=0;i<n;i++)
    {
        dfs(i,0,A,blue,INT_MIN);
    }
     for(int j=0;j<m;j++)
    {
        dfs(0,j,A,blue,INT_MIN);
    }
     for(int i=0;i<n;i++)
    {
        dfs(i,m-1,A,red,INT_MIN);
    }
     for(int j=0;j<m;j++)
    {
        dfs(n-1,j,A,red,INT_MIN);
    }

    int val = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(red[i][j]==1&&blue[i][j]==1)
            {
                val++;
            }
        }
    }
    cout<<val<<endl;
    return 0;
}
