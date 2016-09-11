#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int CARD_RANGE=13; //前后分别安排两个空间，便于查找3连时统一处理，否则边界处理很麻烦
int cardList[CARD_RANGE];  //保存输入的麻将序列
int tmpList[CARD_RANGE];  //处理过程中麻将状态的保存

//2-10的空间分别对应麻将1-9,cardList[i]表示麻将面值为i的麻将数量
const int starPos=2;
const int endPos=10;

void printInfo()
{

	for(int i=0;i<CARD_RANGE;++i)
	{
		printf("%d\t",tmpList[i]);
	}
	printf("\n");
}

bool isDone()
{
	//printInfo();
	for(int idx=starPos;idx<=endPos;++idx)
	{
		if(tmpList[idx]==1 || tmpList[idx]==2 || tmpList[idx]==4)
			return false;
	}
	return true;
}
bool getpatterner(int idx)
{
	//如果临近能构成3连返回true
	if(tmpList[idx]>0 && tmpList[idx+1]>0 && tmpList[idx+2]>0)
	{
		return true;
	}
	return false;
}

bool deal()
{
	for(int i=starPos;i<=endPos;++i)
	{
		//对于必须要找搭档的牌，前后关联找搭档
		if(tmpList[i]==1 || tmpList[i]==2 || tmpList[i]==4)
		{
			//找到搭档将3连删除掉
			//分别查看 (i-2 , i -1 ,i ),(i-1,i,i+1),(i,i+1,i+2)是否存在，存在继续往下
			//不存在，则回溯
			bool havePatterner=false;
			for(int k=i-2;k<=i;++k)
			{
				if(getpatterner(k))
				{
					--tmpList[k];
					--tmpList[k+1];
					--tmpList[k+2];
					if(isDone())
						return true;
					deal();
					if(isDone())
						return true;
					++tmpList[k];
					++tmpList[k+1];
					++tmpList[k+2];
					havePatterner=true;	
				}
			}
			if(!havePatterner)
			{
				//1个的，2个相同的，4个相同的找不到3连则不能胡牌
				return false;

			}

		}
	}
	//如果是大队胡，则取出正确麻将后没有需要进一步处理直接返回成功
	return ture;
}


int main()
{
	printf("input 14 numbers ,ervery number between 1 and 9\n");

	while(1)
	{
		bool isOk=false;
		bool isSourceDataRight=true;
		memset(cardList,0,sizeof(cardList));
		int idx,iputcnt=0;
		while(scanf("%d",&idx))
		{
			++iputcnt;
			if(idx<1 || idx>9)
			{
				printf("number %d is illeagl!\n",idx);
				isSourceDataRight=false;
				break;
			}
			cardList[idx+1]+=1;
			if(iputcnt>=14)
				break;
		}
		for(int i=starPos;i<=endPos;++i)
		{
			if(cardList[i]>4)
			{
				printf("the count of number %d present more than 4 times\n",cardList[i]);
				isSourceDataRight=false;
			}
		}
		if(!isSourceDataRight)
			continue;

		memcpy(tmpList,cardList,sizeof(cardList));
		//printInfo();
		for(int i=starPos;i<=endPos;++i)
		{
			//取出一对相同的
			if(tmpList[i]>1)
			{
				tmpList[i]-=2;
				if(deal())
				{
					isOk=true;
				}
			}
			//将麻将恢复到初始状态，继续使用另一对相同的作为麻将
			memcpy(tmpList,cardList,sizeof(cardList));
		}
		if(isOk)
			printf("yes!\n");
		else
			printf("no!\n");
	}

	return 0;
}
