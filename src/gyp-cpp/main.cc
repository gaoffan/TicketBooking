#include <node.h>
#include <string>
#include <iostream> 
#include <fstream>
using namespace std;

namespace demo{
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Value;
    using v8::Number;

    // Method1 实现一个 输出"hello world ONE !" 的方法
    void buyticket(const FunctionCallbackInfo<Value>& args){
Isolate* isolate = args.GetIsolate();
//void (const string riqi, const string gotime, const string checi, const string qidian, const string zhongdian, int level, const string zuowei)
Local<String> riqi1 = Local<String>::Cast(args[0]); 
Local<String> gotime1 = Local<String>::Cast(args[1]); 
Local<String> checi1 = Local<String>::Cast(args[2]); 
Local<String> qidian1 = Local<String>::Cast(args[3]); 
Local<String> zhongdian1 = Local<String>::Cast(args[4]); 
Local<Number> dengji = Local<Number>::Cast(args[5]); 
Local<String> zuowei1 = Local<String>::Cast(args[6]); 


	ofstream outf;
	outf.open("ticket.txt", ios::app);
	
	outf << riqi1->StringValue() << gotime1->StringValue() << checi1->StringValue() << qidian1->StringValue() << zhongdian1->StringValue() << dengji->NumberValue() << zuowei1->StringValue() << endl;
	outf.close();
	        args.GetReturnValue().Set(String::NewFromUtf8(isolate, "成功了！"));
/*
	int j=0, i=0;
	for (; j <= num; j++)
	{
		for (; i < ticket[j].zhanshu; i++)
		{

			if (checi1 == ticket[j].checi)
				switch (dengji)
				{
				case 1: {ticket[j].erdengzuo - 1; }break;
				case 2: {ticket[j].yidengzuo - 1; }break;
				case 3: {ticket[j].erdengzuo - 1; }break;
				}
		}
	}
	save();
*/
    }

    // Method2 实现一个 加一 的方法
    void Method2(const FunctionCallbackInfo<Value>& args){
        Isolate* isolate = args.GetIsolate();
        // 获取参数，js Number 类型转换成 v8 Number 类型 
        Local<Number> value = Local<Number>::Cast(args[0]); 
        double num = value->NumberValue() + 1;

        // double 转 char*，这里我不知道有没有其他办法
        char buf[128] = {0};
        sprintf(buf,"%f", num);

        args.GetReturnValue().Set(String::NewFromUtf8(isolate, buf));
    }

    void init(Local<Object> exports){
        NODE_SET_METHOD(exports, "buyticket", buyticket);
        NODE_SET_METHOD(exports, "addOne", Method2);
    }

    NODE_MODULE(addon, init)
}
/*

#include <iomanip> 
#include <stdlib.h> 

#include <ctime> 
#include <conio.h> 
#include <windows.h>
#include <memory.h> 
#include<cstdio>

class zhandian
{
public:
	string name;
	string time;
	int price;
};

class train
{
public:
	int zhanshu;
	string checi;
	zhandian abc[10];
	int yidengzuo;
	int erdengzuo;
	int shangwuzuo;
};
train ticket[10];
int num = -1;

void readfile(const char *s)
{
	string chezhan;
	ifstream inf(s);
	if (!inf)
	{
		cout << "cannot open the file\n";
		return;
	}

	inf.eof();
	do
	{
		num++;
		inf >> ticket[num].checi >> ticket[num].shangwuzuo >>
			ticket[num].yidengzuo >> ticket[num].erdengzuo >> ticket[num].zhanshu;

		for (int i = 0; i < ticket[num].zhanshu; i++)
		{
			inf >> ticket[num].abc[i].name >> ticket[num].abc[i].time >> ticket[num].abc[i].price;

		}
	} while (!inf.eof());
}
string chaxun1(const string a, const string b)

{
	int x = 0;
	string str;
	int i = 0, j = 0;
	for (; j <= num; j++)
	{
		for (; i < ticket[j].zhanshu; i++)
		{
			if (a == ticket[j].abc[i].name)
			{
				for (int c = i; c < ticket[j].zhanshu; c++)
				{
					if (b == ticket[j].abc[c].name)
					{
						x = 1;

						for (int d = i; d <= c; d++)
						{
							str += ticket[j].abc[d].name;
							str += ticket[j].abc[d].time;



						}
						int p = ticket[j].abc[c].price - ticket[j].abc[i].price;
						char m[10];
						sprintf_s(m, "%d", p);
						str += m;
					}

				}

			}


		}
	}
	if (x == 0)
		str = "未找到对应站点!";
	return str;
}
string chaxun2(const string c)

{
	int x = 0;
	string str;
	int i = 0, j = 0;
	for (; j <= num; j++)
	{
		for (; i < ticket[j].zhanshu; i++)
		{
			
			if (c == ticket[j].checi)
			{
				x = 1;
				for (int a = 0; a < ticket[j].zhanshu; a++)
				{
					str += ticket[j].abc[a].name;
					str += ticket[j].abc[a].time;
				}
				int p = ticket[j].abc[ticket[j].zhanshu-1].price-ticket[j].abc[0].price;
				char m[10];
				sprintf_s(m, "%d", p);
				str += m;

			}

		}

	}
	if (x == 0)
		str = "未找到对应站点!";
	return str;
}
void save()
{
	ofstream file("data.txt", ios::out);
	for (int j = 0; j <= num; j++)
	{
		file << ticket[j].checi << " ";
		file << ticket[j].shangwuzuo << " ";
		file << ticket[j].yidengzuo << " ";
		file << ticket[j].erdengzuo << " ";
		file << ticket[j].zhanshu << " ";
		for(int q=0;q<ticket[j].zhanshu;q++)
		{
			file << ticket[j].abc[q].name << " ";
			file << ticket[j].abc[q].time << " ";
			file << ticket[j].abc[q].price << " ";//此处与录入格式不同，带空格
		}
	}
	file.close();
}
string del(string sc)
{
	string fanhui;
	int i, j;
	for (i = 0; i <= num; i++)
	{
		if (sc == ticket[i].checi)
		{
			for (j = i + 1; j <= num; j++)
			{
				ticket[j - 1] = ticket[j];
			}
			fanhui = "删除成功！";
			break;
		}
	}
	if (i > num)
		fanhui = "对不起，没有有关此站点的车次信息！";
	else
	{
		num--;
		save();
		

	}
	return fanhui;
}


*/