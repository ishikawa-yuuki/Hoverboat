from openpyxl import load_workbook
import struct

workbook = load_workbook(filename = "C:/Users/CG1801/Desktop/Hover/Hoverboat/Game/Assets/Character_Data/Character_Data.xlsx",
                         read_only = True)
sheet = workbook["CharaData"]
accel=0.0
friction=0.0
sutearing = 0.0
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

 sutearing = sheet.cell(column = 5, row = rowNo).value
 fp.write(struct.pack("f", sutearing))
 rowNo +=1

