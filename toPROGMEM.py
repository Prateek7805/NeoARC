import os
header = "const char PROGMEM = R\"=====("
trailer = ")=====\";"
files = os.listdir()
for file in files:
    if os.path.isfile(file):
        if file.endswith(".htm") or file.endswith(".html") or file.endswith(".css") or file.endswith(".js"):
            modifiedHeader = header[: header.index("P")] + "_"+file[ : file.rindex(".")] + "[] " + header[header.index("P") : ]
            filePoint = open(file, 'r')
            fileContent = modifiedHeader +"\n"+ filePoint.read() +"\n"+ trailer;
            filePoint.close()
            
            filePoint = open(file[ : file.rindex(".")]+".h", "w")
            filePoint.write(fileContent)
            filePoint.close()
            

