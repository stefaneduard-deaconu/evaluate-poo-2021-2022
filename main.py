import os


if __name__ == '__main__':

    files = list(filter(
        lambda fn: fn.endswith('.cpp'),
        os.listdir('.')
    ))

    cmakelists = '''cmake_minimum_required(VERSION 3.21)
project(colocviu_143)

set(CMAKE_CXX_STANDARD 14)

{}'''

    options = '''
# add_executable(colocviu_143 "{}")'''

    options = (options*len(files)).format(*files)
    # print(cmakelists.format(options))
    with open('CMakeLists.txt', 'w') as f:
        f.write(options)

