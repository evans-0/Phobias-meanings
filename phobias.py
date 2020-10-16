with open('phobias.txt','r') as fo:
    fc = fo.readlines()
    
phobia = []
phobia_meaning = []

for line in fc:
    line = line.strip('\n').split('\t')
    phobia.append(line[0])
    phobia_meaning.append(line[1])
    word = line[1].split(' ')[-1]

import tkinter
from tkmacosx import Button

root = tkinter.Tk()
root.configure(bg='black')
root.geometry('700x150')

lbl = tkinter.Label(root, text='Choose phobia: ')
lbl.place(x=20, y=20)
lbl.configure(font = ('Courier', 30), bg='black', fg='white')

s = tkinter.StringVar(root)
opt = tkinter.OptionMenu(root, s, *phobia)
opt.place(x=308, y=20)
opt.configure(font = ('Courier', 30), bg='black')

def clicked():
    try:
        ch = phobia.index(s.get())
        print(phobia_meaning[ch])
        root.destroy()
    except:
        tkinter.messagebox.showinfo('Warning', 'Select option!!')
    
btn1 = Button(root, text='OK', command=clicked)
btn1.place(x=200, y=80)
btn1.configure(font = ('Courier', 30), bg='black', fg='white')

btn2 = Button(root, text='EXIT', command=root.destroy)
btn2.place(x=400, y=80)
btn2.configure(font = ('Courier', 30), bg='black', fg='white')

root.mainloop()
