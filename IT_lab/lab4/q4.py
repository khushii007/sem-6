class stringFunc:
    def get_string(self):
        str = input("Enter string:")
        return str
    
    def print_string(self,str):
        uppercaseString = str.upper()
        print(uppercaseString)
        
str = stringFunc().get_string()
stringFunc().print_string(str)