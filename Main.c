#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

// 에러 처리를 위한 함수
void finish_with_error(MYSQL* con) {
    fprintf(stderr, "%s\n", mysql_error(con)); // 오류 메시지 출력
    mysql_close(con); // MySQL 연결 종료
    exit(1); // 프로그램 종료
}

// 언어 ID 가져오기 함수
int get_language_id(MYSQL* con, const char* language) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT id FROM Main WHERE language = '%s'", language);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        printf("No matching data found for language '%s'\n", language);
        mysql_free_result(result);
        return -1;  // 오류가 발생한 경우 -1 반환
    }

    int language_id = atoi(row[0]);
    mysql_free_result(result);
    return language_id;
}

// 버전 데이터 삽입 함수
void insert_version_data(MYSQL* con, const char* table_name, int language_id, const char* version, const char* date, const char* documentation) {
    if (language_id < 0) {
        printf("Invalid language_id for table %s, skipping insert.\n", table_name);
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO %s (language_id, version, date, documentation) VALUES (%d, '%s', '%s', '%s')",
        table_name, language_id, version, date, documentation);

    if (mysql_query(con, query)) {
        fprintf(stderr, "Failed to insert into %s: %s\n", table_name, mysql_error(con));
    }
    else {
        printf("Data inserted into %s successfully!\n", table_name);
    }
}

// 데이터 조회 함수
void query_and_print_table(MYSQL* con, const char* table_name) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM %s", table_name);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    printf("Data from %s:\n", table_name);
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    mysql_free_result(result);
}

int main() {
    // MySQL 연결 객체 초기화
    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    // MySQL 서버에 연결
    if (mysql_real_connect(con, "localhost", "root", "kimhungjin88@", "MyNewDatabase", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    // Main 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS Main ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language VARCHAR(100), "
        "Front_Back VARCHAR(100))")) {
        finish_with_error(con);
    }

    // 다른 언어별 테이블 생성 (외래 키 포함)
    const char* create_table_queries[] = {
        "CREATE TABLE IF NOT EXISTS C ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)",

        "CREATE TABLE IF NOT EXISTS Cpp ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)",

        "CREATE TABLE IF NOT EXISTS C_Sharp ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)",

        "CREATE TABLE IF NOT EXISTS Ruby ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)",

        "CREATE TABLE IF NOT EXISTS Java ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)",

        "CREATE TABLE IF NOT EXISTS Python ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)",

        "CREATE TABLE IF NOT EXISTS JavaScript ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)",

        "CREATE TABLE IF NOT EXISTS TypeScript ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)",

        "CREATE TABLE IF NOT EXISTS R ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)",

        "CREATE TABLE IF NOT EXISTS MySQL ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "language_id INT, "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200), "
        "FOREIGN KEY (language_id) REFERENCES Main(id) ON DELETE CASCADE ON UPDATE CASCADE)"
    };

    for (int i = 0; i < sizeof(create_table_queries) / sizeof(create_table_queries[0]); i++) {
        if (mysql_query(con, create_table_queries[i])) {
            finish_with_error(con);
        }
    }

    // Main 테이블에 데이터 삽입
    if (mysql_query(con, "INSERT INTO Main (language, Front_Back) VALUES "
        "('C', 'Backend'), "
        "('C++', 'Backend'), "
        "('C#', 'Backend'), "
        "('Ruby', 'Backend'), "
        "('Java', 'Backend'), "
        "('Python', 'Backend'), "
        "('JavaScript', 'Frontend'), "
        "('TypeScript', 'Frontend'), "
        "('R', 'Backend'), "
        "('MySQL', 'Backend')")) {
        finish_with_error(con);
    }

    printf("Main data inserted successfully!\n");

    // 각 언어별로 id 값을 가져와서 버전 데이터 삽입
    int language_id;

    // C 테이블 데이터 삽입
    language_id = get_language_id(con, "C");
    if (language_id > 0) {
        insert_version_data(con, "C", language_id, "C23", "2023/07/28", "New version of C23");
        insert_version_data(con, "C", language_id, "C17", "2017/01/15", "New version of C17");
    }

    // C++ 테이블 데이터 삽입
    language_id = get_language_id(con, "C++");
    if (language_id > 0) {
        insert_version_data(con, "Cpp", language_id, "Cpp23", "2023/07/28", "New version of Cpp23");
        insert_version_data(con, "Cpp", language_id, "Cpp17", "2017/01/15", "New version of Cpp17");
    }

    // C# 테이블 데이터 삽입
    language_id = get_language_id(con, "C#");
    if (language_id > 0) {
        insert_version_data(con, "C_Sharp", language_id, "C# 12.0", "2023/11/00", ".NET 8");
        insert_version_data(con, "C_Sharp", language_id, "C# 11.0", "2022/11/00", ".NET 7");
    }

    // Ruby 테이블 데이터 삽입
    language_id = get_language_id(con, "Ruby");
    if (language_id > 0) {
        insert_version_data(con, "Ruby", language_id, "Ruby 3.3.6", "2024/11/05", "Minor bug fixed");
        insert_version_data(con, "Ruby", language_id, "Ruby 3.2.6", "2024/10/30", "Improve base time of assert_linear");
    }

    // Java 테이블 데이터 삽입
    language_id = get_language_id(con, "Java");
    if (language_id > 0) {
        insert_version_data(con, "Java", language_id, "Java SE 24", "2025/03/18", "Not released");
        insert_version_data(con, "Java", language_id, "Java SE 23", "2024/09/17", "Minor bug fixed");
    }

    // Python 테이블 데이터 삽입
    language_id = get_language_id(con, "Python");
    if (language_id > 0) {
        insert_version_data(con, "Python", language_id, "Python 3.13", "2024/10/17", "Minor bug fixed");
        insert_version_data(con, "Python", language_id, "Python 3.12", "2023/10/02", "Minor bug fixed");
    }

    // JavaScript 테이블 데이터 삽입
    language_id = get_language_id(con, "JavaScript");
    if (language_id > 0) {
        insert_version_data(con, "JavaScript", language_id, "ECMAScript 2023 (ES14)", "2023/06/00", "Add new method");
        insert_version_data(con, "JavaScript", language_id, "ECMAScript 2022 (ES13)", "2022/06/00", "Fixed Error Class");
    }

    // TypeScript 테이블 데이터 삽입
    language_id = get_language_id(con, "TypeScript");
    if (language_id > 0) {
        insert_version_data(con, "TypeScript", language_id, "TypeScript 5.0", "2023/03/00", "Turbo Mode");
        insert_version_data(con, "TypeScript", language_id, "TypeScript 4.9", "2022/11/00", "Auto-import");
    }

    // R 테이블 데이터 삽입
    language_id = get_language_id(con, "R");
    if (language_id > 0) {
        insert_version_data(con, "R", language_id, "R 4.3.1", "2023/05/03", "Upgrade");
        insert_version_data(con, "R", language_id, "R 4.2.3", "2023/03/10", "Base R Upgrade");
    }

    // SQL 테이블 데이터 삽입
    language_id = get_language_id(con, "MySQL");
    if (language_id > 0) {
        insert_version_data(con, "MySQL", language_id, "MySQL 8.0", "2018/04/00", "Window Functions");
        insert_version_data(con, "MySQL", language_id, "MySQL 5.7", "2015/10/00", "Fixed Full-Text Search");
    }

    printf("All data inserted successfully!\n");

    // 데이터 조회
    query_and_print_table(con, "Main");
    query_and_print_table(con, "C");
    query_and_print_table(con, "Cpp");
    query_and_print_table(con, "C_Sharp");
    query_and_print_table(con, "Ruby");
    query_and_print_table(con, "Java");
    query_and_print_table(con, "Python");
    query_and_print_table(con, "JavaScript");
    query_and_print_table(con, "TypeScript");
    query_and_print_table(con, "R");
    query_and_print_table(con, "MySQL");

    mysql_close(con); // MySQL 연결 종료
    return 0; // 프로그램 정상 종료
}
