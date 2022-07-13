#include <iostream>
#include <cstring>
#include <unordered_map>

#include <cctype>
#include <iomanip>
#include <sstream>
using namespace std;


//pasar a C++: http://www.geekhideout.com/downloads/urlcode.c
//https://stackoverflow.com/questions/154536/encode-decode-urls-in-c/4823686#4823686
string urlDecode(string &SRC) 
{
    string ret;
    char ch;
    int i, ii;
    for (i=0; i<SRC.length(); i++) 
    {
        if (int(SRC[i])==37) 
        {
            sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } 
        else if (int(SRC[i])==43) 
        { 
            ret += ' ';
        } 
        else 
        {
            ret+=SRC[i];
        }
    }
    return (ret);
}

//Lucas Osacar Discovery: 
//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
unordered_map<string, string> generateUriMap(string uri)
{
    unordered_map<string, string> m;
    string equal = "=";
    string ampersand = "&";
    size_t pos = 0;
    string key;
    string value;
    while ((pos = uri.find(equal)) != std::string::npos) 
    {
        key = uri.substr(0, pos);
        uri.erase(0, pos + equal.length());
        value = uri.substr(0,uri.find(ampersand));
        uri.erase(0, uri.find(ampersand) + ampersand.length());
        //cout << value << endl;
        //filtering or sanitize
        key = urlDecode(key);
        value = urlDecode(value);
        
        m[key]= value;
    }
    return m;
}

int main()
{
    /*https://cybmeta.com/meta-charset-como-y-por-que-utilizarlo-siempre*/
    cout << "Content-type:text/html; charset=utf-8\r\n\r\n";
    cout << "<!DOCTYPE html>\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>Hello World - Second CGI Program</title>\n";
    cout << "<meta charset='utf-8'>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<form action='hello_world_cgi_refact_04.exe' method='post'>";
    cout << "<label>Name:</label>\n";
    cout << "<input type='text' name='name'>\n";
    cout << "<label>Surname:</label>\n";
    cout << "<input type='text' name='surname'>\n";
    cout << "<input type='submit' name='sbmt' value='enviar'>\n";
    cout << "</form>\n";

    string str = "";
    cin >> str;
    if (str != "")
    {
        unordered_map<string,string> uriMap = generateUriMap(str);
        cout << "<h2>Hello! your name is: " << uriMap["name"] << "</h2>\n";
        cout << "<h2>your surname is: " << uriMap["surname"] << "</h2>\n";
    }

    cout << "</body>\n";
    cout << "</html>\n";
    return 0;
}
