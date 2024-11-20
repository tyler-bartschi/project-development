import random


class Library:
    all_items = {}
    all_books = {}
    all_movies = {}
    all_patrons = {}
    total_items = 0
    total_books = 0
    total_movies = 0
    total_patrons = 0

    def __init__(self, name, address):
        self.name = name
        self.address = address

    
    def __str__(self):
        return f"The {self.name} Library located at {self.address}.\n"


    def __repr__(self):
        return f"Library({repr(self.name)}, {repr(self.address)})"


    # creates a new patron account, adds it to the all_patrons dictionary and adds one to total patrons
    def create_account(self):
        name = input("Please enter the name of the user: ")
        if self._check_duplicate_account(name):
            self.create_account()
        address = input("Please enter the address of the user: ")

        new_patron = Patron(name, address, self._create_patron_id())
        self.all_patrons[new_patron.id_number] = new_patron
        self.total_patrons += 1

        print("Here is your new ID information!\n")
        print(new_patron)

    
    # creates a random 7 digit id number for a new patron and checks to ensure it is not a duplicate
    # if it is a duplicate, it will create another one, then return the ID number
    def _create_patron_id(self):
        tempID = ""
        for i in range(7):
            tempID += str(int(random.random() * 10))
        if tempID in self.all_patrons:
            self._create_patron_id()
        else:
            return tempID
    
    
    # this will check if the account has the same name as another account, and let the user decide
    # they can either create another account with the same name, or choose to not and create a different account
    def _check_duplicate_account(self, name):
        for id in self.all_patrons:
            if self.all_patrons[id].name == name:
                print(f"There is already an account with the name {name}.")
                response = input("Do you want to create another account(y/n)? ")
                if response.lower() == "y" or response.lower() == "yes":
                    return False
                else:
                    return True
                

    def donate(self):
        pass


# Class for a general item, storing variables describing that item
class Item:
    currently_checked_out = False
    when_due = ""
    num_times_checked = 0


    def __init__(self, title, genre, id):
        self.title = title
        self.genre = genre
        self.id = id

    
    # defined in sub classes
    def __str__(self):
        pass

    
    # defined in sub classes
    def __repr__(self):
        pass


    # a function to check out a book, updating the instance variables currenty_checked_out, num_times_checked and when_due
    def _check_out(self, due_date):
        self.currently_checked_out = True
        self.num_times_checked += 1
        self.when_due = due_date
    

    # returns if the item is currently checked out
    def _is_out(self):
        return self.currently_checked_out
    

    # a function to return an item, updating the currently_checked_out and when_due instance variables
    def _return_item(self):
        self.currently_checked_out = False
        self.when_due = ""


class Book(Item):
    def __init__(self, title, genre, id, author="Anonymous"):
        super().__init__(title, genre, id)
        self.author = author

    
    # returns a multi-line string displaying the name, author, genre, library id, and whether or not it is currently checked out
    def __str__(self):
        if self.currently_checked_out:
            currently_out = f"This book is currently checked out!\nDue: {self.when_due}"
        else:
            currently_out = "This book is availble for rent."
        return f"{self.title} by {self.author}\nGenre: {self.genre}\nLibrary ID: {self.id}\n{currently_out}\n"


    def __repr__(self):
        return(f"{repr(self.title)}, {repr(self.genre)}, {repr(self.id)}, {repr(self.author)}")



class Movie(Item):
    def __init__(self, title, genre, id, runtime):
        super().__init__(title, genre, id)
        self.runtime = runtime

    # returns a multi-line string displaying the title, genre, library id, runtime, and whether or not it is currently checked out    
    def __str__(self):
        if self.currently_checked_out:
            currently_out = f"This movie is currently checked out!\nDue: {self.when_due}"
        else:
            currently_out = "This movie is available for rent."
        return f"{self.title}\nGenre: {self.genre}\nLibrary ID: {self.id}\nRuntime: {self.runtime}\n{currently_out}\n"
    

    def __repr__(self):
        return(f"{repr(self.title)}, {repr(self.genre)}, {repr(self.id)}, {repr(self.runtime)}")


class Patron():
    # currently_checked_out will be a dictionary of ID numbers of items paired with their due dates
    currently_checked_out = {}
    # history is a list of previously checked out item ID numbers
    history = []
    charge_on_card = 0

    def __init__(self, name, address, id_num):
        self.name = name
        self.address = address
        self.id_number = id_num
        # print(f"Patron created with the name {self.name} and ID number {self.id_number}")

    
    def __str__(self):
        return f"ID Number: {self.id_number}\nName: {self.name}\nAddress: {self.address}\n"
    

    def __repr__(self):
        return f"Patron({repr(self.name)}, {repr(self.address)}, {repr(self.id_number)})"
