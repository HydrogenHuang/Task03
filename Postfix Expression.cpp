#include <iostream>
#include <cmath>
#include <stack>
#include <string>

using namespace std;

bool IsValid(string);
string In2Pos(string);
bool isnumber(char);
int precede(char);
float Evaluate(string,float,float,float);

int main()
{
	int a,b,c;
	string formula;
	string post_expresion;
	cout<<"变量初始化：\na=";
	cin>>a;
	cout<<"b=";
	cin>>b;
	cout<<"c=";
	cin>>c;
	
	cout<<"输入表达式：\n"; 
	cin>>formula;
	if(IsValid(formula))
	{
		cout<<"Yes"<<endl;
		post_expresion = In2Pos(formula);
		cout<<post_expresion<<endl;
		cout<<Evaluate(post_expresion,a,b,c)<<endl;
	}
	else
	cout<<"No"<<endl;
	
	return 0;
}

bool IsValid(string formula)
/*
Pre:输入函数为标准的中缀表达式，只有整数,没有单目运算符，如++，-2之类的，否则检测结果不准确。 
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
	string first,second,result;
	stack<string> num;
	stack<char> ope;
	int length = formula.size();
	char temp;
	for(int i=0;i<length;i++)
	{
		temp = formula[i];
		if(isnumber(temp))
		{
			string integar = "\0";
			integar = integar+temp;
			num.push(integar);
		}
		else //operator
		{
			if(ope.empty())
			{
				ope.push(temp);
				continue;
			}
			int level = precede(temp);
			if(level==-2)
			{
				fore = ope.top();
				while(precede(fore)!=-1)
				{
					ope.pop();
					second = num.top();
					num.pop();
					first = num.top();
					num.pop();
					first = first+second+fore;
					num.push(first);
					fore = ope.top();
				}
				ope.pop();
			}
			else if(level==-1||level==5)
			ope.push(temp);
			else if(level>=0)
			{
				fore = ope.top();
				while(precede(fore)>=level)
				{
					ope.pop();
					second = num.top();
					num.pop();
					first = num.top();
					num.pop();
					first = first+second+fore;
					num.push(first);
					
					if(!ope.empty())
					fore = ope.top();
					else
					break;
				}
				ope.push(temp);
			}
		}
	}
	while(!ope.empty())
	{
		fore = ope.top();
		ope.pop();
		second = num.top();
		num.pop();
		first = num.top();
		num.pop();
		first = first+second+fore;
		num.push(first);
	}
	result = num.top();
	return result;
}

bool isnumber(char temp)
{
	if((temp>47&&temp<58)||(temp>96&&temp<(96+1+3)))
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
		case '}':l=-2;break;
		case '(':
		case '[':
		case '{':l=-1;break;
		
		case '^':l=5;break;
		case '*':
		case '/':
		case '%':l=4;break;
		case '+':
		case '-':l=3;break;
		case '<':
		case '>':l=2;break;
		case '&':
		case '|':l=1;break;
		case '=':l=0;break; 
	}
	return l;
}

float Evaluate(string post_expresion,float a,float b,float c)
{
	stack<float> num;
	float x1,x2;
	int length = post_expresion.size();
	char temp;
	for(int i=0;i<length;i++)
	{
		temp = post_expresion[i];
		if(isnumber(temp))
		{
			switch(temp){
				case 'a':num.push(a);break;
				case 'b':num.push(b);break;
				case 'c':num.push(c);break;
				default: num.push(float(temp-48));
			}
		}
		else
		{
			x2 = num.top();
			num.pop();
			x1 = num.top();
			num.pop();
			//cout<<x1<<' '<<x2<<endl;
			switch(temp){
				case '^':x1=pow(x1,x2);break;
				case '*':x1=x1*x2;break;
				case '/':x1=x1/x2;break;
				case '%':x1=float(int(x1)%int(x2));break;
				case '+':x1=x1+x2;break;
				case '-':x1=x1-x2;break;
				case '<':x1=x1<x2;break;
				case '>':x1=x1>x2;break;
				case '&':x1=x1&&x2;break;
				case '|':x1=x1||x2;break;
				case '=':x1=x1==x2;break;
			}
			num.push(x1);
		}
	}
	return num.top();
}
