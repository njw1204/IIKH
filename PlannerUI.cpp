#include "PlannerUI.h"
#include "RecipeUI.h"
#include "RecipeDatabase.h"
#include "Date.h"
#include "Plan.h"
#include "util.h"
#include <climits>
#include <cstdlib>
using namespace std;


void PlannerUI::showPlannerForm()
{
    if (rdb.getRecipesList().empty())
    {
        cout << endl;
        cout << " You don't have any recipes!" << endl;
        cout << " Please add some recipes to the database." << endl;
        cout << endl;
        cout << " Press Enter to Continue... ";
        waitEnter();
        return;
    }

    Plan plan;
    vector<Date>& dates = plan.getDates();

    for (int i = 1; ; i++)
    {
        system("cls");
        cout << endl;
        cout << " ######################" << endl;
        cout << " ##                  ##" << endl;
        cout << " ##   Meal Planner   ##" << endl;
        cout << " ##                  ##" << endl;
        cout << " ######################" << endl;

        for (int j = 1; j < i; j++) {
            cout << endl;
            cout << endl;
            cout << " [No." << j << "]" << endl;
            cout << " " << dates.back().toString() << " Saved." << endl;;
        }

        int year, month, day;
        Date date;

        cout << endl;
        cout << endl;
        cout << " [Day " << i << "]" << endl;
        cout << " Date (yyyy mm dd) (Input -1 to save & print a file) : ";
        cin >> year;

        if (year == -1)
        {
            system("cls");
            Plan plan;
            plan.setDates(dates);
            plan.printPlan();
            plan.writePlanToFile("plan");

            cin.ignore(INT_MAX, '\n');
            cout << endl;
            cout << " Success! Write the plan to \"plan.txt\". Check the file." << endl;
            cout << " Press Enter to Continue... ";
            waitEnter();
            break;
        }
        
        cin >> month >> day;
        cin.ignore(INT_MAX, '\n');
        
        if (!date.init(year, month, day))
        {
            cout << endl;
            cout << " Invalid Date! Please write again." << endl;
            cout << " Press Enter to Continue... ";
            waitEnter();
            i--;
            continue;
        }

        makeDailyPlan(date);
        dates.push_back(date);
    }
}

void PlannerUI::makeDailyPlan(Date& date)
{
    RecipeUI rui = RecipeUI(rdb);

    while (true)
    {
        system("cls");
        cout << endl;
        cout << "  Daily Plan Menu (" << date.toString() << ")" << endl;
        cout << endl;
        cout << " #############################" << endl;
        cout << " ##                         ##" << endl;
        cout << " ##   1. Add to Breakfast   ##" << endl;
        cout << " ##   2. Add to Lunch       ##" << endl;
        cout << " ##   3. Add to Dinner      ##" << endl;
        cout << " ##   4. Set People Count   ##" << endl;
        cout << " ##   5. Show daily plan    ##" << endl;
        cout << " ##   0. Save & Exit        ##" << endl;
        cout << " ##                         ##" << endl;
        cout << " #############################" << endl;
        cout << endl;

        cout << "  Select Operation Number : ";
        int selector;
        cin >> selector;
        cin.ignore(INT_MAX, '\n');

        int mealType;
        Recipe recipe(-1);
        
        switch (selector)
        {
        case 0:
            return;

        case 1: case 2: case 3:
            mealType = selector;

            system("cls");
            cout << endl;
            cout << " Pick a recipe that you want to add" << endl;
            cout << endl;

            recipe = rdb.getRecipe(rui.showRecipeList());
            switch (mealType)
            {
            case 1:
                date.getBreakfast().addMenu(recipe);
                break;
            case 2:
                date.getLunch().addMenu(recipe);
                break;
            case 3:
                date.getDinner().addMenu(recipe);
            }

            break;

        case 4:
            int breakfastP, lunchP, dinnerP;
            cout << endl;
            cout << " 1) Breakfast People Count : ";
            cin >> breakfastP;
            cout << " 2) Lunch People Count : ";
            cin >> lunchP;
            cout << " 3) Dinner People Count : ";
            cin >> dinnerP;
            date.getBreakfast().setPeople(breakfastP);
            date.getLunch().setPeople(lunchP);
            date.getDinner().setPeople(dinnerP);

            cin.ignore(INT_MAX, '\n');
            cout << endl;
            cout << " Commited." << endl;
            cout << " Press Enter to Continue... ";
            waitEnter();
            break;

        case 5:
            vector<Date> tempDates;
            Plan plan;
            tempDates.push_back(date);
            plan.setDates(tempDates);

            system("cls");
            plan.printPlan();
            cout << endl;
            cout << " Press Enter to Continue... ";
            waitEnter();
        }
    }
}