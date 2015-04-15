# -*- coding:utf-8 -*- 

from Tkinter import *
import sys
from tkMessageBox import showerror
import subprocess	
import os
from tkFileDialog import askopenfilename 
from tkFileDialog import asksaveasfilename 
class ScrolledText(Frame):
	def __init__(self, parent=None):
		Frame.__init__(self, parent)
		self.pack(expand=YES, fill=BOTH)
		self.master.title(u"SNL编译器--琨琨出品")
		self.master.iconbitmap("./icon/han.ico")
		self.programText=""
		self.firstText=""
		self.ll1Text=""
		self.dgxjText=""
		self.yuyiText=""
		self.currentLineNo = IntVar()
		self.make()
	def clear(self):
		self.setText("")
		self.state = 0
	def make(self):
		toolbar = Frame(self, cursor='hand2', relief=SUNKEN, bd=2)
		toolbar.pack(side=TOP, fill=X)
		Button(toolbar, text=u"新建", command=self.clear).pack(side=LEFT)
		Button(toolbar, text=u"打开", command=self.open).pack(side=LEFT)
		Button(toolbar, text=u"另存为", command=self.saveas).pack(side=LEFT)
		Button(toolbar, text=u"保存", command=self.save).pack(side=LEFT)
		Button(toolbar, text=u"源程序", command=self.program).pack(side=LEFT)
		Button(toolbar, text=u"词法分析", command=self.first).pack(side=LEFT)
		Button(toolbar, text=u"递归下降", command=self.dgxj).pack(side=LEFT)
		Button(toolbar, text=u"LL1", command=self.ll1).pack(side=LEFT)
		Button(toolbar, text=u"语义分析", command=self.yuyi).pack(side=LEFT)
		Button(toolbar, text=u"退出", command=self.quit).pack(side=LEFT)
		statebar = Frame(self,  bd=2)
		statebar.pack(side=BOTTOM, fill=X)
		Label(statebar, text=u"当前行号", font=('新宋体', 12, 'normal')).pack(side=LEFT)
		lineno = Entry(statebar, text="",font=('新宋体', 12, 'normal'))
		lineno.config(textvariable=self.currentLineNo)
		lineno.pack(side=LEFT)
		lineno.bind('<Key-Return>', self.enter_a_lineno)
		sbar = Scrollbar(self)
		text = Text(self, relief=SUNKEN)
		text.config(font=('新宋体', 16, 'normal'))
		sbar.config(command=text.yview)
		text.config(yscrollcommand=sbar.set)
		sbar.pack(side=RIGHT, fill=Y)
		text.pack(side=LEFT, expand=YES, fill=BOTH)
		text.bind('<Button-1>', self.mouseClick)
		text.bind('<ButtonRelease-1>', self.mouseClick)
		text.bind('<Double-1>', self.mouseClick)
		self.text = text
	def mouseClick(self, event):
		 self.currentLineNo.set(int(float(self.text.index(INSERT))))
	def enter_a_lineno(self, event):
		try:
			lineno = self.currentLineNo.get()
		except ValueError,e:
			showerror(title=u"琨琨提示", message=u"行号该是个整数")
			self.currentLineNo.set(0)
			return
		self.text.see("%d.0" % lineno)
		self.text.mark_set(INSERT, "%d.0" % lineno)
		self.text.focus()
		self.text.tag_remove(SEL, "1.0", END)
		self.text.tag_add(SEL, "%d.0" % lineno, "%d.100" % lineno)
	def setText(self, text):
		self.text.delete("1.0", END)
		self.text.insert("1.0", text)
		self.text.mark_set(INSERT, "1.0");
		self.text.focus()
	def open(self):
		filename = askopenfilename(filetypes=[("SNL源程序", "*.snl")])
		if filename:
			self.setText(open(filename, "rb").read())
	def saveas(self):
		filename = asksaveasfilename(filetypes=[("SNL源程序", "*.*")])
		if filename:
			open(filename, "wt").write(self.getText().encode("utf8"));
	def getText(self):
		return self.text.get("1.0", END+'-1c')
	def save(self):
			self.programText = self.getText()
	def program(self):
			self.setText(self.programText)
	def first(self):
		if self.programText == "":
			self.setText(u"先输入程序, 并点击【保存】保存.")
		else:
			firstExe = subprocess.Popen("bin/first.exe", stdin=subprocess.PIPE, stdout=subprocess.PIPE)
			o,e = firstExe.communicate(self.programText)
			status = firstExe.wait()
			self.firstText = o.decode("gbk").encode("utf8");
			self.setText(self.firstText)
	def dgxj(self):
		if self.firstText=="":
			self.setText(u"先完成【词法】分析.")
		else:
			dgxjExe = subprocess.Popen("bin/dgxj.exe", stdin=subprocess.PIPE, stdout=subprocess.PIPE)
			o,e = dgxjExe.communicate(self.firstText)
			status = dgxjExe.wait()
			self.dgxjText = o.decode("gbk").encode("utf8");
			self.setText(self.dgxjText)
	def ll1(self):
		if self.firstText=="":
			self.setText(u"先完成【词法】分析.")
		else:
			ll1Exe = subprocess.Popen("bin/ll1.exe", stdin=subprocess.PIPE, stdout=subprocess.PIPE)
			o,e = ll1Exe.communicate(self.firstText)
			status = ll1Exe.wait()
			self.ll1Text = o.decode("gbk").encode("utf8");
			self.setText(self.ll1Text)
	def yuyi(self):
		grammerTree = ""
		if self.dgxjText != "":
			grammerTree = self.dgxjText
		elif self.ll1Text != "":
			grammerTree = self.ll1Text
		else:
			self.setText(u"先完成【语法】分析.")
			return
		yuyiExe = subprocess.Popen("bin/yuyi.exe", stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		o,e = yuyiExe.communicate(grammerTree)
		status = yuyiExe.wait()
		self.yuyiText = o.decode("gbk").encode("utf8");
		#self.yuyiText=self.yuyiText.replace("─", "──")
		#self.yuyiText=self.yuyiText.replace("┼", "─┼")
		#self.yuyiText=self.yuyiText.replace("┤", "─┤")
		self.yuyiText=self.yuyiText.replace("│  	│   	│	│	│		│", "│  	│   	│	│	│		│\t")
		self.yuyiText=self.yuyiText.replace("元素类型", "元素类型\t")
		self.yuyiText=self.yuyiText.replace("│TYPE	│", "\t│TYPE	│")
		self.yuyiText=self.yuyiText.replace("│ VAR	│", "\t│ VAR	│")
		self.yuyiText=self.yuyiText.replace("│PROC	│", "\t│PROC	│")
		self.yuyiText=self.yuyiText.replace("│ END	│", "\t│ END	│")
		self.yuyiText=self.yuyiText.replace("│          	   	   	│", "│          	   	   	\t│")
		self.setText(self.yuyiText)
		
if __name__=="__main__":
	ScrolledText().mainloop()
		