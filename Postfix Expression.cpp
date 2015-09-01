#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool IsValid(string);
string In2Pos(string);
bool isnumber(char);
int precede(char);
int Evaluate();

int main()
{
	string formula;
	cin>>formula;
	if(IsValid(formula))
	cout<<"Yes"<<endl;
	else
	cout<<"No"<<endl;
	
	return 0;
}

bool IsValid(string formula)
/*
Pre:输入函数为标准的中缀表达式，没有单目运算符，如++，-2之类的，否则检测结果不准确。 
*/
{
	stack<char> brackets;//left:+1,right:-1
	bool flag = false;//number:true,operator:false
	int length = formula.size();
	for(int i=0;i<length;i++)
	{
		if(formula[i]=='('||formula[i]=='['||formula[i]=='{')
		{
			//cout<<"LF"<<endl;
			brackets.push(formula[i]);
		}
		else if(formula[i]==')')
		{
			if(brackets.top()=='(')
			brackets.pop();
			else
			return false;
		}
		else if(formula[i]==']')
		{
			if(brackets.top()=='[')
			brackets.pop();
			else
			return false;
		}
		else if(formula[i]=='}')
		{
			if(brackets.top()=='{')
			brackets.pop();
			else
			return false;
		}
		else if(formula[i]>47&&formula[i]<58)//integer
		{
			//cout<<"D"<<endl;
			if(flag) return false;//If it is number right before
			
			flag = true;
			bool dot = false;//decimal?
			while(i+1<length)
			{
				if(formula[i+1]=='.')
					if(dot)
					return false;
					else
					dot = true;
				else if(!(formula[i+1]>47&&formula[i+1]<58))
				break;
				
				i++;
			}
		}
		else if(formula[i]>96&&formula[i]<(96+1+3))
		{
			if(flag) return false;//If there is number right before
			flag = true;
			//cout<<"A"<<endl;
		}
		else
		{
			switch (formula[i])
			{
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':
				case '=':
				case '&':
				case '|':
				case '^': //
				case '<':
				case '>':
					//cout<<"OP"<<endl;
					if(flag)
					flag = false;
					else
					return false;
					break;
				default:
					return false;
			}
		}
	}
	//cout<<0<<endl;
	if(flag||brackets.empty())
	return true;
	else
	return false;
}

string In2Pos(string formula)
{
	char fore;
	string first,second;
	stack<string> num;
	stack<char> ope;
	stack<char> mid;
	int length = formula.size();
	char temp;
	for(int i=0;i<length;i++)
	{
		temp = formula[i];
		if(isnumber(temp))
		{
			string dec = temp+"";
			while(i+1<length)
			{
				if(isnumber(formula[i+1]))
					dec = dec+formula[i+1];
				else
					break;
				i++;
			}
			num.push(dec);
		}
		else
		{
			int level = precede(temp);
			if(level==7)
			{
				
			}
			else if(level==6||level==5)
			ope.push(temp);
			else if(level>0)
			{
				fore = ope.top();
				while(precede(fore)>level)
				{
					ope.pop();
					second = num.top();
					num.pop();
					first = num.top();
					num.pop();
					first = first+second+fore;
					num.push(first);
				}
			}
		}
	}
}
bool isnumber(char temp)
{
	if((temp>47&&temp<58)||temp=='.')
	return true;
	else
	return false;
}
int precede(char temp)
{
	int l;
	switch(temp){
		case ')':
		case ']':
		case '}':l=7;break;
		case '(':
		case '[':
		case '{':l=6;break;
		
		case '^':l=5;break;
		case '*':
		case '/':
		case '%':l=4;break;
		case '+':
		case '-':l=3;break;
		case '&':
		case '|':l=2;break;
		case '=':
		case '<':
		case '>':l=1;break;
	}
	return l;
}
