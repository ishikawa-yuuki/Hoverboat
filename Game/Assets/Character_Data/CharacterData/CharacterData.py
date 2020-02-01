from openpyxl import load_workbook
import struct

workbook = load_workbook(filename = "C:/Users/CG1801/Desktop/test/Booktest.xlsx", read_only = True)
sheet = workbook["AIデータ"]
accel=0.0
friction=0.0
charaNoKazu = 0
rowNo = 5
while True:
 if sheet.cell(column = 2, row = rowNo).value == "end":
 
    break
 charaNoKazu += 1
 rowNo += 1


fp = open("data.ai", "wb")
fp.write(struct.pack("i", charaNoKazu))
rowNo = 5
while True:
 if sheet.cell(column = 2, row = rowNo).value == "end":
 
     break
#加速度を抽出
 accel = sheet.cell(column = 3, row = rowNo).value

 fp.write(struct.pack("f", accel))
#摩擦
 friction = sheet.cell(column = 4, row = rowNo).value
 fp.write(struct.pack("f", friction))
 rowNo +=1

