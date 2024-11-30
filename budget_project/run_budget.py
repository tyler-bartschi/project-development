from budget import *
import re


def store_data(history: History, budget: Budget, savings: Savings, filename="data.txt") -> None:
    '''This function will take the current history object, budget object,
    and savings object and will write the contents to a file to save the data.'''
    content = f"{history.name}|{history.create_budget_list()}\n"
    content += f"{repr(budget)}\n"
    content += repr(savings)

    with open(filename, "w") as file:
        file.writelines(content)


def load_data(filename="data.txt") -> tuple:
    with open(filename) as file:
        content = file.readlines()
    history_name, budget_list = content[0].strip().split("|")
    history = History(history_name)
    print(budget_list)
    print(budget_list)
    # budget_list = [eval(i) for i in budget_list]
    # history.create_history(budget_list)
    # budget = eval(content[1].strip())
    # savings = eval(content[2].strip())
    # return history, budget, savings


if __name__ == "__main__":
    budget1 = Budget("10/11/24", 1000)
    budget2 = Budget("10/15/24", 2000)
    budget3 = Budget("12/12/24", 3000)
    budget4 = Budget("10/11/24", 2000)
    history1 = History("First history")
    savings = Savings(1000)

    history1.create_history([budget2, budget3, budget4])

    store_data(history1, budget1, savings)

    load_data()
    # history, budget, saving = load_data()
    # store_data(history, budget, saving, "test.txt")