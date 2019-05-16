import filecmp

def fileComparer(file1,file2):
    for line1 in file1:
        f1 = open(file1,'r')
        line1 = f1.readline()
        f2 = open(file2,'r')
        line2 = f2.readline()
        if line1!=line2:
                return file1.index(line1)
    return 1


def lineInfo(file,num):
        f1 = open(file,'r')
        line1 = f1.readline(num)
        return line1

outputs = ['/tests_trabPratico/T01/output1.txt','/tests_trabPratico/T02/output2.txt','/tests_trabPratico/T03/output.txt','/tests_trabPratico/T04/output.txt','/tests_trabPratico/T05/output.txt','/tests_trabPratico/T06/output.txt','/tests_trabPratico/T07/output.txt','/tests_trabPratico/T08/output.txt','/tests_trabPratico/T09/output.txt','/tests_trabPratico/T10/output.txt','/tests_trabPratico/T11/output.txt','/tests_trabPratico/T12/output.txt','/tests_trabPratico/T13/output.txt','/tests_trabPratico/T14/output.txt','/tests_trabPratico/T15/output.txt','/tests_trabPratico/T16/output.txt','/tests_trabPratico/T17/output.txt','/tests_trabPratico/T18/output.txt','/tests_trabPratico/T19/output.txt','/tests_trabPratico/T20/output.txt']
outs = iter(outputs)
input = 'output.txt'
for i in outs:
    if fileComparer(input,i) != 1:
        nline = outputs.index(i)+1 #Nº da linha
        print(str(nline) + ' ' + lineInfo(input,nline))
        print('Expected : ' + lineInfo(i,nline))
        break
    else:
            print('Teste '+nline)
