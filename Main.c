#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

// 에러 처리를 위한 함수
// MySQL에서 오류가 발생하면 오류 메시지를 출력하고 연결을 종료하며 프로그램을 종료함
void finish_with_error(MYSQL* con) {
    fprintf(stderr, "%s\n", mysql_error(con)); // 오류 메시지 출력
    mysql_close(con); // MySQL 연결 종료
    exit(1); // 프로그램 종료
}

int main() {
    // MySQL 연결 객체 초기화
    MYSQL* con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con)); // 초기화 실패 시 오류 메시지 출력
        exit(1); // 프로그램 종료
    }

    // MySQL 서버에 연결
    if (mysql_real_connect(con, "localhost", "root", "kimhungjin88@", "MyNewDatabase", 0, NULL, 0) == NULL) {
        finish_with_error(con); // 연결 실패 시 에러 처리 함수 호출
    }

    // Main 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS Main ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // id 필드: 자동 증가, 기본 키
        "language VARCHAR(100), "
        "Front_Back VARCHAR(100))")) { 
        finish_with_error(con); // 쿼리 실행 실패 시 에러 처리 함수 호출
    }

    // C 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS C ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(10), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // C++ 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS Cpp ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(10), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // C# 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS C_Sharp ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(10), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // Ruby 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS Ruby ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(10), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // Java 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS Java ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(10), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // Python 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS Python ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(10), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // JavaScript 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS JavaScript ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(10), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // TypeScript 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS TypeScript ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(10), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // R 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS R ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(10), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // SQL 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS `SQL` ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // Id 필드 : 자동 증가, 기본 키
        "language_id VARCHAR(20), "
        "version VARCHAR(100), "
        "date VARCHAR(100), "
        "documentation VARCHAR(200))")) {
        finish_with_error(con);
    }

    // Main 데이터 삽입
    //if (mysql_query(con, "INSERT INTO Main (language, Front_Back) VALUES "
    //    "('C', 'Backend'), "
    //    "('C++', 'Backend'), "
    //    "('C#', 'Backend'), "
    //    "('Ruby', 'Backend'), "
    //    "('Java', 'Backend'), "
    //    "('Python', 'Backend'), "
    //    "('Java_Script', 'Frontend'), "
    //    "('TypeScript', 'Backend'), "
    //    "('R', 'Backend'), "
    //    "('SQL', 'Backend')")) {
    //    finish_with_error(con); // 데이터 삽입 실패 시 에러 처리 함수 호출
    //}

    //printf("Data inserted successfully!\n"); // 데이터 삽입 성공 메시지 출력

    // C 테이블에 데이터 삽입
    /*if (mysql_query(con, "INSERT INTO C (language_id, version, date, documentation) VALUES "
        "('1', 'C23', '2023/07/28', 'new_version_of_23'), "
        "('1', 'C17', '2017/01/15', 'new_version_of_17')")) {
        finish_with_error(con);
    }

    printf("Data inserted into C successfully!\n");*/

    //// C++ 테이블에 데이터 삽입
    //if (mysql_query(con, "INSERT INTO Cpp (language_id, version, date, documentation) VALUES "
    //    "('2', 'Cpp23', '2023/07/28', 'new_version_of_23'), "
    //    "('2', 'Cpp17', '2017/01/15', 'new_version_of_17')")) {
    //    finish_with_error(con);
    //}

    //printf("Data inserted into C++ successfully!\n");

    //// C# 테이블에 데이터 삽입
    //if (mysql_query(con, "INSERT INTO C_Sharp (language_id, version, date, documentation) VALUES "
    //    "('3', 'C# 12.0', '2023/11/00', '.NET 8'), "
    //    "('3', 'C# 11.0', '2022/11/00', '.NET 7')")) {
    //    finish_with_error(con);
    //}

    //printf("Data inserted into C# successfully!\n");

    // Ruby 테이블에 데이터 삽입
    /*if (mysql_query(con, "INSERT INTO Ruby (language_id, version, date, documentation) VALUES "
        "('4', 'Ruby 3.3.6', '2024/11/05', 'minor bug fixed'), "
        "('4', 'Ruby 3.2.6', '2024/10/30', 'Improve base time of assert_linear')")) {
        finish_with_error(con);
    }*/

    //printf("Data inserted into Ruby successfully!\n");

    //// Java 테이블에 데이터 삽입
    //if (mysql_query(con, "INSERT INTO Java (language_id, version, date, documentation) VALUES "
    //    "('5', 'Java SE 24', '2025/3/18', 'Not released'), "
    //    "('5', 'Java SE 23', '2024/09/17', 'minor bug fixed')")) {
    //    finish_with_error(con);
    //}

    //printf("Data inserted into Java successfully!\n");

    //// Python 테이블에 데이터 삽입
    //if (mysql_query(con, "INSERT INTO Python (language_id, version, date, documentation) VALUES "
    //    "('6', 'Python 3,13', '2024/10/17', 'minor bug fixed'), "
    //    "('6', 'Python 3.12', '2023/10/02', 'minor bug fixed')")) {
    //    finish_with_error(con);
    //}

    //printf("Data inserted into Python successfully!\n\n");

    //// JavaScript 테이블에 데이터 삽입
    //if (mysql_query(con, "INSERT INTO JavaScript (language_id, version, date, documentation) VALUES "
    //    "('7', 'ECMAScript 2023 (ES14)', '2023/06/00', 'Add new method'), "
    //    "('7', 'ECMAScript 2022 (ES13)', '2022/06/00', 'Fixed Error Class')")) {
    //    finish_with_error(con);
    //}

    //printf("Data inserted into TJavaScript successfully!\n\n");

    //// TypeScript 테이블에 데이터 삽입
    //if (mysql_query(con, "INSERT INTO TypeScript (language_id, version, date, documentation) VALUES "
    //    "('8', 'TypeScript 5.0', '2023/03/00', 'Turbo Mode'), "
    //    "('8', 'TypeScript 4.9', '2022/11/00', 'auto-import')")) {
    //    finish_with_error(con);
    //}

    //printf("Data inserted into TypeScript successfully!\n\n");

    //// R 테이블에 데이터 삽입
    //if (mysql_query(con, "INSERT INTO R (language_id, version, date, documentation) VALUES "
    //    "('9', 'R 4.3.1', '2023/05/03', 'Upgrade'), "
    //    "('9', 'R 4.2.3', '2023/03/10', 'base R Upgrade')")) {
    //    finish_with_error(con);
    //}

    //printf("Data inserted into R successfully!\n\n");

    // SQL 테이블에 데이터 삽입
    if (mysql_query(con, "INSERT INTO `SQL` (language_id, version, date, documentation) VALUES "
        "('10', 'MySQL 8.0', '2018/04/00', 'Window Functions'), "
        "('10', 'MySQL 5.7', '2015/10/00', 'Fixed Full-Text Search')")) {
        finish_with_error(con);
    }

    printf("Data inserted into SQL successfully!\n\n");

    // Main 데이터 조회
    if (mysql_query(con, "SELECT * FROM Main")) {
        finish_with_error(con); // 데이터 조회 쿼리 실패 시 에러 처리 함수 호출
    }

    // 쿼리 결과 저장
    MYSQL_RES* result = mysql_store_result(con);

    if (result == NULL) {
        finish_with_error(con); // 결과 저장 실패 시 에러 처리 함수 호출
    }

    // 결과 필드(열) 수 가져오기
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    // 조회된 데이터 출력
    printf("Main Data:\n");
    while ((row = mysql_fetch_row(result))) { // 결과를 한 행씩 가져옴
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL"); // 각 열의 데이터를 출력 (NULL은 "NULL"로 표시)
        }
        printf("\n"); // 한 행 출력 완료 후 줄 바꿈
    }
    printf("\n");

    // C 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM C")) {
        finish_with_error(con);
    }

    MYSQL_RES* result2 = mysql_store_result(con);
    if (result2 == NULL) {
        finish_with_error(con);
    }

    printf("Data from C:\n");
    int num_fields2 = mysql_num_fields(result2);
    MYSQL_ROW row2;
    while ((row2 = mysql_fetch_row(result2))) {
        for (int i = 0; i < num_fields2; i++) {
            printf("%s ", row2[i] ? row2[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    // C++ 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM Cpp")) {
        finish_with_error(con);
    }

    MYSQL_RES* result3 = mysql_store_result(con);
    if (result3 == NULL) {
        finish_with_error(con);
    }

    printf("Data from C++:\n");
    int num_fields3 = mysql_num_fields(result3);
    MYSQL_ROW row3;
    while ((row3 = mysql_fetch_row(result3))) {
        for (int i = 0; i < num_fields3; i++) {
            printf("%s ", row3[i] ? row3[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    // C# 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM C_Sharp")) {
        finish_with_error(con);
    }

    MYSQL_RES* result4 = mysql_store_result(con);
    if (result4 == NULL) {
        finish_with_error(con);
    }

    printf("Data from C_Sharp:\n");
    int num_fields4 = mysql_num_fields(result4);
    MYSQL_ROW row4;
    while ((row4 = mysql_fetch_row(result4))) {
        for (int i = 0; i < num_fields4; i++) {
            printf("%s ", row4[i] ? row4[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    // Ruby 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM Ruby")) {
        finish_with_error(con);
    }

    MYSQL_RES* result5 = mysql_store_result(con);
    if (result5 == NULL) {
        finish_with_error(con);
    }

    printf("Data from Ruby:\n");
    int num_fields5 = mysql_num_fields(result5);
    MYSQL_ROW row5;
    while ((row5 = mysql_fetch_row(result5))) {
        for (int i = 0; i < num_fields5; i++) {
            printf("%s ", row5[i] ? row5[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    // Java 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM Java")) {
        finish_with_error(con);
    }

    MYSQL_RES* result6 = mysql_store_result(con);
    if (result6 == NULL) {
        finish_with_error(con);
    }

    printf("Data from java:\n");
    int num_fields6 = mysql_num_fields(result6);
    MYSQL_ROW row6;
    while ((row6 = mysql_fetch_row(result6))) {
        for (int i = 0; i < num_fields6; i++) {
            printf("%s ", row6[i] ? row6[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    // Python 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM Python")) {
        finish_with_error(con);
    }

    MYSQL_RES* result7 = mysql_store_result(con);
    if (result7 == NULL) {
        finish_with_error(con);
    }

    printf("Data from Python:\n");
    int num_fields7 = mysql_num_fields(result7);
    MYSQL_ROW row7;
    while ((row7 = mysql_fetch_row(result7))) {
        for (int i = 0; i < num_fields7; i++) {
            printf("%s ", row7[i] ? row7[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    // JavaScript 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM JavaScript")) {
        finish_with_error(con);
    }

    MYSQL_RES* result8 = mysql_store_result(con);
    if (result8 == NULL) {
        finish_with_error(con);
    }

    printf("Data from JavaScript:\n");
    int num_fields8 = mysql_num_fields(result8);
    MYSQL_ROW row8;
    while ((row8 = mysql_fetch_row(result8))) {
        for (int i = 0; i < num_fields8; i++) {
            printf("%s ", row8[i] ? row8[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    // TypeScript 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM TypeScript")) {
        finish_with_error(con);
    }

    MYSQL_RES* result9 = mysql_store_result(con);
    if (result9 == NULL) {
        finish_with_error(con);
    }

    printf("Data from TypeScript:\n");
    int num_fields9 = mysql_num_fields(result9);
    MYSQL_ROW row9;
    while ((row9 = mysql_fetch_row(result9))) {
        for (int i = 0; i < num_fields9; i++) {
            printf("%s ", row9[i] ? row9[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    // R 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM R")) {
        finish_with_error(con);
    }

    MYSQL_RES* result10 = mysql_store_result(con);
    if (result10 == NULL) {
        finish_with_error(con);
    }

    printf("Data from R:\n");
    int num_fields10 = mysql_num_fields(result10);
    MYSQL_ROW row10;
    while ((row10 = mysql_fetch_row(result10))) {
        for (int i = 0; i < num_fields10; i++) {
            printf("%s ", row10[i] ? row10[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");

    // SQL 테이블 데이터 조회
    if (mysql_query(con, "SELECT * FROM `SQL`")) {
        finish_with_error(con);
    }

    MYSQL_RES* result11 = mysql_store_result(con);
    if (result11 == NULL) {
        finish_with_error(con);
    }

    printf("Data from SQL:\n");
    int num_fields11 = mysql_num_fields(result11);
    MYSQL_ROW row11;
    while ((row11 = mysql_fetch_row(result11))) {
        for (int i = 0; i < num_fields11; i++) {
            printf("%s ", row11[i] ? row11[i] : "NULL");
        }
        printf("\n");
    }
    printf("\n");


    mysql_free_result(result); // 결과 메모리 해제
    mysql_close(con); // MySQL 연결 종료

    return 0; // 프로그램 정상 종료
}
