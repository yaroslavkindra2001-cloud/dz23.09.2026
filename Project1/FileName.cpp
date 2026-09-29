#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool ValidateHTML(string fileName)
{
    ifstream file(fileName);    

    if (!file.is_open())
    {
        cout << "Не удалось открыть файл" << endl;
        return false;
    }

    string text;
    string line;

    while (getline(file, line))
    {
        text += line;
    }

    file.close();

    int openTags = 0;

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == '<')
        {
            int j = i + 1;

            while (j < text.length() && text[j] != '>')
            {
                j++;
            }

            if (j == text.length())
            {
                cout << "Ошибка: знак '<' не имеет закрывающего '>'." << endl;
                return false;
            }

            string tag = "";

            int k = i + 1;

            if (text[k] == '/')
            {
                k++;
            }

            while (k < j && text[k] != ' ' && text[k] != '\t')
            {
                tag += text[k];
                k++;
            }

            if (text[i + 1] == '/')
            {
                openTags--;

                if (openTags < 0)
                {
                    cout << "Ошибка: закрывающий тег без открывающего." << endl;
                    return false;
                }
            }
            else if (text[j - 1] == '/')
            {
            }
            else if (text[i + 1] == '!')
            {
            }
            else if (tag == "meta" ||
                tag == "link" ||
                tag == "br" ||
                tag == "hr")
            {
            }
            else
            {
                openTags++;
            }

            i = j;
        }
    }

    if (openTags != 0)
    {
        cout << "Ошибка: не все открытые теги закрыты." << endl;
        return false;
    }

    return true;
}

int main()
{
    system("chcp 65001");

    string fileName;

    cout << "Введите путь к HTML файлу: ";
    cin >> fileName;

    if (ValidateHTML(fileName))
    {
        cout << "файл валиден" << endl;
    }
    else
    {
        cout << "файл невалиден" << endl;
    }

    return 0;
}