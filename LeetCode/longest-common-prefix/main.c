class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) 
    {
        set<string> Result;
        for (auto str : strs)
            Result.insert(str);

        string firststr = *Result.begin();
        string laststr = *Result.rbegin();
        string result0;
        int num = 1;
        while (1)
        {
            if (num > firststr.size() || num > laststr.size())
            {
                break;
            }
            
            string tmp1(firststr,0,num);
            string tmp2(laststr, 0, num);
            if (tmp1 == tmp2)
            {
                result0 = tmp1;
                num++;
            }
            else
                break;
        }
	    return result0;
    }
};
