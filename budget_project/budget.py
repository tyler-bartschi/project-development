class History():
    def __init__(self, name):
        self.name = name
        self.budget_history = {}

    def __add__(self, other):
        """will either add a budget to the history, or combine to histories together"""
        if isinstance(other, History):
            first_history = self.create_budget_list()
            second_history = other.create_budget_list()
            comb_hist = History.combine_histories(
                first_history, second_history)
            new_hist = History(self.name)
            new_hist.create_history(comb_hist)
            return new_hist
        elif isinstance(other, Budget):
            if other.name not in self.budget_history:
                new_budget_list = self.create_budget_list()
                new_budget_list.append(other)
                new_hist = History(self.name)
                new_hist.create_history(new_budget_list)
                return new_hist
            else:
                raise ValueError(
                    "You cannot have two budgets with the same date in the history.")
        else:
            raise TypeError("You can only add a History or Budget Type")

    def _verify_list(self, budget_list):
        """verifies that the list passed to create_history only has Budget types, otherwise raises a ValueError"""
        for item in budget_list:
            if not isinstance(item, Budget):
                raise TypeError(f"{item} in this list is not a Budget type.")

    def create_history(self, budget_list):
        """creates a history when given a list of budget types, intended to be used when reading from a save file and reloading information"""
        assert isinstance(budget_list, list), "Must be a list"
        assert len(budget_list) > 0, "List must have items in it"

        self._verify_list(budget_list)
        for item in budget_list:
            if item.name not in self.budget_history:
                self.budget_history[item.name] = item
            else:
                raise ValueError(
                    f"{item} has the same date as another item in the list.")

    def clear_history(self):
        """clears the history, currently for testing purposes but might be useful"""
        self.budget_history = {}

    def create_budget_list(self):
        """creates a list of budgets out of an existing budget_history dictionary that can be passed to the create_history function"""
        return [self.budget_history[i] for i in self.budget_history]

    @staticmethod
    def combine_histories(frst, scnd):
        """designed to combine two lists representing histories from two different history objects.
        will ignore duplicate items, printing a message that the duplicate will not be included"""
        new_history = [item for item in frst]
        for item in scnd:
            if item in new_history:
                print(f"Duplicate item {item} not included in new history.")
            else:
                new_history.append(item)
        return new_history


class Budget():
    def __init__(self, name, income):
        self.income = self._convert_amount(income)
        self.name = name
        self.current_total_expenses = 0.0
        self.amount_left = self.income - self.current_total_expenses
        self.expense_list = []
        self.category_dict = {}

    def __str__(self):
        return (f"{self.name}, {self.income}")

    def __repr__(self):
        """returns a string that calls the build_budget method, which will allow complete replication of the current budget object"""
        return f"Budget.build_budget([{repr(self.name)}, {self.income}, {self.current_total_expenses}, {self.amount_left}, {self.expense_list}, {self.store_categories()}])"

    def test_data(self):
        """similar to repr, only to be used for testing purposes"""
        return f'[{self.name}, {self.income}, {self.current_total_expenses}, {self.amount_left}, {self.expense_list}, {self.store_categories()}]'

    def expenditure(self, amount, name):
        """a function for processing an expenditure in the budget"""
        amount = self._convert_amount(amount)
        self.current_total_expenses += amount
        self.expense_list.append((name, amount))
        self.update_amount_left(amount)

    def update_amount_left(self, amount):
        """a function for updating the variable amount_left"""
        amount = self._convert_amount(amount)
        self.amount_left -= amount

    def update_income(self, amount):
        """a function for adding additional money to the income variable"""
        amount = self._convert_amount(amount)
        self.income += amount
        self.amount_left = self.income - self.current_total_expenses

    def create_category(self, name, amount):
        """a function for creating a category in the budget"""
        new_category = Category(name, amount)
        self.category_dict[new_category.name] = new_category

    def update_category_amount(self, amount, category, method="expense", name="Expenditure"):
        """a function to be called when a category amount needs to be updated, which will update
        both the category and the overall budget."""
        if not isinstance(category, Category):
            raise TypeError(f"{category} must be of the Category type.")
        if method.lower() not in ["expense", "income"]:
            raise ValueError(f"{method} unsupported.")

        if method.lower() == "expense":
            category.expenditure(amount, name)
            self.expenditure(
                amount, f"{name} belonging to the category {category.name}")
        elif method.lower() == "income":
            category.update_income(amount)

    def build_category_dict(self, lst):
        """takes a list with the necessary information to create the categories within the budget"""
        assert isinstance(lst, list), "Must be a list"
        for item in lst:
            category = eval(item)
            self.category_dict[category.name] = category

    def store_categories(self):
        """creates a list with the necessary information to store the categories created by the budget"""
        return [repr(object) for _, object in self.category_dict.items()]

    def update_savings(self, amount, savings):
        """Updates a given savings object by the given amount"""
        amount = self._convert_amount(amount)
        savings.update_savings(amount)
        self.expense_list.append(('Savings', float(amount)))
        self.current_total_expenses += amount
        self.update_amount_left(amount)

    def update_savings_final(self, savings):
        """Meant to take the rest of the amount left in the budget and move it into the designated savings."""
        savings.update_savings(self.amount_left)
        self.expense_list.append(("Savings", self.amount_left))
        self.current_total_expenses += self.amount_left
        self.amount_left -= self.amount_left

    def _convert_amount(self, amount):
        try:
            return float(amount)
        except Exception:
            raise TypeError("Must be a valid amount (float, str).")

    @staticmethod
    def build_budget(lst):
        """a function to build the Budget object with preset stuff"""
        # lst will hold [date, income, current_total_expenses, amount_left, expense_list, category_list]
        Budget.verify_data_integrity(lst)
        new_budget = Budget(lst[0], float(lst[1]))
        new_budget.current_total_expenses = float(lst[2])
        new_budget.amount_left = float(lst[3])
        new_budget.expense_list = lst[4]
        new_budget.build_category_dict(lst[5])
        return new_budget

    @staticmethod
    def verify_data_integrity(lst):
        """a function to verify the data given to the build_budget method"""
        if not isinstance(lst, list):
            raise TypeError(f'{lst} must be a list')
        assert len(lst) == 6

        try:
            float(lst[1])
            float(lst[2])
            float(lst[3])
        except ValueError as e:
            raise TypeError('Ensure items at index 1, 2, and 3 are numbers.')
        except TypeError as e:
            raise TypeError("Ensure items at index 1, 2, and 3 are numbers.")

        if not isinstance(lst[0], str):
            raise TypeError(f"{lst[0]} must be a string.")

        if not isinstance(lst[4], list):
            raise TypeError(f"{lst[4]} must be a list.")

        if not isinstance(lst[5], list):
            raise TypeError(f"{lst[5]} must be a list.")


class Category(Budget):
    def __str__(self):
        return f"{self.name} Category with {self.income} in it."

    def __repr__(self):
        """returns a string that calls the build_category method, which will allow complete replication of the current category object"""
        return f"Category.build_category([{repr(self.name)}, {self.income}, {self.current_total_expenses}, {self.amount_left}, {self.expense_list}, {[]}])"

    def test_data(self):
        """similar to repr, only to be used for testing purposes"""
        return f'[{self.name}, {self.income}, {self.current_total_expenses}, {self.amount_left}, {self.expense_list}, {[]}]'

    def create_category(self, name, amount):
        raise TypeError("Cannot create a category within a Category.")

    def build_category_dict(self, lst):
        raise TypeError("Cannot create a category list within a Category.")

    def store_categories(self):
        raise TypeError("Cannot store categories in a category object.")

    def update_savings(self):
        raise TypeError("Cannot update savings from within a category object.")

    def update_savings_final(self):
        raise TypeError("Cannot update savings from within a category object.")

    @staticmethod
    def build_category(lst):
        Budget.verify_data_integrity(lst)
        new_category = Category(lst[0], float(lst[1]))
        new_category.current_total_expenses = float(lst[2])
        new_category.amount_left = float(lst[3])
        new_category.expense_list = lst[4]
        return new_category


class Savings():
    def __init__(self, amount=0):
        """Initializes a savings instance given an amount."""
        self.verify_amount(amount)
        self.saving = float(amount)

    def __str__(self):
        return f"Total Savings: {self.amount}"

    def __repr__(self):
        return f"Savings({self.amount})"

    def update_savings(self, amount):
        """Updates the savings by the specific amount."""
        self.verify_amount(amount)
        self.saving += amount

    def withdraw_savings(self, amount):
        """Removes the specified amount from the savings"""
        self.verify_amount(amount)
        self.saving -= amount

    def verify_amount(self, amount):
        """Verifies that a given amount is a number."""
        try:
            float(amount)
        except Exception:
            raise TypeError("SAVINGS: Ensure amount is a number.")
