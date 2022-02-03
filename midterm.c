#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*tozih : dar surate zadane gozine5 bazi be surate hazfi anjam shode va be in shekl ke agar tedade team ha be forme 2^n nabashad 
dar marhale aval be tedadi az team ha esterahat midahad va az marhale bad team ha do be do bazi karde va hazf mishavand*/

long long participants[100][4];
int teams[100];
int teams_index;
int participants_index;
int people_index;

////////////////// menu /////////////////
int menu(void)
{
	int choice;
	printf("Welcome to our simulator [n_participants: %d] [n_teams: %d]\n\n",participants_index,teams_index);
	printf("1) Add Team\n");
	printf("2) Vote for a Winner\n");
	printf("3) Execute simulation and report a winner\n");
	printf("4) delete\n");
	printf("5) elimination game\n");
	scanf("%d",& choice);
	return choice;
}
////////////////// case1(add team) /////////////////
void add_team(void)
{
	teams_index++;
	
}

////////////////// case2(Vote for a Winner) /////////////////
void vote(void)
{
	int bet_index=0;
	char id_s[15];
	long long int id=0;
	int	cpy_people_index=people_index;
	int i=0;
	int bet,digit_num=0;
	int index=0;
	int run=1;
	long long int cpy;
	
/*	printf("ID: ");  //tozih:age ba ehtesabe sefrhaye aval dar majmu 10 ragham dashtim mishod az in ghesmate comment shode estefade kard va vorudi ra ba string gereft albate lazem bud ketabkhane string.h ham ezafe shavad.
	scanf("%s",id_s);
	if(strlen(id_s)<11)
	{
		for(i=9;i>-1;i--)
		{
			id+=(((int)id_s[i]-48)*pow(10,(9-i)));
		}
	}
	else
	{
		printf("ID has mor than 10 digits\n");
		return;
	}*/
	printf("ID: ");
	scanf("%lld",&id);
	cpy=id;
	while(cpy!=0)
	{
		cpy/=10;
		digit_num++;
	}
	if(digit_num>10)
	{
		printf("ID has mor than 10 digits\n");
		return;
	}
		
	printf("Bet: ");
	scanf("%d",&bet);
	
	if(bet<teams_index)
	{
		for(i=0;i<=cpy_people_index;i++)
		{
			if(id==participants[i][0])
			{
				participants[i][3]++;
				index=i;
				run=0;
			}	
		}
		if(run)
		{
			index=people_index;
			participants[index][3]++;
			people_index++;
			participants[index][0]=id;
		
		}
		
		if(participants[index][3]<3)
		{
	
			bet_index=participants[index][3];
			participants[index][bet_index]=bet;
			participants_index++;
			printf("insertion success\n");
		}
		else
		{
			participants[index][3]--;
			printf("insertion failed\n");
		}		
	}
	else
	{
		printf("The team that you choose doesn`t exist\n");
		return;
	}

}
////////////////// case3(Execute simulation and report a winner) /////////////////
void game_table(int winner[]);
void execute(void)
{
	
	int result,max_result=0;
	int i, j,z=0,game_num;
	game_num=(teams_index*(teams_index-1))/2;
	int res_game[game_num];
	
	for(i=0;i<teams_index;i++)
	{
		for(j=i+1;j<teams_index;j++)
		{
			result=rand()%2;
			if(result==0)
			{
				teams[i]++;
				res_game[z]=i;
				z++;
			}
			else
			{
				teams[j]++;
				res_game[z]=j;
				z++;
			}
		}
	}
	int max=teams[0];
	int max_index=0;
	for(i=0;i<teams_index;i++)
	{
		if(max<teams[i])
		{
			max=teams[i];
			max_index=i;
		}
	}
	//peida kardane tedad team haee ke meghdareshan barabare max shode baraye entekhabe random beine onha
	j=0;
	int maxteams[100];
	for(i=0;i<teams_index;i++)
	{
		if(teams[i]==max)
		{
			max_result++;
			maxteams[j]=i;
			j++;
		}
	}
	int rand_max;
	int ran=0;
	if(max_result>1)
	{
		ran=rand();
		rand_max=ran%max_result;
		max_index=maxteams[rand_max];

	}
	//chape liste emtiazat va moshakhas kardane teame barande na afrade barande
	if(teams_index>0)
		printf("team %d is a winner\n",max_index);
	for(i=0;i<teams_index;i++)
	{
			printf("teams[%d]: %d\n",i,teams[i]);
	}
	for(i=0;i<people_index;i++)
	{
		if(participants[i][3]==2)//chon momken ast fard 1 bar ray dade bashad vali chon khaneye digare onha 0 hast engar ke hamishe be sefr ray dade pas halat bayad joda shavad
		{
			if(participants[i][1]==max_index||participants[i][2]==max_index)
			{
				printf("%.10lld win\n",participants[i][0]);
			}
		}
		else
		{
			if(participants[i][1]==max_index)
			{
				printf("%.10lld win\n",participants[i][0]);
			}
		}
	}
	game_table(res_game);
}
////////////////// case4(delete) /////////////////

void delete_vot(void)
{

	long long int id=0;
	long long temp[1][3];
	int i,j;
	int cpy,digit_num=0;
	int run=1;
	int vot_num;
	printf("ID: ");
	scanf("%lld",&id);
	cpy=id;
	while(cpy!=0)
	{
		cpy/=10;
		digit_num++;
	}
	if(digit_num>10)
	{
		printf("ID has mor than 10 digits\n");
		return;
	}
	for(i=0;i<people_index;i++)
	{
		if(id==participants[i][0])
		{
			vot_num=participants[i][3];
			for(j=0;j<4;j++)
			{
				participants[i][j]=participants[people_index-1][j];	
				participants[people_index-1][j]=0;
			}
			run=0;
		}	
	}
	if(run)
	{
		printf("This person doesn`t exist\n");
		return;
	}
	people_index--;
	participants_index-=vot_num;
	printf("The person is deleted \n");
}
////////////////// (game table)/////////////////
void game_table(int winner[])
{
	int i,j,z=0;
	printf(" Game number | Participating teams | Winner\n");
	printf("--------------------------------------------\n");
	for(i=0;i<teams_index-1;i++)
	{
		for(j=i+1;j<teams_index;j++)
		{
			printf("%12d | %8d vs %-7d | team %d\n",z+1,i,j,winner[z]);
			z++;
		}
	}
}
////////////////// case5(elimination_game) /////////////////
void elimination_game(void)
{
	int new_list[teams_index][2];
	int temp=0;
	int g;
	int m,n,z=0;
	int i,ran,j=0;
	int win_index[teams_index];
	
	for(i=0;i<teams_index;i++)
	{
		win_index[i]=0;
		new_list[i][1]=0;
	}
	n=(teams_index/2);
	for(i=1;i<=n;i++)
	{
		if(pow(2,i)<teams_index)
		{
			temp++;
		}
	}
	m=2*(teams_index-pow(2,temp));
	for(i=0;i<m;i+=2)
	{
		ran=rand()%2;
		if(ran==0)
		{
			new_list[j][1]=i;
			j++;
			win_index[i]++;
		}
		else
		{
			new_list[j][1]=i+1;
			j++;
			win_index[i+1]++;
		}
	}
	for(i=m;i<teams_index;i++)
	{
		new_list[j][1]=i;
		j++;
	}
	int f;
	while(j!=1)
	{
		f=0;
		for(i=0;i<j;i+=2)
		{
			ran=rand()%2;

			if(ran==0)
			{
				g=new_list[i][1];
				win_index[g]+=1;
				new_list[f][1]=g;
				f++;
			}
			else
			{
				g=new_list[i+1][1];
				win_index[g]+=1;
				new_list[f][1]=g;
				f++;
			}
		}
		j/=2;
	}
	//chape liste emtiazat va moshakhas kardane teame barande na afrade barande
	if(teams_index>0)
		printf("team %d is a winner\n",new_list[0][1]);
	for(i=0;i<teams_index;i++)
	{
		printf("teams[%d]: %d\n",i,win_index[i]);
	}
	for(i=0;i<people_index;i++)
	{
		if(participants[i][3]==2)//chon momken ast fard 1 bar ray dade bashad vali chon khaneye digare onha 0 hast engar ke hamishe be sefr ray dade pas halat bayad joda shavad
		{
			if(participants[i][1]==new_list[0][1]||participants[i][2]==new_list[0][1])
			{
				printf("%.10lld win\n",participants[i][0]);
			}
		}
		else
		{
			if(participants[i][1]==new_list[0][1])
			{
				printf("%.10lld win\n",participants[i][0]);

			}
		}
	}
	
}

int main() {
	int choice;
	int run=1;
	time_t t=time(NULL);
	srand(t);
	while (run)
	{
		choice=menu();
		switch (choice)
		{
			case 1:
				add_team();
				break;
			case 2:
				vote();
				break;
			case 3:
				execute();
				return 0;
				break;
			case 4:
				delete_vot();
				break;
			case 5:
				elimination_game();
				return 0;
			default:
				printf("Invalid Choice\n");
		}
		
	}
	return 0;
}

