#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool turnpike(vector<int> & x,multiset<int> d,int n)
{
    bool place(vector<int> & x,multiset<int> & d,int n,int left,int right);
    x[1]=0;                     //令第一个点的坐标为0
    x[n]=*d.rbegin();           //最大距离为最后一个点的坐标
    d.erase(--d.end());         //从距离集中删除该距离

    x[n-1]=*d.rbegin();         //放置下一个最大距离点，根据对称性，该点放在x[2]或者x[n-1]得到的解互为镜像
    d.erase(--d.end());

    if(d.find(x[n]-x[n-1])!=d.end())
    {
        d.erase(d.find(x[n]-x[n-1]));   //不能直接删除值，因为会删除所有相同的值
        return place(x,d,n,2,n-2);      //放置其余的点
    }
    else
        return false;
}
//x存放结果，d为距离集，n为点个数
bool place(vector<int> & x,multiset<int> & d,int n,int left,int right)
{
    int dmax;
    bool found=false;

    if(d.size()==0)                 //距离集空，表明所有点放完，得到正确的答案
        return true;

    dmax=*d.rbegin();

    bool test=true;                 //测试放置的点是否正确
    multiset<int> tmp;              //临时集合

    //先测试放在右边x[right]=dmax

    //左半部分，因为左半部分和右半部分相对于x[right]的距离可能相同，因此需要删除左半部分已经找到的值。
    //避免一值两用
    for(int j=1;j<left;++j)
        if(d.find(dmax-x[j])==d.end())      //如果不存在该距离，则放置错误
        {
            test=false;
            break;
        }
        else
        {
            tmp.insert(dmax-x[j]);
            d.erase(d.find(dmax-x[j]));
        }
    //测试右半部分
    if(test)
    {
        for(int j=right+1;j<=n;++j)
            if(d.find(x[j]-dmax)==d.end())
            {
                test=false;
                break;
            }
    }
    //将左半部分删除的值插入回去
    for(auto itr=tmp.begin();itr!=tmp.end();++itr)
    {
        d.insert(*itr);
    }

    //如果x[right]放置正确
    if(test)
    {
        x[right]=dmax;

        //删除对应的距离
        for(int j=1;j<left;++j)
            d.erase(d.find(dmax-x[j]));

        for(int j=right+1;j<=n;++j)
            d.erase(d.find(x[j]-dmax));

        //接着放置剩下的点
        found=place(x, d, n, left, right-1);

        //如果后面的所有情况全部失败，表明该点放置错误。则撤销这步操作，重新插入距离
        if(!found)
        {
            for(int j=1;j<left;++j)
                d.insert(dmax-x[j]);
            for(int j=right+1;j<=n;++j)
                d.insert(x[j]-dmax);

        }
    }


    //测试放在左边x[left]=x[n]-dmax
    if(!found)
    {

        //和测试右边right相同
        test=true;
        tmp.clear();

        for(int j=1;j<left;++j)
            if(d.find(x[n]-dmax-x[j])==d.end())
            {
                test=false;
                break;
            }
            else
            {

                tmp.insert(x[n]-dmax-x[j]);
                d.erase(d.find(x[n]-dmax-x[j]));
            }
        if(test)
        {
            for(int j=right+1;j<=n;++j)
                if(d.find(x[j]-x[n]+dmax)==d.end())
                {
                    test=false;
                    break;
                }
        }

        for(auto itr=tmp.begin();itr!=tmp.end();++itr)
        {
            d.insert(*itr);
        }


        if(test)
        {


            x[left]=x[n]-dmax;

            for(int j=1;j<left;++j)
                d.erase(d.find(x[n]-dmax-x[j]));

            for(int j=right+1;j<=n;++j)
                d.erase(d.find(x[j]-x[n]+dmax));

            found=place(x, d, n, left+1, right);

            if(!found)
            {
                for(int j=1;j<left;++j)
                    d.insert(x[n]-dmax-x[j]);
                for(int j=right+1;j<=n;++j)
                    d.insert(x[j]-x[n]+dmax);

            }
        }

    }
    return found;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    int n=6;
    multiset<int> d={1,2,2,2,3,3,3,4,5,5,5,6,7,8,10};
    vector<int> x(n+1);
    turnpike(x, d, n);
    for(int i=1;i<=n;++i)
    {
        cout<<x[i]<<endl;
    }
    std::cout << "Hello, World!\n";
    return 0;
    getchar();
}
