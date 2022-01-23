class Solution {
public:
    string replaceSpace(string s) {
        int count = 0;
        int sOldsize = s.size();
        for(int i = 0; i < sOldsize; i++){
            if(s[i] == ' '){
                count++;
            }
        }
        s.resize(s.size() + count * 2);
        int sNewsize = s.size();
        for(int i = sNewsize - 1, j = sOldsize - 1; i > 0; i--, j--){
            if(s[j] != ' '){
                s[i] = s[j];
            }else{
                s[i] = '0';
                s[i-1] = '2';
                s[i-2] = '%';
                i -= 2;
            }
        }
        return s;
    }
};