#include<cstdio>

using namespace std;

int main()
{
    int N1, N2, a, b, wieza1[102], wieza2[102], counter = 0;
	while(scanf("%d %d", &N1, &N2) == 2)
    {
		if(N1 ==0 && N2==0) break;

		for(a = 1; a <= N1; a++)
        {
            scanf("%d", &wieza1[a]);
        }
		for(a = 1; a <= N2; a++)
        {
            scanf("%d", &wieza2[a]);
        }

		int LCS[102][102] = {};
		for(a = 1; a <= N1; a++)
        {
            for(b = 1; b <=N2; b++)
            {
                if(wieza1[a] == wieza2[b])
                {
                    LCS[a][b] = LCS[a-1][b-1] + 1;
                }
				else if(LCS[a-1][b] > LCS[a][b-1])
                {
                    LCS[a][b] = LCS[a-1][b];
                }
                else LCS[a][b] = LCS[a][b-1];
            }
        }
		printf("Twin Towers #%d\n", ++counter);
		printf("Number of Tiles : %d\n\n", LCS[N1][N2]);
	}


    return 0;
}
