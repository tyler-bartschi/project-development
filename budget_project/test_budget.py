import pytest
from budget import *


# testing the create_history function
def test_history_create_history():
    budget1 = Budget("10/11/24", 1000)
    budget2 = Budget("10/15/24", 2000)
    budget3 = Budget("12/12/24", 3000)
    budget4 = Budget("10/11/24", 2000)
    history1 = History("First history")
    history2 = History("Second history")
    with pytest.raises(AssertionError):
        history1.create_history(10)
    with pytest.raises(AssertionError):
        history1.create_history("Hello")
    with pytest.raises(AssertionError):
        history1.create_history(budget1)
    with pytest.raises(AssertionError):
        history1.create_history([])
    with pytest.raises(TypeError):
        history1.create_history([budget1, "hello", budget2])
    with pytest.raises(TypeError):
        history1.create_history([10, budget2, budget3])
    with pytest.raises(ValueError):
        history2.create_history([budget2, budget3, budget1, budget4])
    history2.clear_history()

    history1.create_history([budget1, budget2])
    assert history1.budget_history == {
        "10/11/24": budget1, "10/15/24": budget2}
    history2.create_history([budget2, budget1, budget3])
    assert history2.budget_history == {
        "10/15/24": budget2, "10/11/24": budget1, "12/12/24": budget3}


# this will test adding another budget to the history
def test_history_add1():
    budget1 = Budget("10/11/24", 1000)
    budget2 = Budget("10/15/24", 2000)
    budget3 = Budget("12/12/24", 3000)
    budget4 = Budget("10/11/24", 2000)
    budget5 = Budget("9/2/23", 12000)
    history1 = History("First history")
    history2 = History("Second history")
    history1.create_history([budget1, budget2, budget3])
    history2.create_history([budget1])

    with pytest.raises(TypeError):
        history1 += 10
    with pytest.raises(TypeError):
        history1 += "hello"
    with pytest.raises(TypeError):
        history1 = history1 + 12.34
    with pytest.raises(ValueError):
        history1 += budget4
    with pytest.raises(ValueError):
        history2 += budget1
    with pytest.raises(ValueError):
        history1 = history1 + budget4
    history2 += budget2
    assert history2.budget_history == {
        "10/11/24": budget1, "10/15/24": budget2}
    history2 += budget3
    assert history2.budget_history == {
        "10/11/24": budget1, "10/15/24": budget2, "12/12/24": budget3}
    history1 = history1 + budget5
    assert history1.budget_history == {
        "10/11/24": budget1, "10/15/24": budget2, "12/12/24": budget3, "9/2/23": budget5}
    history2 += budget5
    assert history2.budget_history == {
        "10/11/24": budget1, "10/15/24": budget2, "12/12/24": budget3, "9/2/23": budget5}


# this will test adding two histories together to return a new history
def test_history_add2():
    budget1 = Budget("10/11/24", 1000)
    budget2 = Budget("10/15/24", 2000)
    budget3 = Budget("12/12/24", 3000)
    budget4 = Budget("10/11/24", 2000)
    budget5 = Budget("9/2/23", 12000)
    budget6 = Budget("6/7/15", 2020)
    budget7 = Budget("8/9/10", 1000)
    budget8 = Budget("10/10/10", 200)
    history1 = History("First history")
    history2 = History("Second history")
    history3 = History("Third history")
    history1.create_history([budget1, budget2, budget3])
    history2.create_history([budget1, budget5, budget6, budget7])
    history3.create_history([budget8])

    history3 += history1
    assert history3.budget_history == {
        "10/10/10": budget8, "10/11/24": budget1, "10/15/24": budget2, "12/12/24": budget3}
    history3 += history1
    assert history3.budget_history == {
        "10/10/10": budget8, "10/11/24": budget1, "10/15/24": budget2, "12/12/24": budget3}
    history1 += history2
    assert history1.budget_history == {"10/11/24": budget1, "10/15/24": budget2,
                                       "12/12/24": budget3, "9/2/23": budget5, "6/7/15": budget6, "8/9/10": budget7}
    history2 += history1
    assert history2.budget_history == {"10/11/24": budget1, "10/15/24": budget2,
                                       "12/12/24": budget3, "9/2/23": budget5, "6/7/15": budget6, "8/9/10": budget7}


# tests that the create_budget_list function works properly
def test_create_budget_list():
    budget1 = Budget("10/11/24", 1000)
    budget2 = Budget("10/15/24", 2000)
    budget3 = Budget("12/12/24", 3000)
    history1 = History("First history")
    history2 = History("Second history")
    history3 = History("Second history")
    history1.create_history([budget1, budget2, budget3])
    history2.create_history([budget1, budget2])
    history3.create_history([budget3, budget1, budget2])

    assert history1.create_budget_list() == [budget1, budget2, budget3]
    assert history2.create_budget_list() == [budget1, budget2]
    assert history3.create_budget_list() == [budget3, budget1, budget2]


# test that the budget object is working correctly
def test_budget_repr():
    budget1 = Budget("10/11/24", 1000)
    budget2 = Budget("10/15/24", 2000)
    budget3 = Budget("12/12/24", 3000)

    # assert repr(budget1) == Budget.build_budget([10/11/24, 1000, 0, 1000, [], []])
    budget4 = eval(repr(budget1))
    budget5 = eval(repr(budget4))
    budget6 = eval(repr(budget2))

    assert budget1.test_data() == budget4.test_data()
    assert budget1.test_data() == budget5.test_data()
    assert budget5.test_data() == budget4.test_data()
    assert budget6.test_data() == budget2.test_data()
    assert budget5 is not budget4
    assert budget4 is not budget1
    assert budget6 is not budget2

    assert budget6.income == 2000
    assert budget5.name == "10/11/24"
    assert budget4.income == 1000
    budget4.expenditure(200, "test1")
    assert budget4.amount_left == 800
    assert budget4.current_total_expenses == 200
    assert budget4.expense_list == [("test1", 200)]
    budget1.expenditure(500, "test2")
    assert budget1.amount_left == 500
    assert budget1.current_total_expenses == 500
    assert budget1.expense_list == [("test2", 500)]
    budget1.update_income(200)
    assert budget1.income == 1200
    assert budget1.amount_left == 700


def test_budget_verify_data_integrity():
    budget1 = Budget("10/11/24", 1000)
    budget2 = Budget("10/15/24", 2000)
    budget3 = Budget("12/12/24", 3000)

    with pytest.raises(TypeError):
        Budget.verify_data_integrity(["10/11/24", [1000], 0, 1000, [], []])
    with pytest.raises(TypeError):
        Budget.verify_data_integrity(["10/11/24", 1000, "hello", 1000, [], []])
    with pytest.raises(TypeError):
        Budget.verify_data_integrity(
            ["10/11/24", 1000, 0, ("this is a test", 2), [], []])
    with pytest.raises(TypeError):
        Budget.verify_data_integrity([10, 1000, 0, 1000, [], []])
    with pytest.raises(TypeError):
        Budget.verify_data_integrity(["10/11/24", 1000, 0, 1000, "hi", []])
    with pytest.raises(TypeError):
        Budget.verify_data_integrity(["10/11/24", 1000, 0, 1000, [], 24])
    with pytest.raises(AssertionError):
        Budget.verify_data_integrity(["10/11/24", 1000])
    with pytest.raises(AssertionError):
        Budget.verify_data_integrity(
            ["10/11/24", 123, 12, 4532, [], [], "Hello"])
    with pytest.raises(TypeError):
        Budget.verify_data_integrity("hello")


def test_savings():
    budget1 = Budget("10/11/24", 1000)
    saving_account = Savings()

    with pytest.raises(TypeError):
        budget1.update_savings("hello")
    with pytest.raises(TypeError):
        budget1.expenditure("10b", "haha")

    budget1.update_savings(100, saving_account)
    assert budget1.expense_list == [("Savings", 100)]
    assert budget1.current_total_expenses == 100
    assert budget1.amount_left == 900
    assert saving_account.saving == 100

    saving_account.withdraw_savings(50)
    assert saving_account.saving == 50

    with pytest.raises(TypeError):
        saving_account.withdraw_savings("122.b")
    with pytest.raises(TypeError):
        saving_account.withdraw_savings("hello")

    budget1.update_savings_final(saving_account)
    assert budget1.expense_list == [("Savings", 100), ("Savings", 900)]
    assert budget1.current_total_expenses == 1000
    assert budget1.amount_left == 0
    assert saving_account.saving == 950


def test_category_basic():
    budget1 = Budget("10/22/23", 2000)

    budget1.create_category("Test1", 100)
    budget1.create_category("Test2", 500)

    # test the create_category method, as well as the update_category_amount method, as well as the Category object itself
    assert len(budget1.category_list) == 2
