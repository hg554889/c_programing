#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

// 에러 처리를 위한 함수
void finish_with_error(MYSQL* con) {
    fprintf(stderr, "%s\n", mysql_error(con)); // 오류 메시지 출력
    mysql_close(con); // MySQL 연결 종료
    exit(1); // 프로그램 종료
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

    // 데이터베이스의 테이블 목록 가져오기
    if (mysql_query(con, "SHOW TABLES")) {
        finish_with_error(con);
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }

    printf("Tables in MyNewDatabase:\n");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("%s\n", row[0]);
    }
    mysql_free_result(result);

    // 각 테이블의 열 정보 가져오기
    if (mysql_query(con, "SHOW TABLES")) {
        finish_with_error(con);
    }

    result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }

    while ((row = mysql_fetch_row(result))) {
        char query[256];
        snprintf(query, sizeof(query), "SHOW COLUMNS FROM %s", row[0]);

        if (mysql_query(con, query)) {
            finish_with_error(con);
        }

        MYSQL_RES* columns_result = mysql_store_result(con);
        if (columns_result == NULL) {
            finish_with_error(con);
        }

        printf("\nColumns in table %s:\n", row[0]);
        MYSQL_ROW column_row;
        while ((column_row = mysql_fetch_row(columns_result))) {
            printf("%s %s\n", column_row[0], column_row[1]);
        }
        mysql_free_result(columns_result);
    }

    mysql_free_result(result);
    mysql_close(con); // MySQL 연결 종료
    return 0; // 프로그램 정상 종료
}
