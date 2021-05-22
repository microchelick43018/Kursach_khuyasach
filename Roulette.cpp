#include "Roulette.h"
void Roulette::ShowMenu()
{
    cout << "1 - ��������� �� �������." << endl;

    cout << "2 - ��������� �� �������." << endl;

    cout << "3 - ��������� �� ������." << endl;

    cout << "4 - ��������� �� ���������� �����" << endl;
}

Roulette::Roulette()
{
    string colors = "grbrbrbrbrbbrbrbrbrrbrbrbrbrbbrbrbrbr";
    for (int i = 0; i < 37; i++)
    {
        _cells[i] = colors[i];
    }
}

int Roulette::Play(int bet)
{
    FileManager::IncGameCount();
    int chosenNumber = -1;
    ShowMenu();
    int choice = MakeAChoice(4);
    if (choice == 4)
    {
        cout << "�������� ����� (0 - 36): " << endl;
        chosenNumber = MakeAChoice(0, 36);
    }
    cout << "������ ������� � ��������� �����..." << endl;
    this_thread::sleep_for(2s);
    int droppedNumber = rand() % 37;
    char droppedColor = _cells[droppedNumber];
    cout << "�������� �����: " << droppedNumber << ", ";
    switch (droppedColor)
    {
    case 'g':
        cout << "������� ������." << endl;
        break;
    case 'r':
        cout << "������� ������." << endl;
        break;
    case 'b':
        cout << "������ ������." << endl;
        break;
    default:
        break;
    }
    if (chosenNumber != -1)
    {
        if (chosenNumber == droppedNumber)
        {
            cout << "����������� ��� ������� �������� " << bet * 36 << " (36x)!" << endl;
            return bet * 36;
        }
        else
        {
            cout << "������ �� �������." << endl;
            return 0;
        }
    }
    else if (_cells[choice - 1] == droppedColor)
    {
        cout << "����������� ��� ������� �������� " << bet * 2 << " (2x)!" << endl;
        return bet * 2;
    }
    cout << "������ �� �������." << endl;
    return 0;
}