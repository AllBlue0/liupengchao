class Solution {
public:
    int lengthOfLastWord(string s) {
        int i = s.size() - 1;

        while(s[i] == ' '){
            i--;
        }
        int worldlenth = 0;
        while(i >= 0 && s[i] != ' '){
            worldlenth++;
            i--;
        }
        return worldlenth;
    }
};
