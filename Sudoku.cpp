#include"Sudoku.h"


Sudoku::Sudoku()
{
	recursiveTimes=0;
}


void Sudoku::giveQuestion()//沒有輸入，輸出81個數字(OK)
{
	for(int i=0; i<=8; i++)
	{
		for(int j=0; j<=8; j++)
		{
			cout<<rawBoard[i][j];
		}
		cout<<"\n";
	}
	
	return;
}


void Sudoku::readIn()//用cin讀入81個數字，沒有輸出(OK)
{
	char ch;
	
	for(int i=0; i<=8; i++)
	{
		for(int j=0; j<=8; j++)
		{
			cin>>ch;
			sudokuBoard[i][j]=ch-'0';
		}
	}
	
	return;
}


void Sudoku::solve()//沒有輸入，輸出解答(OK)
{
	//寫一個檢查程序，看是否題目有誤變成無解
	bool nums[10];
	
	for(int i=0; i<=8; i++)
	{
		for(int j=0; j<=8; j++)
		{
			if(sudokuBoard[i][j]==0)
			{
				//cout<<"開始檢查("<<i<<","<<j<<")"<<endl;
				//先找一格，然後從row，column，cell看是否有不合理之處
				
				//先初始化陣列都為false
				//cout<<"先初始化nums陣列"<<endl;
				for(int k=1; k<=9; k++)
				{
					nums[k]=false;
					//cout<<nums[k];
				}
				//cout<<endl;
				
				//然後用row填入我們的候選數裡面
				//cout<<"開始在row上找"<<endl;
				for(int k=0; k<=8; k++)
				{
					if(sudokuBoard[i][k]!=0)//如果找到一格已經有數字的格子的話
					{
						//cout<<"在"<<i<<","<<k<<"發現了數字"<<sudokuBoard[i][k]<<endl;
						if(nums[sudokuBoard[i][k]]==true)//可是該數字已經出現過了，代表矛盾
						{
							
							//cout<<"矛盾，數字"<<sudokuBoard[i][k]<<"已經出現過了"<<endl;
							cout<<0;
							return;
						}
						else//如果該數字還沒出現過，我們就紀錄他出現了
						{
							//cout<<"該數字還沒出現過!"<<endl;
							nums[sudokuBoard[i][k]]=true;
						}
					}
				}
				
				//cout<<"先初始化nums陣列"<<endl;
                                for(int k=1; k<=9; k++)
                                {
                                        nums[k]=false;
                                        //cout<<nums[k];
                                }
                                //cout<<endl;
				//接下來用column填入我們的候選數裡面
				//cout<<"開始在column上找"<<endl;
				for(int k=0; k<=8; k++)
				{
					if(sudokuBoard[k][j]!=0)
					{
						//cout<<"在"<<k<<","<<j<<"發現了數字"<<sudokuBoard[k][j]<<endl;
						if(nums[sudokuBoard[k][j]]==true)
						{
							//cout<<"矛盾，數字"<<sudokuBoard[k][j]<<"已經出現過了"<<endl;
							cout<<0;
							return;
						}
						else
						{
							//cout<<"該數字還沒出現過!"<<endl;
							nums[sudokuBoard[k][j]]=true;
						}
					}
				}
				

				//cout<<"先初始化nums陣列"<<endl;
                                for(int k=1; k<=9; k++)
                                {
                                        nums[k]=false;
                                        //cout<<nums[k];
                                }
                                //cout<<endl;
				//接下來用cell填入我們的候選數裡面
				//cout<<"開始在cell上找"<<endl;
				for(int k=i-i%3; k<=(i-i%3)+2; k++)
				{
					for(int l=j-j%3; l<=(j-j%3)+2; l++)
					{
						if(sudokuBoard[k][l]!=0 && (k!=i) && (l!=j))
						{
							//cout<<"在"<<i<<","<<k<<"發現了數字"<<sudokuBoard[i][k]<<endl;
							if(nums[sudokuBoard[k][l]]==true)
							{
								//cout<<"矛盾，數字"<<sudokuBoard[k][l]<<"已經出現過了"<<endl;
								cout<<0;
								return;
							}
							else
							{
								//cout<<"該數字還沒出現過!"<<endl;
								nums[sudokuBoard[k][l]]=true;
							}
						}
					}
				}
			}
		}
	}



	int resultF,resultB;

	for(int c=0; c<=8; c++)
	{
		for(int d=0; d<=8; d++)
		{
			forwardAns[c][d]=sudokuBoard[c][d];
			backwardAns[c][d]=sudokuBoard[c][d];
		}
	}
	
	//先執行solveForward();
	recursiveTimes=0;
	resultF=solveForward();
	if(resultF==-1)
	{
		cout<<0;
		return;
	}
	
	
	//再執行solveBackward();
	recursiveTimes=0;
	resultB=solveBackward();
	//cout<<"用solveBackward結果為"<<resultB<<endl;
	//cout<<"打印backwardAns"<<endl;
	/*
	for(int c=0; c<=8; c++)
	{
		for(int d=0; d<=8; d++)
		{
			cout<<backwardAns[c][d];
		}
		cout<<endl;
	}
	*/
	
	bool isSame;
	isSame=true;
	
	for(int c=0; c<=8; c++)
	{
		for(int d=0; d<=8; d++)
		{
			if(forwardAns[c][d]!=backwardAns[c][d])
			{
				cout<<2;
				return;
			}
		}
	}
	cout<<1<<endl;
	
	for(int c=0; c<=8; c++)
        {
                for(int d=0; d<=8; d++)
                {
			cout<<backwardAns[c][d]<<" ";
                }
                cout<<endl;
        }
	
	
		
}



int Sudoku::solveForward()
{
	if(recursiveTimes==100)
	{
		exit(0);
	}
	
	justFailed=false;

	bool candidate[10];//候選數的陣列，1~9代表1~9，0我們不使用

	for(int i=1; i<=9; i++)
	{
		candidate[i]=false;
	}		

	for(int i=0; i<=8; i++)//代表row
	{
		for(int j=0; j<=8; j++)//代表column
		{
			if(forwardAns[i][j]==0)
			{

				//cout<<"找到一個待填空格("<<i<<"'"<<j<<")"<<endl;

				//如果找到一個空格，就開始確認候選數
				for(int k=0; k<=8; k++)//在同一row上做搜尋，如果找到某數字，candidate上就寫true
                                {
                                        if(forwardAns[i][k]!=0)
                                        {
                                                candidate[forwardAns[i][k]]=true;
                                        }
                                }
				
				for(int k=0; k<=8; k++)//在同一column上做搜尋，如果找到某數字，candidate上就寫true
                                {
                                        if(forwardAns[k][j]!=0)
                                        {
                                                candidate[forwardAns[k][j]]=true;
                                        }
                                }

				for(int k=(i-i%3); k<=((i-i%3)+2); k++)//在所在的cell上面做搜尋，如果找到某數字，candidate上就寫true
                                {
                                        for(int l=(j-j%3); l<=((j-j%3)+2); l++)
                                        {
                                                if(forwardAns[k][l]!=0)
                                                {
                                                        candidate[forwardAns[k][l]]=true;
                                                }
                                        }
                                }

				//cout<<"輸出candidate陣列檢查";
				
				/*
				for(int k=1; k<=9; k++)
				{
					cout<<candidate[k];	
				}
				cout<<endl;
				*/		
				
                                LastRecursiveFailed:
				
				if(justFailed==true)
				{

					//cout<<"剛剛失敗了"<<endl;

					candidate[justPicked[recursiveTimes]]=true;
				}
				
				
				int countCandidate;
				countCandidate=0;
				for(int k=1; k<=9; k++)
				{
					if(candidate[k]==true)
					{
						countCandidate++;
					}
				}
				if(countCandidate==9)//如果9個數字全都存在了，代表該題可能無解或是之前填錯
				{

					//cout<<"發現矛盾"<<endl;

					forwardAns[i][j]=0;
					return -1;//所以無解的題目，他會return-1
				}
				
				
				//cout<<"現在開始找一個測試數填入"<<endl;

				for(int k=1; k<=9; k++)
				{

					//cout<<"進入迴圈第"<<k<<"次"<<endl;

					if(candidate[k]!=true)//如果某號候選數，還沒出現的話
					{
						forwardAns[i][j]=k;//我們就試著把該格填上其中一個候選數
						
						//cout<<"試著在"<<i<<","<<j<<"填入"<<k<<endl;

						justPicked[recursiveTimes]=k;//我們在第幾次遞迴，測試了某個數字
						justFailed=false;
						int count;
						count=0;
						for(int a=0; a<=8; a++)
						{
							for(int b=0; b<=8; b++)
							{
								if(forwardAns[a][b]!=0)
								{
									count++;
								}
							}
						}
						if(count==81)
						{
							return 1;
						}

					}else
					{
						continue;
					}


					/*
					我們填完一個測試數之後，就在執行下一次
					如果下一次return 1的話，代表出現矛盾，這邊我們就要把剛剛挑的數字( justPicked[recursiveTimes] )
					在candidate[]裡面變成true，不讓我們填他，並再次執行當次的遞迴
					*/
					recursiveTimes++;
					int result;
					result=solveForward();

					//cout<<"solve執行完畢"<<endl;
					//cout<<"result目前為"<<result<<endl;

					if(result==-1)
					{

						//cout<<"接到矛盾消息，該重新執行當次迴圈"<<endl;

						recursiveTimes--;
						justFailed=true;

						//cout<<"更新justFailed為true"<<endl;

						goto LastRecursiveFailed;	
					}
					else if(result==1)
					{
						return 1;
					}					
				}
			}	
		}
	}
}


int Sudoku::solveBackward()
{
	if(recursiveTimes==100)
	{
		exit(0);
	}
	
	justFailed=false;

	bool candidate[10];//候選數的陣列，1~9代表1~9，0我們不使用

	for(int i=1; i<=9; i++)
	{
		candidate[i]=false;
	}		

	for(int i=0; i<=8; i++)//代表row
	{
		for(int j=0; j<=8; j++)//代表column
		{
			if(backwardAns[i][j]==0)
			{

				//cout<<"找到一個待填空格("<<i<<"'"<<j<<")"<<endl;

				//如果找到一個空格，就開始確認候選數
				for(int k=0; k<=8; k++)//在同一row上做搜尋，如果找到某數字，candidate上就寫true
                                {
                                        if(backwardAns[i][k]!=0)
                                        {
                                                candidate[backwardAns[i][k]]=true;
                                        }
                                }
				
				for(int k=0; k<=8; k++)//在同一column上做搜尋，如果找到某數字，candidate上就寫true
                                {
                                        if(backwardAns[k][j]!=0)
                                        {
                                                candidate[backwardAns[k][j]]=true;
                                        }
                                }

				for(int k=(i-i%3); k<=((i-i%3)+2); k++)//在所在的cell上面做搜尋，如果找到某數字，candidate上就寫true
                                {
                                        for(int l=(j-j%3); l<=((j-j%3)+2); l++)
                                        {
                                                if(backwardAns[k][l]!=0)
                                                {
                                                        candidate[backwardAns[k][l]]=true;
                                                }
                                        }
                                }

				//cout<<"輸出candidate陣列檢查";
				
				/*
				for(int k=1; k<=9; k++)
				{
					cout<<candidate[k];	
				}
				cout<<endl;
				*/		
				
                                LastRecursiveFailed:
				
				if(justFailed==true)
				{

					//cout<<"剛剛失敗了"<<endl;

					candidate[justPicked[recursiveTimes]]=true;
				}
				
				
				int countCandidate;
				countCandidate=0;
				for(int k=1; k<=9; k++)
				{
					if(candidate[k]==true)
					{
						countCandidate++;
					}
				}
				if(countCandidate==9)//如果9個數字全都存在了，代表該題可能無解或是之前填錯
				{

					//cout<<"發現矛盾"<<endl;

					backwardAns[i][j]=0;
					return -1;//所以無解的題目，他會return-1
				}
				
				
				//cout<<"現在開始找一個測試數填入"<<endl;

				for(int k=1; k<=9; k++)
				{

					//cout<<"進入迴圈第"<<k<<"次"<<endl;

					if(candidate[10-k]!=true)//如果某號候選數，還沒出現的話
					{
						backwardAns[i][j]=10-k;//我們就試著把該格填上其中一個候選數
						
						//cout<<"試著在"<<i<<","<<j<<"填入"<<k<<endl;

						justPicked[recursiveTimes]=10-k;//我們在第幾次遞迴，測試了某個數字
						justFailed=false;
						int count;
						count=0;
						for(int a=0; a<=8; a++)
						{
							for(int b=0; b<=8; b++)
							{
								if(backwardAns[a][b]!=0)
								{
									count++;
								}
							}
						}
						if(count==81)
						{
							return 1;
						}

					}else
					{
						continue;
					}


					/*
					我們填完一個測試數之後，就在執行下一次
					如果下一次return 1的話，代表出現矛盾，這邊我們就要把剛剛挑的數字( justPicked[recursiveTimes] )
					在candidate[]裡面變成true，不讓我們填他，並再次執行當次的遞迴
					*/
					recursiveTimes++;
					int result;
					result=solveBackward();

					//cout<<"solve執行完畢"<<endl;
					//cout<<"result目前為"<<result<<endl;

					if(result==-1)
					{

						//cout<<"接到矛盾消息，該重新執行當次迴圈"<<endl;

						recursiveTimes--;
						justFailed=true;

						//cout<<"更新justFailed為true"<<endl;

						goto LastRecursiveFailed;	
					}
					else if(result==1)
					{
						return 1;
					}					
				}
			}	
		}
	}
}


void Sudoku::changeNum(int a, int b)//把sudokuBoard上的a，b做交換
{
	
	for(int i=0; i<=8; i++)
	{
		for(int j=0; j<=8; j++)
		{
			if(sudokuBoard[i][j]==a)
			{
				sudokuBoard[i][j]=b;
			}
			else if(sudokuBoard[i][j]==b)
			{
				sudokuBoard[i][j]=a;
			}
		}
	}
	
}


void Sudoku::changeRow(int a, int b)//輸入0,1,2 把這兩列大row做交換(OK)
{
	int swap;
	int b3=b*3;
	
	for(int i=a*3; i<=a*3+2; i++)
	{
		for(int j=0; j<=8; j++)
		{
			//先把b相對應位子的值存進swap
			swap=sudokuBoard[b3][j];
			sudokuBoard[b3][j]=sudokuBoard[i][j];
			sudokuBoard[i][j]=swap;
		}
		b3++;
	}
}


void Sudoku::changeCol(int a, int b)//(OK)
{
	int swap;
	int b3=b*3;

	for(int i=a*3; i<=a*3+2; i++)
	{
		for(int j=0; j<=8; j++)
		{
			swap=sudokuBoard[j][b3];
			sudokuBoard[j][b3]=sudokuBoard[j][i];
			sudokuBoard[j][i]=swap;
		}
		b3++;	
	}
	
}


void Sudoku::rotate(int n)
{
	int swapBoard[9][9];
	
	for(int i=0; i<n; i++)
	{
		for(int i=0; i<=8; i++)
		{
			for(int j=0; j<=8; j++)
			{
				swapBoard[i][j]=sudokuBoard[i][j];
			}	
		}
		
		for(int i=0; i<=8; i++)
		{
			for(int j=0; j<=8; j++)
			{
				sudokuBoard[i][j]=swapBoard[8-j][i];
			}
		}
	}
}


void Sudoku::flip(int n)
{
	int swapBoard[9][9];
	for(int i=0; i<=8; i++)
        {
        	for(int j=0; j<=8; j++)
                {
        	        swapBoard[i][j]=sudokuBoard[i][j];
                }
        }

	
	if(n==1)//水平翻轉
	{
		for(int i=0; i<=8; i++)
	        {
	        	for(int j=0; j<=8; j++)
	                {
	        	        sudokuBoard[i][j]=swapBoard[i][8-j];
	                }
	        }
	}
	else if(n==0)
	{
		for(int i=0; i<=8; i++)
                {
                        for(int j=0; j<=8; j++)
                        {
                                sudokuBoard[i][j]=swapBoard[8-i][j];
                        }
                }	
	}
}


void Sudoku::transform()
{
	printSudokuBoard();
}


void Sudoku::printSudokuBoard()
{
        for(int i=0; i<=8; i++)
        {
                for(int j=0; j<=8; j++)
                {
                        cout<<sudokuBoard[i][j];
                }
                cout<<endl;
        }

}
