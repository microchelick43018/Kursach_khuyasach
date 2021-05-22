#include "Roulette.h"
void Roulette::ShowMenu()
{
    cout << "1 - Поставить на зеленое." << endl;

    cout << "2 - Поставить на красное." << endl;

    cout << "3 - Поставить на черное." << endl;

    cout << "4 - Поставить на конкретное число" << endl;
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
        cout << "Выберите число (0 - 36): " << endl;
        chosenNumber = MakeAChoice(0, 36);
    }
    cout << "Крутим рулетку и запускаем шарик..." << endl;
    this_thread::sleep_for(2s);
    int droppedNumber = rand() % 37;
    char droppedColor = _cells[droppedNumber];
    cout << "Выпавшее число: " << droppedNumber << ", ";
    switch (droppedColor)
    {
    case 'g':
        cout << "зеленая ячейка." << endl;
        break;
    case 'r':
        cout << "красная ячейка." << endl;
        break;
    case 'b':
        cout << "чёрная ячейка." << endl;
        break;
    default:
        break;
    }
    if (chosenNumber != -1)
    {
        if (chosenNumber == droppedNumber)
        {
            cout << "Поздравляем ваш выйгрыш составил " << bet * 36 << " (36x)!" << endl;
            return bet * 36;
        }
        else
        {
            cout << "Ставка не сыграла." << endl;
            return 0;
        }
    }
    else if (_cells[choice - 1] == droppedColor)
    {
        cout << "Поздравляем ваш выйгрыш составил " << bet * 2 << " (2x)!" << endl;
        return bet * 2;
    }
    cout << "Ставка не сыграла." << endl;
    return 0;
}