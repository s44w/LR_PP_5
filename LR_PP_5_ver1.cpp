#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <limits>

using namespace std;

/*
Вариант 10: данные о прибыли, вывести дни без прибыли
Формат ввода:
    в строку:
    номер филиала, количество дней, прибыли этих дней
         2                3            100    0    50
Формат вывода:
    номер филиала, номера дней без прибыли
         2                2
*/

class ProfitDays
{
private:
    int filial;  //номер филиала
    int days;   //количество дней   
    vector <double> profit_pd; //вектор прибыли в каждый день

public:
    void set_total_days(int total_days) {
        days = total_days;    //количество дней
    }
    void set_num_filial(int number_fil) {
        filial = number_fil;   //номер филиала
    }
    void set_profit_pd(vector <double> prof) {
        profit_pd = prof;
    }


    int get_num_filial() {
        return filial;
    }
    int get_total_days() {
        return days;
    }
    vector <double> get_profit_pd() {
        return profit_pd;
    }

    double get_max_prof()
    {
        double maxc = -110000;
        for (auto c : profit_pd)
            if (c > maxc)
                maxc = c;
        return maxc;
    }

    ProfitDays() {  //конструктор по умолчанию
        filial = 1;
        days = 1;
        profit_pd.push_back(0);

    };
    ~ProfitDays()
    {
        profit_pd.clear();
    }

    vector<double> find_0_profit()
    {
        vector<double> ans;
        for (int i = 0; i < days; ++i)
            if (profit_pd[i] == 0)
                ans.push_back(i);
        return ans;
    }

    double sum_all_profits()
    {
        double sum = 0;
        for (auto c : profit_pd)
            sum += c;
        return sum;
    }

    void output_info(ostream& out)
    {
        out << '\n' << "\tFilial: " << filial << '\n'
            << "\tDays: " << days << '\n'
            << "\tProfits are: ";

        for (int i = 0; i < days; ++i)
            out << profit_pd[i] << "  ";

        vector <double> data = find_0_profit();
        if (data.size() != 0)
        {
            out << '\n' << "\tThere are " << data.size() << " days with 0 profit: ";
            for (auto c : data)
                out << (c + 1) << "  ";
            out << endl;
        }
        else
            out << '\n' << "\tThere are NO days with 0 profit" << endl;
    }
    friend istream& operator>>(istream& in, ProfitDays& PD);
    friend ifstream& operator>>(ifstream& in, vector <ProfitDays>& PD);
    friend ofstream& operator<<(ofstream& out, vector <ProfitDays>& PD_vector);
    friend ostream& operator<<(ostream& out, vector <ProfitDays>& PD_vector);
};

class Companies
{
private:
    string name;

public:
    void set_name(string oname)
    {
        name = oname;
    }
    string get_name()
    {
        return name;
    }
    bool ok = true;

    vector <ProfitDays> PD_vector_com;

    void find_best_fil(ostream& out)
    {
        int max_fil = 0; double sum = -1000000000;

            for (int i = 0; i < PD_vector_com.size(); ++i)
            {
                if (PD_vector_com[i].sum_all_profits() > sum)
                {
                    sum = PD_vector_com[i].sum_all_profits();
                    max_fil = PD_vector_com[i].get_num_filial();
                }
            }
        
        out  << "Best filial is " << max_fil << " with total profit of " << sum  << endl;
    }

    void output_company(ostream& out)
    {
        out << '\n' << "Company`s name: " << name << endl;
        for (auto c : PD_vector_com)
            c.output_info(out);
        out << '\n';
    }

    Companies()
    {
        name = "NewCompany";

    }
    ~Companies()
    {
        name.clear();
        PD_vector_com.clear();
    }
};

double profit_check(string input)
{
    /*
    Функция для прибыли, проверяет, являются ли введенные пользователем данные числом

    Если фукнция stod не срабатывает, то выводит ошибку "invalid_argument", обрабатывает ее через catch
    Если функция stod сработала, то дополнительно провяряем строку. Удаляем первое вхождение точки через erase,
    после этого циклом проходим по элементам

    Возвращает:
        number: double  число, переведенное из input: string, которое ввел пользователь
    */
    bool ok = true;
    double number = 0;
    try
    {
        number = stod(input);

        if (input.find('.') != input.npos)
            input.erase(input.find('.'), 1);

        for (int i = 1; i < input.length(); ++i)
            if (isdigit(input[i]) == false)
                throw (1);

        return number;
    }
    catch (invalid_argument)
    {
        throw runtime_error("Error(1)! Write a number!");
    }
    catch (int i)
    {
        throw runtime_error("Error(2)! Write a number!");
    }
}

int number_check(string input)
{
    /*
    Функция для филиала, дня, количества филиалов и метода ввода/вывода.
        Проверяет, являются ли введенные пользователем данные числом

    Если фукнция stoi не срабатывает, то выводит ошибку "invalid_argument", обрабатывает ее через catch
        Дополнительно сравнивает длину полученного числа с начальной строкой
    Если число меньше нуля, то выводит ошибку

    Возвращает:
        number: int  число, переведенное из input: string, которое ввел пользователь

    */
    int number = 1;
    //if (!input.empty())
    //{
    number = stoi(input);

    if (to_string(number).length() != input.length())
        throw runtime_error("Error! Number must be integer");
    if (number <= 0)
        throw runtime_error("Error! Number must be positive!");
    return number;

    //}
    //else
     //   throw runtime_error("Error! Try again");
}

int count_PD_elem()
{
    /*
    Функция возвращает количество филиалов, введенное пользователем
    */
    string str;
    bool ok = true;
    int count = 0;
    while (ok)
    {
        try
        {            
            cin >> str;

            int count = number_check(str);
            if (count > 0)
                return count;
        }
        catch (runtime_error& e)
        {
            cout << e.what() << endl;
        }
        catch (invalid_argument& e)
        {
            cout << "Error! Wrong input, try again!" << endl;
        }
        catch (out_of_range& e)
        {
            cout << e.what() << endl;
            cout << "Error! Number is too big!" << endl;
        }
    }
    return count;
}

void instruction()
{
    cout << "Input information about profit per days of your filial. " << '\n'
        << "Format: <number of filial> <days> <profit of 1st day> <profit of 2nd day>..." << '\n'
        << "Example: 1 3 10 0 20" << '\n' << endl;
}


void set_all_information(vector <double>& all_numbers, ProfitDays& PD)
{
    //Функция из заполненного числами вектора заполняет информацию об объекте
    
    int days, filial;

    if (all_numbers.size() > 0) filial = all_numbers[0];
    if (all_numbers.size() > 1 && all_numbers[1] != 0)
    {
        days = all_numbers[1];
        bool ok = (days == (all_numbers.size() - 2)); //если количество дней равно размеру вектора без первых двух значений,
        //то ввод корректен
        PD.set_num_filial(filial);
        PD.set_total_days(days);

        if (ok)
        {
            all_numbers.erase(all_numbers.begin(), all_numbers.begin() + 2);
            PD.set_profit_pd(all_numbers);
            all_numbers.clear();
        }
        else
        {
            throw runtime_error("Error! Numbers of days and profits are not equal!");
        }
    }
    else throw runtime_error("Error! Wrong input");
}

void cycle_for(string str, vector <double>& all_numbers)
{
    int numi;
    double numd;
    string curr_num;
    for (int i = 0; i < (str.length()); ++i) //прохожу по строке. пока не встречу пробел, превращаю текст в число. увидел - скипнул или удалил
    {
        if ((str[i] == ' ' && str[i + 1] == ' ') )//|| (str[0] == ' '))
        {
            throw runtime_error("Error! Wrong input, try again!");
        }
        if (str[i] != ' ' && str[i] != EOF && str[i] != '\0' && str[i] != '\n')
            curr_num += str[i];
        if ((str[i] == ' ' && str[i + 1] != ' ') || (str[i + 1] == '\0'))
        {
            if (all_numbers.size() < 2)
                (numi = number_check(curr_num), all_numbers.push_back(numi));
            else
                (numd = profit_check(curr_num), all_numbers.push_back(numd));

            curr_num = "";
        }
    }
}


void cycle_for_file(vector <double>& all_numbers, string str)
{
    /*
    Функция проверяет строку и вносит значения в вектор всех значений, он используется далее
    Аргументы:
        all_numbers: vector <double>& - ссылка на вектор всех цифр,
            введенных пользователем или полученных с файла
        srt: string - обрабатываемая строка
    */
    if (str.length() > 1) 
        cycle_for(str, all_numbers);
    else throw runtime_error("Error! Wrong input, try again!");
}

vector <double> input_data_con(istream& in)
{
    /*
    Функция получает данные с КОНСОЛИ и отдает их на проверку
    Аргументы:
        in: istream& - ссылка на поток ввода
    Выводит:
        all_numbers: <double> - вектор с готовыми значениями
    */
    //cout << "Enter 'N' to finish filling it:" << endl;

    vector <double> all_numbers;
    bool ok = true;
    cout << "Input info about your filial (example: '1 2 10 20'): " << endl;
    while (ok)
    {
        try
        {
            string str;
            getline(in, str);
            cycle_for(str, all_numbers);
            if (all_numbers.size() >= 2)
                if ((all_numbers.size() - 2) >= all_numbers[1])
                    ok = false;
        }
        catch (...)
        {
            cout << "Try again!" << endl;
        }
    }
    return all_numbers;
}

void input_data_file(string str, ProfitDays& PD)
{
    /*
    Функция получает данные с ФАЙЛА, проверяет их и передает объекту PD
    Аргументы:
        in: ifstream& - ссылка на поток ввода
        PD: ProfitDays& - тот самый объект
    */
    vector <double> all_numbers;
    cycle_for_file(all_numbers, str);
    set_all_information(all_numbers, PD);
    
}

istream& operator>>(istream& in, ProfitDays& PD)
{
    /*
    Перегрузка потока ввода в объект PD, берет данные из консоли и присваивает их объекту PD
    Аргументы:
        in: istream& - ссылка на поток ввода с консоли
        PD: ProfitDays& - объект, которому присваиваем данные
    */
    vector <double> info;

    info = input_data_con(in);
    set_all_information(info, PD);

    return in;
}

istream& operator>>(istream& in, Companies& Com)
{
    cout << '\n' << "Enter the name of your company: " << endl;
    string name;
    in >> name;
    Com.set_name(name);
    
    cout << '\n' << "Input total number of your filials: ";
    int count;
    count = count_PD_elem();

    //cout << "Input information about your filial  " << endl;
    for (int i = 0; i < count; ++i)
    {
        try {
            ProfitDays PD;
            in >> PD;
            Com.PD_vector_com.push_back(PD);
        }
        catch (runtime_error& e)
        {
            cout << e.what() << endl;
            cout << "Skipping the line" << '\n' << endl;
            --i;
        }
        catch (invalid_argument& e)
        {
            cout << e.what() << endl;
            cout << "Skipping the line..." << '\n' << endl;
            --i;
        }
        catch (out_of_range& e)
        {
            cout << "Error! Number is too big!" << endl;
            cout << "Skipping the line..." << '\n' << endl;
            --i;
        }
    }

    return in;
}
//
//ifstream& operator>>(ifstream& in, vector <ProfitDays>& PD_vector)
//{
//    /*
//    Перегрузка потока ввода в объект PD, берет данные из файла и сразу заполняет вектор объектов ProfitDays
//    Аргументы:
//        in: ifstream& - ссылка на поток ввода с файла
//        PD_vector: vector <ProfitDays> - пока что пустой вектор объектов PD
//    */
//    ProfitDays test;
//    
//    PD_vector.push_back(test);
//    
//    return in;
//}

ifstream& operator>>(ifstream& in, vector<Companies>& Com_vector)
{
    string str;
    int j = 1;
    while (getline(in, str))
    {
        try {
            Companies Com;
            string name;

            for (int i = 0; i < str.length() && str[i] != ' '; ++i)
                name += str[i];
            str.erase(str.begin(), str.begin() + name.length() + 1);

            //if (str[0] == ' ') str.erase(str.begin());

            Com.set_name(name);
            ProfitDays test;
            input_data_file(str, test);

            bool existing = false;

            for (int i = 0;!existing && i<Com_vector.size(); ++i)
                Com_vector[i].get_name() == name ? Com_vector[i].PD_vector_com.push_back(test), existing = true : existing = false; 
            
            //cout << Com_vector.size() << " " << existing << endl;
            if (!existing)
            {
                Com.PD_vector_com.push_back(test);
                Com_vector.push_back(Com);
            }
            ++j;
        }
        catch (runtime_error& e)
        {
            cout << e.what() << endl;
            cout << "Skipping the line number " << j << '\n' << endl;
            ++j;
        }
        catch (invalid_argument& e)
        {
            cout << e.what() << endl;
            cout << "Skipping the line number " << j << '\n' << endl;
            ++j;
        }
        catch (out_of_range& e)
        {
            cout << "Error! Number is too big!" << endl;
            cout << "Skipping the line number " << j << '\n' << endl;
            ++j;
        }
    }
    return in;
}

ofstream& operator<<(ofstream& out, vector <ProfitDays>& PD_vector)
{
    for (int i = 0; i < PD_vector.size(); ++i)
        PD_vector[i].output_info(out);

    return out;
}

ostream& operator<<(ostream& out, vector <ProfitDays>& PD_vector)
{
    for (int i = 0; i < PD_vector.size(); ++i)
        PD_vector[i].output_info(out);

    return out;
}

ostream& operator<<(ostream& out, vector<Companies>& Com_vector)
{
    for (int i = 0; i < Com_vector.size(); ++i)
    {
        Com_vector[i].output_company(out);
        Com_vector[i].find_best_fil(out);
    }
    return out;
}

ofstream& operator<<(ofstream& out, vector<Companies>& Com_vector)
{
    for (int i = 0; i < Com_vector.size(); ++i)
    {
        Com_vector[i].output_company(out);
        Com_vector[i].find_best_fil(out);
    }
    return out;
}

void set_console_input(int count, vector <Companies>& Com_vector)
{
    //функция заносит данные в вектор PD_vector, 
    // с помощью нее пользователь вводит строки с информацией (их количество равно count) с консоли,
    for (int i = 0; i < count; ++i)
    {
        try {
            Companies Com;
            cin >> Com;
            Com_vector.push_back(Com);
        }
        catch (runtime_error& e)
        {
            cout << e.what() << endl;
            cout << "Skipping the line" << '\n' << endl;
            --i;
        }
        catch (invalid_argument& e)
        {
            cout << e.what() << endl;
            cout << "Skipping the line..." << '\n' << endl;
            --i;
        }
        catch (out_of_range& e)
        {
            cout << "Error! Number is too big!" << endl;
            cout << "Skipping the line..." << '\n' << endl;
            --i;
        }
    }
}


void calcNset(ifstream& in, vector <Companies>& Com_vector, int count)
{
    /*
    Функция проходит по всем строкам ввода и через операторы присваивает объектам PD значения
    Аргументы:
        choose: bool - переменная, отвечает за выбор потока ввода
        in: ifstream& - поток ввода с файла
        PD_vector: vector <ProfitDays>& - вектор со всеми объектами
        count: int - количество объектов
    */
    Companies Com;
    ProfitDays PD;
    if (count)
        set_console_input(count, Com_vector);

    else
        in >> Com_vector;
}


vector <Companies> total_calc_set(int count, ifstream& in)
{
    //функция возвращает массив объектов PD, в каждом уже есть информация
    vector <Companies> arr;
    calcNset(in, arr, count);
    return arr;
}

bool YN_function()
{
    /*
    Функция узнает, вводит пользователь Y или N.
    В зависимости от этого возвращает:
        '1', если введено 'Y'
        '0', если введено 'N'
    */
    cout << '\n' << "Do you want to continue? Input 'Y' or 'N'" << endl;
    string button;
    bool end = false;
    while (!end)
    {
        getline(cin, button);
        if (button == "Y") return  true;
        else if (button == "N")  return false;
        if (button != "Y" && button != "N") cout << "Write 'Y' or 'N'!" << endl;
    }
}

bool console_or_file()
{
    bool ok = true;
    string str;
    while (ok)
    {
        getline(cin, str);
        if (str == "1") return true;
        if (str == "2") return false;
        else if (str != "1" && str != "2" && !str.empty()) cerr << "Error! Please, try again!" << endl;
    }
}

string file_choose()
{
    /*
    Функция, позволяет выбрать файл.
    Пользователь вводит название, если файл с таким названием существует, то вовзвращает его в string.
    */
    string name;
    bool ok = true;
    while (ok)
    {
        cin >> name;
        ifstream file;
        file.open("d:\\texts\\" + name + ".txt");

        if (file)
        {
            name = "d:\\texts\\" + name + ".txt";
            file.close();
            return name;
        }
        else cout << '\n' << "Error! Input correct name!" << endl;
    }
}

void output_file_data(ifstream& in)
{
    string str;
    cout << "File`s data:" << endl;
    while (getline(in, str))
        cout << str << endl;
    cout << '\n';
    in.close();
}

void user_chooses_input(vector <Companies>& test)
{
    ifstream ifile;
    bool choose_input = console_or_file();
    int counting = 0;
    if (choose_input)
    {
        cout << "You chose console" << endl;
        cout << '\n' << "Input total number of your companies: ";
        counting = count_PD_elem();

        test = total_calc_set(counting, ifile);
    }
    else
    {
        cout << "You chose file. Input its name ('input'): " << endl;
        string file_name = file_choose();

        ifile.open(file_name);
        output_file_data(ifile);

        ifile.open(file_name);
        test = total_calc_set(counting, ifile);
        ifile.close();
    }
}

void user_chooses_output(vector <Companies>& test)
{
    bool choose_output = console_or_file();

    if (choose_output)
    {
        cout << "You chose console. Your information:" << endl;
        cout << test;
    }
    else
    {
        cout << "You chose file. Input its name ('output'): " << endl;
        string file_name = file_choose();
        ofstream ofile(file_name, ios::app);
        ofile << test;
        ofile.close();
    }
}

int main()
{
    bool finish = true;
    instruction();
    while (finish)
    {
        vector <Companies> test;
        cout << "Do you want to load information from Console or from File? \n"
            << "Enter '1' to use Console  or  '2' to use File" << '\n' << "Enter: ";
        user_chooses_input(test);

        cout << "Do you want to save information to Console or to File? \n"
            << "Enter '1' to use Console  or  '2' to use File" << '\n' << "Enter: ";
        user_chooses_output(test);

        finish = YN_function();
    }
}