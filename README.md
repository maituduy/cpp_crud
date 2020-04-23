###Requirements:
1. Mysql
2. mysql-connector-cpp
    * Download and extract [Boost](https://www.boost.org/users/download/)
    * Install mysql-connector-cpp
        * git clone https://github.com/mysql/mysql-connector-cpp.git && cd mysql-connector-cpp
        * git checkout 1.1
        * mkdir build && cd build
        * cmake -DBOOST_ROOT:STRING=<em>boost_path</em> ..
        * sudo make install