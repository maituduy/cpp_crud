#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

void print_all(sql::Statement *stmt) {
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM test");
    while (res->next()) {
        std::cout << "id = " << res->getInt("id") << "; ";
        std::cout << "name = " << res->getString("name") << std::endl;
    }
    delete res;
}

int main(int argc, const char* argv[]) {
    try {
        const std::string HOST = "tcp://localhost";
        const std::string PORT = "3306";
        const std::string USERNAME = "test";
        const std::string PASSWORD = "test";
        const std::string DBNAME = "test_crud";

        std::string names[] = {"a", "b", "c", "d", "e", "a", "b", "c", "d", "e"};
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::PreparedStatement *pstmt;

        driver = get_driver_instance();
        con = driver->connect(HOST + ":" + PORT, USERNAME, PASSWORD);

        // Connect to the MySQL test database
        con->setSchema(DBNAME);

        // Create table
        stmt = con->createStatement();
        stmt->execute("DROP TABLE IF EXISTS test");
        stmt->execute("CREATE TABLE test(id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,\n"
                      "name VARCHAR(30) NOT NULL)");

        // INSERT
        pstmt = con->prepareStatement("INSERT INTO test(name) VALUES (?)");
        for (int i = 0; i < 10; i++) {
            pstmt->setString(1, names[i]);
            pstmt->executeUpdate();
        }
        delete pstmt;

        // SELECT

        print_all(stmt);

        // UPDATE
        pstmt = con->prepareStatement("UPDATE test SET name=? where id=?");
        for (int i = 9, j = 1; i >=0 ; --i, ++j) {
            pstmt->setString(1, names[i]);
            pstmt->setInt(2, j);
            pstmt->executeUpdate();
        }
        delete pstmt;

        std::cout << "After Update\n";
        print_all(stmt);

        // DELETE

        pstmt = con->prepareStatement("DELETE FROM test WHERE name=?");
        pstmt->setString(1, "a");
        pstmt->executeUpdate();

        std::cout << "After Delete\n";
        print_all(stmt);

        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line "
        << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}