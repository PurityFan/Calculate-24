/*
node ���ڼ�¼�㵽ans�ļ������
    order ��ʾ����4������ʹ��˳��ļ�¼
    sign ��ʾ����a b������ŵļ�¼��1-6����˳��ֱ��ʾ a+b a*b a-b b-a a/b b/a
num ���ڼ�¼������4������
used ���ڼ�¼�������Ƿ�ʹ�ù�
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;
struct node
{
    int order[5];
    int sign[5];
};
void calculate_24();
bool dfs(int cnt,double num, node rec);
void print(node rec);
int num[5];
bool used[5];
const double eps = 1e-7;

int main()
{
    cout << "Please Input 4 numbers(from 1 to 13): " ;
    cin >> num[1] >> num[2] >> num[3] >> num[4];
    calculate_24();
    return 0;
}

void calculate_24()
{
    for(int i = 1;i <= 4;i++) used[i] = 0;
    node rec;
    if(!dfs(0,0,rec))
        cout << "sorry! There is no way to calculate 24 from this four numbers." << endl;
    return ;
}
bool dfs(int cnt,double ans, node rec)
{
    if(cnt == 4)
    {
        if(fabs(24.0 - ans) < eps){
        print(rec);
        return true;
        }
    }
    if(cnt == 0){
        for(int i = 1;i <= 4;i++){
            used[i] = 1;
            cnt++;
            rec.order[1] = num[i];
            rec.sign[cnt] = 1;
            if(dfs(cnt,ans + num[i],rec)) return true;
            cnt--;
            used[i] = 0;
        }
    }
    else{
        for(int i = 1;i <= 4;i++){
            if(used[i] == 1) continue;
            used[i] = 1;
            cnt++;
            rec.order[cnt] = num[i];
            rec.sign[cnt] = 1;
            if(dfs(cnt,ans + num[i],rec)) return true;
            rec.sign[cnt] = 2;
            if(dfs(cnt,ans * num[i],rec)) return true;
            rec.sign[cnt] = 3;
            if(dfs(cnt,ans - num[i],rec)) return true;
            rec.sign[cnt] = 4;
            if(dfs(cnt,num[i] - ans,rec)) return true;
            rec.sign[cnt] = 5;
            if(dfs(cnt,ans / num[i],rec)) return true;
            rec.sign[cnt] = 6;
            if(dfs(cnt,num[i] / ans,rec)) return true;
            used[i] = 0;
            cnt--;
        }
    }
    return false;
}
void print(node rec)
{
    cout << "Yes! We find it !" << endl;
    vector <string> putans;
    string word;
    stringstream ss;
    ss << rec.order[1];
    word = ss.str();
    putans.push_back(word);
    for(int i = 2;i <= 4;i++){
        stringstream ss;
        ss << rec.order[i];
        word = ss.str();
        if(rec.sign[i] == 1){
            putans.push_back("+");
            putans.push_back(word);
        }
        else if(rec.sign[i] == 2){
            putans.push_back("*");
            putans.push_back(word);
        }
        else if(rec.sign[i] == 3){
            putans.push_back("-");
            putans.push_back(word);
        }
        else if(rec.sign[i] == 4){
            putans.insert(putans.begin(),"-");
            putans.insert(putans.begin(),word);
        }
        else if(rec.sign[i] == 5){
            putans.push_back("/");
            putans.push_back(word);
        }
        else if(rec.sign[i] == 6){
            putans.insert(putans.begin(),"/");
            putans.insert(putans.begin(),word);
        }
        if(i != 4){
            putans.insert(putans.begin(),"(");
            putans.push_back(")");
        }
    }
    for(int i = 0;i < putans.size();i++)
        cout << putans[i] ;
    cout << endl;
    return ;
}
