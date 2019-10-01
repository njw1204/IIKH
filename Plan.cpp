#include <iostream>
#include <fstream>
#include <string>
#include "Plan.h"
using namespace std;

void Plan::printPlan()
{
    writePlanToFile(cout);
}

void Plan::writePlanToFile(string filename)
{
    ofstream file;
    file.open(filename);
    writePlanToFile(file);
    file.close();
}

void Plan::writePlanToFile(ostream& file)
{
    vector<Ingredient> shoppingList;
	for (Date d : dates) {
		int btime = 0, ltime = 0, dtime = 0;
		Meal breakfast = d.getBreakfast(), lunch = d.getLunch(), dinner = d.getDinner();
		file << d.getYear() << '/' << d.getMonth() << '/' << d.getDay() << '\n' << '\n';
		file << "*******BREAKFAST*******" << '\n' << '\n';
		for (Recipe r : breakfast.getMenus()) {
			file << '<' << r.getName() << '>' << '\n';
			file << "Ingredients" << '\n';
			for (Ingredient i : r.getIngredient()) {
				file << " -" << i.getName() << " " << i.getAmount()*breakfast.getPeople() << "g" << '\n';
				bool inshoppinglist = false;
                for (int s = 0; s < shoppingList.size(); s++) {
                    if (shoppingList[s].getName() == i.getName()) {
                        shoppingList[s].setAmount(shoppingList[s].getAmount() + i.getAmount() * breakfast.getPeople());
                        inshoppinglist = true;
                        break;
                    }
                }
                if (!inshoppinglist) {
                    i.setAmount(i.getAmount() * breakfast.getPeople());
                    shoppingList.push_back(i);
                }
			}
			file << "Description" << '\n';
			file << " " << r.getDescription() << '\n';
			file << "Duration : " << r.getDuration() << "minutes" << '\n' << '\n';
			btime += r.getDuration();
		}
		file << "Total Duration : " << btime << "minutes" << '\n' << '\n';
		file << "*******LUNCH*******" << '\n' << '\n';
		for (Recipe r : lunch.getMenus()) {
			file << '<' << r.getName() << '>' << '\n';
			file << "Ingredients" << '\n';
			for (Ingredient i : r.getIngredient()) {
				file << " -" << i.getName() << " " << i.getAmount()*lunch.getPeople() << "g" << '\n';
				bool inshoppinglist = false;
				for (int s = 0; s < shoppingList.size(); s++) {
                    if (shoppingList[s].getName() == i.getName()) {
                        shoppingList[s].setAmount(shoppingList[s].getAmount() + i.getAmount() * lunch.getPeople());
                        inshoppinglist = true;
                        break;
                    }
				}
                if (!inshoppinglist) {
                    i.setAmount(i.getAmount() * lunch.getPeople());
                    shoppingList.push_back(i);
                }
			}
			file << "Description" << '\n';
			file << " " << r.getDescription() << '\n';
			file << "Duration : " << r.getDuration() << "minutes" << '\n' << '\n';
			ltime += r.getDuration();
		}
		file << "Total Duration : " << ltime << "minutes" << '\n' << '\n';
		file << "*******DINNER*******" << '\n' << '\n';
		for (Recipe r : dinner.getMenus()) {
			file << '<' << r.getName() << '>' << '\n';
			file << "Ingredients" << '\n';
			for (Ingredient i : r.getIngredient()) {
				file << " -" << i.getName() << " " << i.getAmount()*dinner.getPeople() << "g" << '\n';
				bool inshoppinglist = false;
				for (int s = 0; s < shoppingList.size(); s++) {
                    if (shoppingList[s].getName() == i.getName()) {
                        shoppingList[s].setAmount(shoppingList[s].getAmount() + i.getAmount() * dinner.getPeople());
                        inshoppinglist = true;
                        break;
                    }
				}
                if (!inshoppinglist) {
                    i.setAmount(i.getAmount() * dinner.getPeople());
                    shoppingList.push_back(i);
                }
			}
			file << "Description" << '\n';
			file << " " << r.getDescription() << '\n';
			file << "Duration : " << r.getDuration() << "minutes" << '\n' << '\n';
			dtime += r.getDuration();
		}
		file << "Total Duration : " << dtime << "minutes" << '\n' << '\n';
		file << '\n';
	}
	file << '\n';
	file << "*******SHOPPING LIST*******" << '\n';
	for (Ingredient i : shoppingList) file << i.getName() << " " << i.getAmount() << '\n';
}