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

    // 테이블 생성
    if (mysql_query(con, "CREATE TABLE IF NOT EXISTS TestTable ("
        "id INT AUTO_INCREMENT PRIMARY KEY, " // id 필드: 자동 증가, 기본 키
        "name VARCHAR(100), " // name 필드: 최대 100자의 문자열
        "age INT)")) { // age 필드: 정수형
        finish_with_error(con); // 쿼리 실행 실패 시 에러 처리 함수 호출
    }

    // 데이터 삽입
    if (mysql_query(con, "INSERT INTO TestTable (name, age) VALUES('Alice', 25), ('Bob', 30)")) {
        finish_with_error(con); // 데이터 삽입 실패 시 에러 처리 함수 호출
    }

    printf("Data inserted successfully!\n"); // 데이터 삽입 성공 메시지 출력

    // 데이터 조회
    if (mysql_query(con, "SELECT * FROM TestTable")) {
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
    printf("Fetched Data:\n");
    while ((row = mysql_fetch_row(result))) { // 결과를 한 행씩 가져옴
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL"); // 각 열의 데이터를 출력 (NULL은 "NULL"로 표시)
        }
        printf("\n"); // 한 행 출력 완료 후 줄 바꿈
    }

    mysql_free_result(result); // 결과 메모리 해제
    mysql_close(con); // MySQL 연결 종료

    return 0; // 프로그램 정상 종료
}
