from library import *


my_lib = Library("Cerritos", "1800 Shellfish Ave, Cerritos, CA 90832")

my_movie = Movie("Maze Runner", "Action", "M89238", "2hrs")
print(my_movie)
my_movie._check_out("5 October 2024")
print(my_movie)
my_movie._return_item()
print(my_movie)

#my_lib.create_account()
# my_lib.create_account()

# print(my_lib)
# print(repr(my_lib))
