bool palind(string str, int left, int right){
    if (left >= right) return true;
    else if (str[left] == ' ') return palind(str, ++left, right);
    else if (str[right] == ' ') return palind(str, left, --right);
    else if (str[left] != str[right]) return false;
    else return palind(str, ++left, --right);
}

bool isPalindrome(string str) 
{ 
  if (str.length() == 0) return false;
  int left = 0, right = str.length() - 1;
  return palind(str, left, right);
}
