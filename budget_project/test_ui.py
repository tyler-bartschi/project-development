import tkinter as tk


class ContactManagerApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Simple Contact Manager")
        self.geometry("400x300")
        
        self.contact_list_frame = ContactListFrame(self)

        self.add_contact_frame = AddContactFrame(self)

        self.show_frame(self.contact_list_frame)

        def show_frame(self, frame):
            frame.tkraise()


class ContactListFrame(tk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.grid(row=0, column=0, sticky="nsew")

        label = tk.Label(self, text="Contact List", font=("Helvetica", 16))
        label.pack(pady=10)

        self.contact_listbox = tk.Listbox(self)

        self.contact_listbox.pack(expand=True, fill='both', padx=20, pady=10)

        btn_add_contact = tk.Button(self, text="Add Contact", command=lambda:master.show_frame(master.add_contact_frame))
        btn_add_contact.pack(pady=10)


class AddContactFrame(tk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.grid(row=0, column=0, sticky="nsew")

        # Label to indicate the screen
        label = tk.Label(self, text="Add New Contact", font=("Helvetica", 16))
        label.pack(pady=10)

        # Entry widgets for contact details
        self.name_var = tk.StringVar()
        name_label = tk.Label(self, text="Name:")
        name_label.pack()
        self.name_entry = tk.Entry(self, textvariable=self.name_var)
        self.name_entry.pack(pady=5)

        self.phone_var = tk.StringVar()
        phone_label = tk.Label(self, text="Phone:")
        phone_label.pack()
        self.phone_entry = tk.Entry(self, textvariable=self.phone_var)
        self.phone_entry.pack(pady=5)

        # Button to save contact and return to contact list
        btn_save = tk.Button(self, text="Save Contact", command=self.save_contact)
        btn_save.pack(pady=10)
        
        # Button to go back without saving
        btn_back = tk.Button(self, text="Back", command=lambda: master.show_frame(master.contact_list_frame))
        btn_back.pack(pady=5)

    def save_contact(self):
        name = self.name_var.get()
        phone = self.phone_var.get()
        if name and phone:
            # For simplicity, assume contact_list_frame is the first frame.
            self.master.contact_list_frame.contact_listbox.insert(tk.END, f"{name} - {phone}")
            self.master.show_frame(self.master.contact_list_frame)


if __name__ == "__main__":
    app = ContactManagerApp()
    app.mainloop()
# from tkinter import font


# def on_button_click():
#     print("Hello, Tkinter!")


# def colorful():
#     print("hello")


# def on_enter(event):
#     event.widget['background'] = 'lightgreen'


# def on_leave(event):
#     event.widget['background'] = "green"


# def on_enter_2(event):
#     event.widget['background'] = "darkgrey"


# def on_leave_2(event):
#     event.widget['background'] = "SystemButtonFace"


# root = tk.Tk()
# root.geometry('800x600+50+50')

# button_font = font.Font(family="Arial", size=16, weight='bold')
# label = tk.Label(root, text="Welcome to Tkinter!")
# label.pack()

# label2 = tk.Label(root, text="experimentation with color",
#                   bg="lightblue", fg="darkblue")
# label2.pack(pady=10)

# button = tk.Button(root, text="Greet", command=on_button_click, width=20, height=2, font=button_font)
# button.pack(pady=5)
# button.bind("<Enter>", on_enter_2)
# button.bind("<Leave>", on_leave_2)

# button2 = tk.Button(root, text="Close", command=root.quit)
# button2.pack(side="bottom")


# colored_button = tk.Button(root, text="Colorful", command=colorful, bg="green",
#                            fg="white", activebackground="darkgreen", activeforeground="lightgray")
# colored_button.pack(pady=5)
# colored_button.bind("<Enter>", on_enter)
# colored_button.bind("<Leave>", on_leave)

# entry = tk.Entry(root)
# entry.pack()

# root.mainloop()
