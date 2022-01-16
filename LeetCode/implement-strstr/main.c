class Solution {
public:
    int strStr(string haystack, string needle) {
        // 建立偏移表
        int hSize=haystack.size();
        int nSize=needle.size();
        unordered_map<char, int> pianyi;
        for(int i=0;i<nSize;i++) pianyi[needle[i]]=nSize-i;

        // 遍历
        int i=0;
        while(i<=hSize-nSize){
            if(haystack.substr(i,nSize)==needle) return i;
            else{
                // 查询substr后的字符的偏移值
                if(i+nSize>hSize-1) return -1;
                else{
                    if(pianyi.find(haystack[i+nSize])!=pianyi.end()){
                        i+=pianyi[haystack[i+nSize]];
                    }
                    else{
                        i+=nSize+1;
                    }
                }
            }
        }

        return -1;
    }
};
