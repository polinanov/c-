#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <regex>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class HTTP{
    public:
        //HTTP();
        string httpGet(string name);
        string httpPost(string name);
        string getCookie(string name);
        string setCookie(string name, string value);
        void sendCookie();
        void fin_header();


        void showData();
        void getData_();
        char from_hex(char ch);
        string url_decode(string text);
        int ascii_code(string x);
        string space_ch(string change);
        void parsing_cookie(string str);
        void parsing();
        void handlingEnter();
        bool deleteData(int index);
        void setDataFile();
        void setData();

        //~HTTP();
    public:
        string Data;
        string pt_n="", pt_sur="", pt_c="", pt_d="";
        string name="", surname="", direction="", course_number="";
        vector<tuple<string, string, int, string >> students;
        tuple <string, string, int, string> student;
        map <string, string> getData;
        map <string, string> postData;
        map <string, string> cookieHeader;
        enum pattern { name_ = 0, surname_ = 1, course_number_ = 2, direction_ = 3};

};


void HTTP::sendCookie(){
    string temp;
    for (auto it = cookieHeader.begin(); it != cookieHeader.end(); ++it){
        temp = string(it->first);
        temp += "=";
        temp += string(it->second);
        cout << "Set-Cookie: " + temp << endl;
    }
    fin_header();
};


void HTTP::fin_header(){
    cout << "Content-Type: text/html; charset=utf-8" << endl << endl;
}


string HTTP::httpGet(string name){
    string temp;
    for (auto it = getData.begin(); it != getData.end(); ++it){
        if(it->first == name){
            temp = it->second;
            return temp;
        }

  }
};

string HTTP::httpPost(string name){
    string temp;
    for (auto it = postData.begin(); it != postData.end(); ++it){
        if(it->first == name){
            temp = it->second;
            return temp;
        }

  }
};

string HTTP::setCookie(string name, string value){
    cookieHeader.insert(pair<string, string>(name,value));
};

string HTTP::getCookie(string name){
    char * langPtr;
    string value, cookie;
    string::size_type i;
    i = cookie.find(name);
        while (i != string::npos) {
            cookie.erase(i, name.length());
            i = cookie.find(name, i);
        }
    cout << cookie;
    langPtr = getenv("HTTP_COOKIE");
    if (langPtr != NULL)
		cookie = getenv("HTTP_COOKIE");
    for(int i = 0; i < cookie.length(); i++){
        if(cookie[i]!='=' && cookie[i]!=';'){
            value += cookie[i];
        }else if(cookie[i]==';'){
            cout << value;
            //break;
        }
    }
};



char HTTP::from_hex(char ch) {
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

string HTTP::url_decode(string text) {
    char h;
    ostringstream escaped;
    escaped.fill('0');

    for (auto i = text.begin(), n = text.end(); i != n; ++i) {
        string::value_type c = (*i);

        if (c == '%') {
            if (i[1] && i[2]) {
                h = from_hex(i[1]) << 4 | from_hex(i[2]);
                escaped << h;
                i += 2;
            }
        }else {
            escaped << c;
        }
    }

    return escaped.str();
}

int HTTP::ascii_code(string x){
    int a;
    a = x[0];
    return a;
};

string HTTP::space_ch(string change){
    for(int i = 0; i < change.length(); i++){
        if(change[i] == '+') change[i] = ' ';
    }
    return change;
}

void HTTP::parsing_cookie(string str){
    pattern pt_pars = name_;
    pattern pt_fill = name_;
    //int pat = 0;
    string::size_type i;
    const string pattern1("student_name=");
    const string pattern2("student_surname=");
    const string pattern3("course_number=");
    const string pattern4("direction=");
    switch (pt_pars) {
        case name_:
            i = str.find(pattern1);
            while (i != string::npos) {
                str.erase(i, pattern1.length());
                i = str.find(pattern1, i);
                //pat = 0;
            }
        case surname_:
            i = str.find(pattern2);
            while (i != string::npos) {
                str.erase(i, pattern2.length());
                i = str.find(pattern2, i);
                //pat = 1;
            }
        case course_number_:
            i = str.find(pattern3);
            while (i != string::npos) {
                str.erase(i, pattern3.length());
                i = str.find(pattern3, i);
               // pat = 2;
            }
        case direction_:
            i = str.find(pattern4);
            while (i != string::npos) {
                str.erase(i, pattern4.length());
                i = str.find(pattern4, i);
                //pat = 3;
            }
            break;
        default:
            // Code
            break;
    }
    switch(pt_fill){
        case name_:
            pt_n = str;
            break;
        case surname_:
            pt_sur = str;
            break;
        case course_number_:
            pt_c = str;
            break;
        case direction_:
            pt_d = str;
            break;
    }
}

void HTTP::parsing(){
    pattern pt_pars = name_;
    string::size_type i;
    const string pattern1("student_name=");
    const string pattern2("student_surname=");
    const string pattern3("course_number=");
    const string pattern4("direction=");
    switch (pt_pars) {
        case name_:
            i = name.find(pattern1);
            while (i != string::npos) {
                name.erase(i, pattern1.length());
                i = name.find(pattern1, i);
            }
        case surname_:
            i = surname.find(pattern2);
            while (i != string::npos) {
                surname.erase(i, pattern2.length());
                i = surname.find(pattern2, i);
            }
        case course_number_:
            i = direction.find(pattern3);
            while (i != string::npos) {
                direction.erase(i, pattern3.length());
                i = direction.find(pattern3, i);
            }
        case direction_:
            i = course_number.find(pattern4);
            while (i != string::npos) {
                course_number.erase(i, pattern4.length());
                i = course_number.find(pattern4, i);
            }
            break;
        default:
            // Code
            break;
    }
}


void HTTP::handlingEnter(){
    string pattern = "key=", cookie="";
    string::size_type i;
    int key, j = 0;
    int cook = 0;
    char * langPtr;
    string kode = getenv("QUERY_STRING");

    int chtotam = ascii_code(kode);
    if(chtotam == 0){
        getData_();
    }
    else if(getenv("QUERY_STRING") != ""){
        fin_header();
        Data = getenv("QUERY_STRING");
        i = Data.find(pattern);
        while (i != string::npos) {
            Data.erase(i, pattern.length());
            i = Data.find(pattern, i);
            key = atoi(Data.c_str());
        }
        switch (key) {
            case 1:
                 langPtr = getenv("HTTP_COOKIE");
                    if (langPtr != NULL){
						cookie = getenv("HTTP_COOKIE");
                    //cout << "Cookie" << cookie << endl;
					name=""; surname=""; direction=""; course_number="";
                    for(int i=0; i<cookie.length(); i++){
                        if(cookie[i]==';'){
                            i = i+2;
                            j++;
                        }
                        switch (j) {
                            case 0:
                                name+=cookie[i];
                                break;
                            case 1:
                                surname+=cookie[i];
                                break;
                            case 2:
                                direction+=cookie[i];
                                break;
                            case 3:
                                course_number+=cookie[i];
                                break;
                            default:
                                // Code
                                break;
                        }
                    }
                    pt_n=""; pt_sur=""; pt_c=""; pt_d="";
                    parsing_cookie(name);
                    parsing_cookie(surname);
                    parsing_cookie(direction);
                    parsing_cookie(course_number);
                    name = pt_n;
                    surname = pt_sur;
                    course_number = pt_d;
                    direction = pt_c;
                  //  parsing();
                    cout << "<form action='main.cgi' method='POST'>";
                    cout << "<p>Имя студента: <input name='student_name' value='"+name+"'></p>";
                    cout << "<p>Фамилия студента: <input name='student_surname' value='"+surname+"'></p>";
                    cout << "<p>Курс <input name='course_number' value='"+direction+"'></p>";
                    cout << "<p>Направление подготовки <input name='direction' value='"+course_number+"'></p>";
                    cout << "<p><input type='submit'></p>";
                    cout << "</form>";
                    pt_n=""; pt_sur=""; pt_c=""; pt_d="";
                  }

                    else{
                        cout << "<form action='main.cgi' method='POST'>";
                        cout << "<p>Имя студента: <input name='student_name'></p>";
                        cout << "<p>Фамилия студента: <input name='student_surname'></p>";
                        cout << "<p>Курс <input name='course_number'></p>";
                        cout << "<p>Направление подготовки <input name='direction'></p>";
                        cout << "<p><input type='submit'></p>";
                        cout << "</form>";
                    }
                break;
            case 2:
                cout << "<form action='main.cgi' method='POST'>";
                cout << "<p>Выберите номер записи, которую нужно удалить: <input name='delete'></p>";
                cout << "<p><input type='submit' value='Удалить'></p>";
                cout << "</form>";
                break;
            case 3:
                showData();
                return;
                break;
            default:
                // Code
                break;
            }
    }

}

bool HTTP::deleteData(int index){
	cout << endl << "Запись " << index-1 << " удалена" << endl;
	index = index - 2;
    vector<string> vec;
    ifstream file("out.txt");

    if (file.is_open()){
        string str;
        while (getline(file, str))
            vec.push_back(str);
        file.close();
        if (vec.size() < index)
            return false;
        vec.erase(vec.begin() + index);
        ofstream outfile("out.txt");
        if (outfile.is_open()){
            copy(vec.begin(), vec.end(),
                ostream_iterator<std::string>(outfile, "\n"));
            outfile.close();
            return true;
        }
        return false;
    }
    return false;
}
void HTTP::showData(){
    string line, buff = "1|", str="";
    int j = 0, num = 1;
    ifstream in("out.txt");
    cout << "<table border='1' width='100%' cellpadding='5'>";
        cout << "<tr>";
            cout << "<th>Имя студента</th>";
            cout << "<th>Фамилия студента</th>";
            cout << "<th>Курс</th>";
            cout << "<th>Номер группы</th>";
            cout << "<th>Удалить</th>";
        cout << "</tr>";
        cout << "<tr>";
    if (in.is_open()){
        while (getline(in, line)){
            line += "\n";
        for(int k=0; k<line.length(); k++){

            if(Data[k]==' '){
                k++;
                j++;
            }
            switch (j) {
                case 0:
                  name+=line[k];
                  break;
                case 1:
                  surname+=line[k];
                  break;
                case 2:
                 direction+=line[k];
                  break;
                case 3:
                  course_number+=line[k];
                  break;
                default:
                  // Code
                  break;
                }
        }
        int dir = atoi(direction.c_str());
        tuple <string, string, int, string> student (name, surname, dir, course_number);
        students.push_back(student);
            num++;
            str = char(num)+'0';
            line +=  str+'|';
            for(int i = 0; i<line.length(); i++){
                if(line[i]==' '){
                    cout << "<td>"<< buff << "</td>";
                    buff = "";
                }
                else if(line[i] == '\n'){
                    cout << "<td>" << buff << "</td>";
                    cout << "<td><form action='main.cgi' method='POST'>";
                    cout << "<input hidden name='delete' value='"+str+"'>";
                    cout << "<input type='submit' value='Удалить'>";
                    cout << "</form></td>";
                    buff = "";
                    cout << "</tr>";
                    cout << "<tr>";
                }
                else{
                    if(line[i]=='+'){ line[i] = ' ';}
                    buff += line[i];
                }
            }cout << "</tr>";
        } cout << "</tr>";
    }
    else{
        cout << "Файл не может быть открыт!" <<endl;
        return;
    }
    cout << "</table>";
    cout << "<a href='index.html'><button>Назад</button></a>";
    in.close();
}

void HTTP::setDataFile(){
    fstream fout("out.txt", std::ios::app);
    if (!fout.is_open()) // если файл не открыт
        cout << "Файл не может быть открыт!" <<endl; // сообщить об этом
    else{
		for(auto& tuple: students) {
			fout << get<0>(tuple) << " " << get<1>(tuple) << " " << get<2>(tuple) << " " << get<3>(tuple) << endl;
		//	cout << get<0>(tuple) << " " << get<1>(tuple) << " " << get<2>(tuple) << " " << get<3>(tuple) << endl;
		}
		fout.close(); // закрываем файл
		cout << "<a href='index.html'><button>Назад</button></a>";

    }
}


void HTTP::setData(){
    string ch_name, ch_surname, ch_dir, ch_course_number;
    ch_name = name; ch_surname = surname; ch_dir = direction; ch_course_number = course_number;
    parsing();
    ch_name = space_ch(ch_name);
    ch_surname = space_ch(ch_surname);
    ch_dir = space_ch(ch_dir);
    ch_course_number = space_ch(ch_course_number);
    ch_course_number = space_ch(ch_course_number);
    cout << endl << "<p>Добавленная запись: Имя: " << ch_name << ", Фамилия: "<< ch_surname << ", курс: "<< ch_dir << ", номер группы: "<< ch_course_number << "</p>" << endl;
    int dir = atoi(direction.c_str());
    tuple <string, string, int, string> student (name, surname, dir, course_number);
    students.push_back(student);

    postData.insert(pair<string, string>("student_name",name));
    postData.insert(pair<string, string>("student_surname", surname));
    postData.insert(pair<string, string>("direction",direction));
    postData.insert(pair<string, string>("course_number",course_number));

    setDataFile();
};

void HTTP::getData_(){
    string pattern4 = "delete=";
    string::size_type i;
    bool del;
    int j = 0, index;
    if(getenv("QUERY_STRING") == ""){
        Data = getenv("QUERY_STRING");
    }else{
        cin >> Data;
        Data = url_decode(Data);
	if(Data == "show=now"){
	    fin_header();
       // cout << "Переданные данные: " << Data << endl;
		showData();
		return;
	}
        i = Data.find(pattern4);
        while (i != string::npos) {
            Data.erase(i, pattern4.length());
            i = Data.find(pattern4, i);
            fin_header();
           // cout << "Переданные данные: " << Data << endl;
            index = atoi(Data.c_str());
            del = deleteData(index);
            cout << "<a href='main.cgi?key=3'><button>Назад</button></a>";
            return;
	}
    for(int i=0; i<Data.length(); i++){
            if(Data[i]=='&'){
                i++;
                j++;
            }
            switch (j) {
                case 0:
                    name+=Data[i];
                    break;
                case 1:
                  surname+=Data[i];
                  break;
                case 2:
                    direction+=Data[i];
                    break;
                case 3:
                    course_number+=Data[i];
                    break;
                default:
                    // Code
                  break;
                }
        }
    }
	//cout << "Set-Cookie: " + name << endl;
	//cout << "Set-Cookie: " + surname << endl;
	//cout << "Set-Cookie: " + direction << endl;
	//cout << "Set-Cookie: " + course_number << endl;
	parsing();
	setCookie("student_name", name);
	setCookie("student_surname", surname);
	setCookie("direction", course_number);
	setCookie("course_number", direction);
	sendCookie();
    setData();
}

int main(){
    HTTP objHTTP;
   /* objHTTP.getData.insert(pair<string, string>("key","value"));
    objHTTP.postData.insert(pair<string, string>("student_name","Polina"));
    objHTTP.postData.insert(pair<string, string>("student_surname", "Nov ikova"));
    objHTTP.postData.insert(pair<string, string>("direction","3Vti"));
    objHTTP.postData.insert(pair<string, string>("course_number","3"));
    string temp = objHTTP.httpGet("key");
    cout << temp << endl;
    temp = "";
    temp = objHTTP.httpPost("student_surname");
    cout << temp << endl;*/
    objHTTP.handlingEnter();
  //  string msg = "%D0%BA%D0%BE%D1%88%D0%BA%D0%B0rn!";
 //   string decodemsg = url_decode(msg);
 //   cout << decodemsg << endl;

}
