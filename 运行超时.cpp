void solveSudoku(char** board, int boardSize, int* boardColSize){
    int i,j;
    int di=0;
    int mark;
    bool a[9][9];
  int  b[100]={0};
    for(int k =0;k<9;k++)
    {
        for(int l =0;l<9;l++)
        {
            if(board[k][l]=='.')
            {
                a[k][l]=false;
                b[k++]=k*10+l;
            }
            else
            {
                a[k][l]=true;
            }
        }
    }

    for(i =0;i<9;i++)
    {
        for( j =0;j<9;j++)
        if(board[i][j]=='.')
        {
            board[i][j]=1;
            break;
        }
        if(j!=9)
        break;
    }
    
    while(1)
    {
      for(int m=0;m<9;m++)
      {if(board[i][m]==board[i][j]&&m!=j)
         mark=0;}
   if(mark==1){
    for(int m=0;m<9;m++)
      {if(board[m][j]==board[i][j]&&m!=i)
         mark=0;}}
    if(mark==1)
    {
     for (int m = (i / 3) * 3; m < (i / 3) * 3 + 3; m++){
        for (int n = (j / 3) * 3; n < (j / 3) * 3 + 3; n++){
            if (board[m][n] == board[i][j]&&m!=i&&n!=j)
                  { mark =0;
                   break;}
                                         }

                                                 }
}
if(mark==1&&i==8&&j==8)
{
    return;
}
if(mark==1&&i!=8||j!=8)
{
    for(int k =i;k<8;k++)
    {
        int l;
        for( l=j;l<8;l++)
        {
            if(a[k][l]==false)
            {
                i=k;
                j=l;break;
            }
            
        }
        if(l!=8)
            break;
        if(k==7&&l==8)
        return;
    }
    board[i][j]=1;  di++;  continue;
}
while(board[i][j]==9)
{
    a[i][j]=false;
    di--;
   i=b[di]/10;
   j=b[di]%10;
}
board[i][j]=board[i][j]+1;
    }
}
