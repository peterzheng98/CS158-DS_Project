import os
returnID = os.system('g++ -o insertionData data_make.cpp -O2 -std=c++14 -w')
if returnID != 0:
    print('Fail to make Insertion Data Generator!')
    exit(-1)

returnID = os.system('g++ -o queryData data_make_query.cpp -O2 -std=c++14 -w')
if returnID != 0:
    print('Fail to make Query Data Generator!')
    exit(-1)

returnID = os.system('g++ -o eraseData data_make_erase.cpp -O2 -std=c++14 -w')
if returnID != 0:
    print('Fail to make Erase Data Generator!')
    exit(-1)

os.system('./insertionData > tmp && ./queryData > tmp && ./eraseData > tmp && rm tmp')
returnID = os.system('g++ -o hello_world BTree.cpp -O2 -std=c++14')
if returnID != 0:
    print('Fail to make your BTree, please check whether there exists any compilication error!')
    exit(-1)

os.system('g++ -o target sql_checker.cpp -O2 -std=c++14 -w')
print('[Accepted] Compiling')
os.system('./target')
